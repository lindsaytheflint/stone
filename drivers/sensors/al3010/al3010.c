#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/microp_notify.h>
#include <linux/atomic.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/miscdevice.h>
#include <linux/switch.h>
#include <linux/microp_api.h>
#include <linux/microp_pin_def.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h> 
#endif

#define AL3010_DRV_NAME	"al3010_light_sensor"
#define DRIVER_VERSION		"1.0"

#define P01_EVENT_NOTIFY_LIGHTSENSOR_NO_ERROR (0)
#define P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR (-1)

#define AL3010_NUM_CACHABLE_REGS	9

#define	AL3010_ALS_COMMAND	0x04
#define	AL3010_RAN_MASK	0x70
#define	AL3010_RAN_SHIFT	(4)

#define AL3010_MODE_COMMAND	0x00
#define AL3010_MODE_SHIFT	(0)
#define AL3010_MODE_MASK	0x07

#define AL3010_POW_MASK		0x01
#define AL3010_POW_UP		0x01
#define AL3010_POW_DOWN		0x00
#define AL3010_POW_RESET        0x04
#define AL3010_POW_SHIFT	(0)

#define	AL3010_ADC_LSB	0x0c
#define	AL3010_ADC_MSB	0x0d

#if 0
static u8 al3010_reg[AL3010_NUM_CACHABLE_REGS] = 
	{0x00,0x01,0x0c,0x0d,0x10,0x1a,0x1b,0x1c,0x1d};
#endif

static int al3010_range[4] = {77806,19452,4863,1216};

struct al3010_data {
	struct i2c_client *client;
	struct mutex lock;
        struct input_dev   *input_dev;
	u8 reg_cache[AL3010_NUM_CACHABLE_REGS];
	u8 power_state_before_suspend;
};

struct _al3010_device {
    int (*init_hw)(struct i2c_client *client);
    u8    (*read_int_pin_state)(void);
    int irq;
} g_al3010_device;

struct al3010_data *g_al3010_data_as;
struct input_dev *this_input_dev_p02_als = NULL;

static struct workqueue_struct *al3010light_workqueue = NULL;
static struct delayed_work al3010_attached_P02_work;
static struct work_struct al3010_ISR_work;
bool al3010_interrupt_busy = false;

/*For resume and debounce I2C issue*/
static struct delayed_work Al3010light_resume_work;
static struct delayed_work Al3010light_debounce_work;
static struct workqueue_struct *Al3010light_delay_workqueue = NULL;
bool g_al3010_suspend_switch_on = false;
	

struct i2c_client *al3010_client = NULL;

static int level = 0;
static int TOTALMAPS = 12;
static int g_al3010_light_map[12] = 
    {0,50,100,200,300,450,700,850,1050,1250,1500,2200};

static int al3010_threshold_max_level = 34;
static int g_al3010_light_level[34] = 
    {1,3,6,10,13,16,20,23,26,30,36,46,56,70,80,90,100,125,150,175,200,250,275,300,325,350,450,550,700,850,1050,1250,1500,2200} ;    
    
//{ 0 , 50, 100, 200, 300, 400, 500, 600, 700, 900, 1100, 1400, 1700, 2100};

bool g_bIsP01Attached = false;
bool g_al3010_switch_on = false;
static int g_AlsP01ProbeError = 0xff;

static int g_al3010_switch_earlysuspend = 0;
static int g_al3010_light = 0;
static int g_last_al3010_light = -1;
static int p_als_threshold_lo = 0;
static int p_als_threshold_hi = 0;

/* For Calibration*/
#ifdef ASUS_FACTORY_BUILD
static int p_als_calibration_lux = 800;
static int p_als_low_calibration_adc = 0;
static int p_als_high_calibration_adc = 0;
#endif
static u32 g_al3010_light_calibration = 84;
static int g_al3010_light_shift_calibration = 35;


static int al3010_get_adc_value(struct i2c_client *client);
static void lightsensor_attached_pad_P01(struct work_struct *work);
static int al3010_put_property(struct i2c_client *client);
static void mp_als_interrupt_handler(struct work_struct *work);
//static int al3010_init_client(struct i2c_client *client);

//void reportPadStationI2CFail(char *devname);;
extern void als_lux_report_event(int);
//extern bool hdmi_exist(void);
extern int g_HAL_als_switch_on;
extern int g_cm36283_light;
extern unsigned int g_microp_ver;

atomic_t p02_ambient_update;


static struct switch_dev ls_switch_dev ={ 
        .name = AL3010_DRV_NAME,
        .index = 0,
};

#ifdef CONFIG_I2C_STRESS_TEST

#include <linux/i2c_testcase.h>

#define I2C_TEST_FAIL_SENSOR (-1)
int set_als_power_state_of_P01(int);

static int Test_Al3010_SensorI2C(struct i2c_client *apClient)
{
	int err = 0;
	int lnResult = I2C_TEST_PASS;

	//i2c_log_in_test_case("Test_Al3010_SensorI2C++\n");
	
	if( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(100));

		i2c_log_in_test_case("Test_Al3010_SensorI2C++\n");
		
		if (g_HAL_als_switch_on)
			err = set_als_power_state_of_P01(1);
		else
			err = set_als_power_state_of_P01(0);
		if ( err < 0 )	{
			i2c_log_in_test_case("Fail to lsensor test\n");
			lnResult = I2C_TEST_FAIL_SENSOR;
		}
	}else	{
		i2c_log_in_test_case("Fail to lsensor test\n");
		lnResult = I2C_TEST_FAIL_SENSOR;
	}

	i2c_log_in_test_case("Test_Al3010_SensorI2C--\n");

	return lnResult;
};

static struct i2c_test_case_info gSensorTestCaseInfo[] =
{
	__I2C_STRESS_TEST_CASE_ATTR(Test_Al3010_SensorI2C),
};
#endif
//ASUS_MERGE_END

// ++Louis 20120215

#define AL3010_INT_STATUS          0x01
#define AL3010_INT_COMMAND         0x10
#define AL3010_INT_SHIFT           0x00       
#define AL3010_INT_IF              0x03
#define AL3010_INT_MASK            0xff

#define AL3010_LOW_THD_LSB         0x1A
#define AL3010_LOW_THD_MSB         0x1B
#define AL3010_HIGH_THD_LSB        0x1C
#define AL3010_HIGH_THD_MSB        0x1D

//range 4: 0~1216 lux, resolution = 0.0186 lux/count
#define CNT_RESOLUTION  (10000/186)  //  range 4: 1/0.0186 = 54
static int g_thd[33] = { 0, 1, 3, 6, 10, 13, 16, 20, 23, 26, 30, 36, 46, 56, 70, 80,90,100,125,150,175,200,250,275,300,325,350, 450, 550, 700, 850, 1050, 1213};

/*
static int g_lsb_thd[30] =   {0,0x01,0x03,0x06,0x0a,0x0d,0x10,0x14,0x17,0x1e,0x24,0x2e,0x38,0x46,0x53,
									0x64,0x96,0xc8,0xfa,0x2c,0x5e,0xc2,0x26,0xbc,0x52,0x1a,0xe2,0xdc,0x98,0xff};

static int g_msb_thd[30] = {0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
									0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x02,0x02,0x03,0x04,0x04,0x05,0x08,0xff};
*/


/*Interrupt Filter*/
static int ALS_IF = 0x02;	//8 conversion times

/*Ambient light detectable range*/
static int ALS_Gain = 0x03;		//0~1216 Lux 	  :   resolution = 0.3

/*
 * register access helpers
 */

static int __al3010_read_reg(struct i2c_client *client,
			       u32 reg, u8 mask, u8 shift)
{
	struct al3010_data *data = i2c_get_clientdata(client);
	return (data->reg_cache[reg] & mask) >> shift;
}

static int __al3010_write_reg(struct i2c_client *client,
				u32 reg, u8 mask, u8 shift, u8 val)
{
	struct al3010_data *data = i2c_get_clientdata(client);
	int ret = 0;
	u8 tmp;

	if (reg >= AL3010_NUM_CACHABLE_REGS)
		return -EINVAL;

	mutex_lock(&data->lock);

	tmp = data->reg_cache[reg];
	tmp &= ~mask;
	tmp |= val << shift;

	ret = i2c_smbus_write_byte_data(client, reg, tmp);
	if (!ret)
		data->reg_cache[reg] = tmp;

	mutex_unlock(&data->lock);
	return ret;
}

/*
 * internally used functions
 */

/* range */
static int al3010_get_range(struct i2c_client *client)
{
	int tmp;
	tmp = __al3010_read_reg(client, AL3010_ALS_COMMAND,
											AL3010_RAN_MASK, AL3010_RAN_SHIFT);;
	return al3010_range[tmp];
}

static int al3010_set_range(struct i2c_client *client, int range)
{
	//return __al3010_write_reg(client, AL3010_ALS_COMMAND, AL3010_RAN_MASK, AL3010_RAN_SHIFT, range);
	return i2c_smbus_write_byte_data(client, AL3010_INT_COMMAND,  range);
}

/* mode */
static int al3010_get_mode(struct i2c_client *client)
{
	return __al3010_read_reg(client, AL3010_MODE_COMMAND,
		AL3010_MODE_MASK, AL3010_MODE_SHIFT);
}

static int al3010_set_mode(struct i2c_client *client, int mode)
{
    if(AL3010_POW_UP == (mode & AL3010_POW_MASK)) {
        g_al3010_switch_on = true;
    }
    else if(AL3010_POW_DOWN == (mode & AL3010_POW_MASK)) {
        g_al3010_switch_on = false;
    }

	return __al3010_write_reg(client, AL3010_MODE_COMMAND,
		AL3010_MODE_MASK, AL3010_MODE_SHIFT, mode);
}

/* power_state */
static int al3010_set_power_state(struct i2c_client *client, int state)
{
	if(AL3010_POW_UP == state)
		g_al3010_switch_on = true;
	else if(AL3010_POW_DOWN == state)
		g_al3010_switch_on = false;

	printk(DBGMSK_PRX_G2"[als_P01] al3010_set_pwr_state: state:%d\n", g_al3010_switch_on);

	return i2c_smbus_write_byte_data(al3010_client, AL3010_MODE_COMMAND, g_al3010_switch_on);
}

static int al3010_get_power_state(struct i2c_client *client)
{
	return i2c_smbus_read_byte_data(al3010_client, AL3010_MODE_COMMAND );
/*
	struct al3010_data *data = i2c_get_clientdata(client);
	u8 cmdreg = data->reg_cache[AL3010_MODE_COMMAND];
	return (cmdreg & AL3010_POW_MASK) >> AL3010_POW_SHIFT;
*/
}

int set_als_power_state_of_P01(int state)
{
	int ret = 0, indx;
	printk("[als_P01]set_als_pwr_state: %d\n", state );
	if( !AX_MicroP_IsP01Connected() )	{
		printk(DBGMSK_PRX_G0"[als_P01]Without P03 plug in\n");
		return -1;		
	}
	
	if( g_al3010_switch_earlysuspend == 1 )	{
		g_al3010_suspend_switch_on = state;
		printk(DBGMSK_PRX_G0"[als_P01][als] Al3010 without resume, by pass; state:%d\n", g_al3010_switch_earlysuspend);
		return 0;
	}else
		g_al3010_suspend_switch_on = false;

	printk("MicroP fw ver=0x%x\r\n",g_microp_ver);
	if( g_microp_ver  >= 0x328 )	{		//Check microp fw
		al3010_interrupt_busy = true;

		/*Turn on/off al3010*/
		for(indx = 0; indx<5; indx++) {
			if( state){
				ret = al3010_put_property(al3010_client);
				msleep(2);
			}
			ret = AX_MicroP_initLightsensor(state);
			if(!ret) {
				printk(DBGMSK_PRX_G2"[al3010][als] switch on al3010 success\n");
				msleep(10);
				ret = AX_MicroP_getLightsensorInitResult();
				printk(DBGMSK_PRX_G2"[al3010][als] Read Microplightsensor command result = %d\n", ret );
				if ( ret )
					printk("[al3010][als] Microplightsensor command fail\n");
				else	{
					if(AL3010_POW_UP == state)
						g_al3010_switch_on = true;
					else if(AL3010_POW_DOWN == state)
						g_al3010_switch_on = false;
					break;
				}
			}else
				printk("[al3010][als] i2c error retry = %d\n",indx);
		}

		if (indx >= 5) {
			al3010_interrupt_busy = false;
			return ret;
		}

		/*Release interrupt trigger*/
		AX_MicroP_getLightsensorADC();
		al3010_interrupt_busy = false;
		
		if (state == 1)
			printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor dev_open\n");
		else
			printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor dev_close\n");
	}	else		{		//For support old microp version
		for(indx = 0; indx<5; indx++) {		
			ret = al3010_put_property(al3010_client);
			if(!ret)	{
				printk(DBGMSK_PRX_G2"[al3010][als] init al3010 success\n");
				break;
			}else	{
				printk("[al3010][als] init_client error retry = %d\n",indx);
				msleep( 10 );
			}
		}
		if ( indx == 5 )
			return ret;

		for(indx = 0; indx<5; indx++) {
			ret = al3010_set_power_state(al3010_client, state? AL3010_POW_UP:AL3010_POW_DOWN);
			if(!ret) {
				printk(DBGMSK_PRX_G2"[al3010][als] switch on al3010 success\n");
				break;
			}else
				printk("[al3010][als] i2c error retry = %d\n",indx);
		}

		if (indx == 5) {
			//reportPadStationI2CFail("al3010");
			return ret;
		}

		if (state == 1)
			printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor dev_open\n");
		else
			printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor dev_close\n");
	}

	if ( g_al3010_switch_on )
		queue_work(al3010light_workqueue ,&al3010_ISR_work);
	
	return ret;
}
EXPORT_SYMBOL(set_als_power_state_of_P01);

static int al3010_get_adc_value(struct i2c_client *client)
{
	struct al3010_data *data = i2c_get_clientdata(client);
	int lsb, msb;
	int adc, i;
	printk(DBGMSK_PRX_G6"[als_P01]++al3010_get_adc_value \n");

	if( g_microp_ver  >= 0x328 )		//Check microp fw
		adc = AX_MicroP_getLightsensorADC();
	else		{
	
		mutex_lock(&data->lock);
		msb = i2c_smbus_read_byte_data(client, AL3010_MODE_COMMAND);
		printk(DBGMSK_PRX_G6"[als_P01]al3010_get_adc_value: reg (0x00) = 0x%x\n", msb);
		msb = i2c_smbus_read_byte_data(client, AL3010_INT_COMMAND);
		printk(DBGMSK_PRX_G6"[als_P01]al3010_get_adc_value: reg (0x10) = 0x%x\n", msb);

		lsb = i2c_smbus_read_byte_data(client, AL3010_ADC_LSB);

		if (lsb < 0) {
			mutex_unlock(&data->lock);
			return lsb;
		}

		msb = i2c_smbus_read_byte_data(client, AL3010_ADC_MSB);
		mutex_unlock(&data->lock);

		printk(DBGMSK_PRX_G6"[als_P01]****al3010_get_adc_value: msb=%d, lsb=%d\n", msb, lsb);

		if (msb < 0)
			return msb;

		adc = (u32)((msb << 8) | lsb) ;
	}

	adc = adc / CNT_RESOLUTION;

	/*Get Lux*/
	adc = g_al3010_light_shift_calibration + (adc * g_al3010_light_calibration);
	for( i = 1 ; i < TOTALMAPS ; i++) {
		if( adc < g_al3010_light_map[i] ) {
			adc = g_al3010_light_map[ i -1 ];
			break;
		}
		else if( adc > g_al3010_light_map[TOTALMAPS - 1] )	{
			adc = g_al3010_light_map[ TOTALMAPS -1 ];
			break;
		}
	}
	if( adc > g_al3010_light_map[TOTALMAPS - 1] )
		adc = g_al3010_light_map[TOTALMAPS - 1];

	return adc;
}



static int al3010_put_property(struct i2c_client *client)
{
	int status = 0;
	int lsb, msb;

	if( g_microp_ver  >= 0x328 )	{		//Check microp fw
		status = AX_MicroP_setLightsensor_TS_Low( g_thd[0] * CNT_RESOLUTION );

		printk(DBGMSK_PRX_G2"[als_P02]++ al3010_set_inital_low_threshold_value: %d \n", g_thd[0] * CNT_RESOLUTION );

		msleep(1);
		status = AX_MicroP_setLightsensor_TS_High( g_thd[1] * CNT_RESOLUTION );

		printk(DBGMSK_PRX_G2"[als_P02]-- al3010_set_inital_high_threshold_value: %d\n", g_thd[1] * CNT_RESOLUTION );
	}else 	{		//For support old microp version

	        status = i2c_smbus_write_byte_data(client, AL3010_INT_COMMAND,  ALS_IF | (ALS_Gain << 4 ));
	        if (status < 0)  {
	            printk(DBGMSK_PRX_G2"[als_P02] addr=0x%x, val=0x%x, ret=%d\n",AL3010_INT_COMMAND, ALS_IF | (ALS_Gain << 4 ), status);
	            switch_set_state(&ls_switch_dev, P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR);
	            return status;
	        }
	        else
	            printk(DBGMSK_PRX_G2"[als_P02] addr=0x%x, val=0x%x\n",AL3010_INT_COMMAND, ALS_IF  | (ALS_Gain << 4 ) );

	        i2c_smbus_write_byte_data(client, AL3010_LOW_THD_LSB, (g_thd[0] * CNT_RESOLUTION) & 0xFF);
	        lsb = i2c_smbus_read_byte_data(client, AL3010_LOW_THD_LSB);
	        
	        i2c_smbus_write_byte_data(client, AL3010_LOW_THD_MSB, ((g_thd[0] * CNT_RESOLUTION) >> 8 ) & 0xFF);
	        msb = i2c_smbus_read_byte_data(client, AL3010_LOW_THD_MSB);

	        printk(DBGMSK_PRX_G2"[als_P02]++ al3010_set_inital_low_threshold_value: msb=%d, lsb=%d\n", msb, lsb);

	        i2c_smbus_write_byte_data(client, AL3010_HIGH_THD_LSB, (g_thd[1] * CNT_RESOLUTION) & 0xFF);
	        lsb = i2c_smbus_read_byte_data(client, AL3010_HIGH_THD_LSB);
	        

	        i2c_smbus_write_byte_data(client, AL3010_HIGH_THD_MSB, ((g_thd[1] * CNT_RESOLUTION) >> 8 ) & 0xFF);
	        msb = i2c_smbus_read_byte_data(client, AL3010_HIGH_THD_MSB);

	        printk(DBGMSK_PRX_G2"[als_P02]-- al3010_set_inital_high_threshold_value: msb=%d, lsb=%d\n", msb, lsb);

	}
/*
	status = i2c_smbus_read_byte_data(client, AL3010_INT_STATUS);

	if (status == 0)
		printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor interrupt is cleared\n");
	else
		printk(DBGMSK_PRX_G2"[al3010][als] P02 light sensor interrupt is triggered\n");
*/  
        return 0;
}

static void mp_als_interrupt_delay_work(struct work_struct *work)
{
	struct al3010_data *data = i2c_get_clientdata(al3010_client);
	int i,ret = 0;

	mutex_lock(&data->lock);
	al3010_interrupt_busy = true;

	/* Set Low threshold*/
	AX_MicroP_setLightsensor_TS_Low( g_thd[level] * CNT_RESOLUTION );
#if 0
		if(!ret) {
			msleep(2);
			ret = AX_MicroP_getLightsensorInitResult();
			printk(DBGMSK_PRX_G2"[al3010][als] SetLightsensor_TS_Low command result = %d\n", ret );
			if ( ret )
				printk("[al3010][als] SetLightsensor_TS_Low command fail\n");
			else	
				printk(DBGMSK_PRX_G2"[al3010][als] SetLightsensor_TS_Low command success\n");
		}
#endif

	p_als_threshold_lo = g_thd[level];
	printk(DBGMSK_PRX_G2"[als_P02]-- al3010_set_low_threshold_value: %d \n",p_als_threshold_lo );

	/* Set High threshold*/
	msleep(1);		//wait for AX_MicroP_setLightsensor_TS_Low finish
	AX_MicroP_setLightsensor_TS_High( g_thd[level + 1] * CNT_RESOLUTION );
#if 0
		if(!ret) {
			msleep(2);
			ret = AX_MicroP_getLightsensorInitResult();
			printk(DBGMSK_PRX_G2"[al3010][als] SetLightsensor_TS_Hight command result = %d\n", ret );
			if ( ret )
				printk("[al3010][als] SetLightsensor_TS_Hight command fail\n");
			else	
				printk(DBGMSK_PRX_G2"[al3010][als] SetLightsensor_TS_Hight command success\n");
		}
#endif
	p_als_threshold_hi = g_thd[level + 1];
	printk(DBGMSK_PRX_G2"[als_P02]++ al3010_set_high_threshold_value: %d \n",p_als_threshold_hi );

	/*Trun on al3010*/
	msleep(1);
	for(i = 0; i<5; i++) {
		ret = AX_MicroP_initLightsensor(g_al3010_switch_on);
		if(!ret) {
			printk(DBGMSK_PRX_G2"[al3010][als] switch on al3010 success\n");
			msleep(10);
			ret = AX_MicroP_getLightsensorInitResult();
			printk(DBGMSK_PRX_G2"[al3010][als] Read Microplightsensor command result = %d\n", ret );
			if ( ret )
				printk("[al3010][als] Microplightsensor command fail\n");
			else	
				break;
		}else
			printk("[al3010][als] i2c error retry = %d\n",i);
	}
	msleep(1);
	/*Release interrupt trigger*/
	AX_MicroP_getLightsensorADC();
	
	mutex_unlock(&data->lock);
	al3010_interrupt_busy = false;
}

static void mp_als_interrupt_handler(struct work_struct *work)
{
	struct al3010_data *data = i2c_get_clientdata(al3010_client);
	int lsb, msb,i,ret = 0;
	u16 adc = 0;
	int k_adc = 0;
	level = 0;
	
	if( g_bIsP01Attached && g_al3010_switch_on ) {
		mutex_lock(&data->lock);

		if( g_microp_ver  >= 0x328 )	{		//Check microp fw
			al3010_interrupt_busy = true;

			/*Get Adc*/
			adc = AX_MicroP_getLightsensorADC();
			if( adc >= 0 ) {
				msleep(1);		//wait for microp change state from mast to slave
				ret = AX_MicroP_initLightsensor(0);
				//ret = AX_MicroP_getLightsensorInitResult();
				printk(DBGMSK_PRX_G2"[al3010][als] GetLightsensorADC command result = %d\n", ret );
				if ( ret )
					printk("[al3010][als] GetLightsensorADC command fail\n");
				else	
					printk(DBGMSK_PRX_G2"[al3010][als] GetLightsensorADC command success\n");
			}

			al3010_interrupt_busy = false;
		}else 	{		//For support old microp version
			lsb = i2c_smbus_read_byte_data(al3010_client, AL3010_ADC_LSB);
			if (lsb < 0) {
				switch_set_state(&ls_switch_dev,P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR);
				return;
			}

			msb = i2c_smbus_read_byte_data(al3010_client, AL3010_ADC_MSB);
			if (msb < 0) {
				switch_set_state(&ls_switch_dev,P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR);
				return;
			}
			adc = (u32)((msb << 8) | lsb) ;
		}
		
		mutex_unlock(&data->lock);
		
		adc = adc / CNT_RESOLUTION;

		printk(DBGMSK_PRX_G2"/********************************************************/\n");
		printk(DBGMSK_PRX_G2"[als_P02] al3010_get_raw_adc_value: %d\n", adc);

		/*Get threshold level*/
		for( i = 0 ; i < al3010_threshold_max_level ; i++) {
			if( adc < g_al3010_light_level[i] ) {
				level = i;
				break;
			}
			else if (adc > g_al3010_light_level[al3010_threshold_max_level - 1])	{
				level = al3010_threshold_max_level;
				break;
			}
		}

		/*Get Lux*/
		g_al3010_light = 0;
		if ( adc <= 0 )
			k_adc = 0;
		else
			k_adc = g_al3010_light_shift_calibration + (adc * g_al3010_light_calibration);
		for( i=1 ; i < TOTALMAPS ; i++) {
			if( k_adc < g_al3010_light_map[i] ) {
				g_al3010_light = g_al3010_light_map[ i -1 ];
				break;
			}
			else if( k_adc > g_al3010_light_map[TOTALMAPS - 1] )	{
				g_al3010_light = g_al3010_light_map[ TOTALMAPS -1 ];
				break;
			}
		}	
		if( g_al3010_light > g_al3010_light_map[TOTALMAPS - 1] )
			g_al3010_light = g_al3010_light_map[TOTALMAPS - 1];
		printk(DBGMSK_PRX_G2"[als_P02] level= %d, raw adc= %d, cal_adc= %d, lux = %d\n",level, adc, k_adc, g_al3010_light);

		/* Report Lux*/
		if(g_al3010_light != g_last_al3010_light) {
			g_last_al3010_light = g_al3010_light;
			als_lux_report_event(g_al3010_light);
		}
		printk(DBGMSK_PRX_G3"[cm36283][als] last=%d light=%d i=%d\n", g_last_al3010_light, g_al3010_light, g_al3010_light_map[i - 1]);

		if( g_microp_ver  >= 0x328 )	{		//Check microp fw
			/*Debounce lightsensor*/
			queue_delayed_work(Al3010light_delay_workqueue, &Al3010light_debounce_work, HZ);
		}else 	{		//For support old microp version
			/* Set Low threshold*/
			i2c_smbus_write_byte_data(al3010_client, AL3010_LOW_THD_LSB, (g_thd[level] * CNT_RESOLUTION) & 0xFF);
			lsb = i2c_smbus_read_byte_data(al3010_client, AL3010_LOW_THD_LSB);

			i2c_smbus_write_byte_data(al3010_client, AL3010_LOW_THD_MSB, ((g_thd[level] * CNT_RESOLUTION) >> 8 ) & 0xFF);
			msb = i2c_smbus_read_byte_data(al3010_client, AL3010_LOW_THD_MSB);

			p_als_threshold_lo = ((msb <<8) | lsb )/ CNT_RESOLUTION;
			printk(DBGMSK_PRX_G2"[als_P02]-- al3010_get_high_threshold_value: %d ,msb=%d, lsb=%d\n"
											,p_als_threshold_lo, msb, lsb);

			/* Set High threshold*/
			i2c_smbus_write_byte_data(al3010_client, AL3010_HIGH_THD_LSB, (g_thd[level + 1] * CNT_RESOLUTION) & 0xFF);
			lsb = i2c_smbus_read_byte_data(al3010_client, AL3010_HIGH_THD_LSB);

			i2c_smbus_write_byte_data(al3010_client, AL3010_HIGH_THD_MSB, ((g_thd[level + 1] * CNT_RESOLUTION) >> 8 ) & 0xFF);
			msb = i2c_smbus_read_byte_data(al3010_client, AL3010_HIGH_THD_MSB);

			p_als_threshold_hi = ((msb <<8) | lsb )/ CNT_RESOLUTION;
			printk(DBGMSK_PRX_G2"[als_P02]++ al3010_get_low_threshold_value: %d ,msb=%d, lsb=%d\n"
											,p_als_threshold_hi, msb, lsb);
		}
	}
}

/*
 * sysfs layer
 */

/* range */
static ssize_t al3010_show_range(struct device *dev, struct device_attribute *attr, char *buf)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		struct i2c_client *client = to_i2c_client(dev);
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_range: %d\n", al3010_get_range(client));
		
		return sprintf(buf, "%i\n", al3010_get_range(client));
	}else
		return 0;
}

static ssize_t al3010_store_range(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		struct i2c_client *client = to_i2c_client(dev);
		unsigned long val;
		int ret;

		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_range\n");

		if ((strict_strtoul(buf, 10, &val) < 0) || (val > 3))
			return -EINVAL;

		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_range: %lu\n", val);
		ret = al3010_set_range(client, val);
		if (ret < 0)
			return ret;

		return count;
	}else
		return 0;
	
}

static DEVICE_ATTR(range, S_IWUSR | S_IRUGO,
		   al3010_show_range, al3010_store_range);

#ifdef ASUS_FACTORY_BUILD
/* calibration */
static int al3010_show_calibration_200(struct device *dev, struct device_attribute *attr, char *buf)
{
	u32 p0_calibration_data = 0;
	
	if ( g_bIsP01Attached )	{
		p0_calibration_data = AX_MicroP_readKDataOfLightSensor();
		
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_gait_calibration: %d\n", p0_calibration_data & 0x00ff );
		
		return sprintf(buf, "%d\n", p0_calibration_data & 0x00ff );
	}else	{
			printk("[als_P01] Without P03\n");
			return -1;
	}
}

static int al3010_store_calibration_200(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val;
	p_als_low_calibration_adc = 0;

	if ( g_bIsP01Attached )	{
		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_resolution\n");

		if ( (strict_strtoul(buf, 10, &val) < 0) )
			return -EINVAL;

		p_als_low_calibration_adc = (int)val;

		printk("[als_P01] al3010 Get low calibration adc value : %d\n", p_als_low_calibration_adc );

		return p_als_low_calibration_adc;
	}
	else	{
			printk("[als_P01] Without P03\n");
			return -1;
	}

	return p_als_low_calibration_adc;
}

static DEVICE_ATTR(calibration_200, S_IRWXU | S_IRWXG,
		   al3010_show_calibration_200, al3010_store_calibration_200);


static ssize_t al3010_show_calibration_1000(struct device *dev, struct device_attribute *attr, char *buf)
{
	u32 p0_calibration_data = 0;
	
	if ( g_bIsP01Attached )	{
		p0_calibration_data = AX_MicroP_readKDataOfLightSensor();

		if ( (0xff << 24 ) & p0_calibration_data )	{
			printk(DBGMSK_PRX_G2"[als_P01] al3010_show_shift_calibration: %d\n", 
				(p0_calibration_data >> 8) | (0xff << 24 ) );
			return sprintf(buf, "%d\n", (int)((p0_calibration_data >> 8) | (0xff << 24)) );
		}else	{
			printk(DBGMSK_PRX_G2"[als_P01] al3010_show_shift_calibration: %d\n", 
				(p0_calibration_data >> 8) );
			return sprintf(buf, "%d\n", (int)(p0_calibration_data >> 8) );
		}
	}else	{
			printk("[als_P01] Without P03\n");
			return -1;
	}
}

static int al3010_store_calibration_1000(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int err = 0;
	unsigned long val;
	u32 p0_calibration_data = 0;
	p_als_high_calibration_adc = 0;

	if ( g_bIsP01Attached )	{
		printk(DBGMSK_PRX_G2"[als_P01] al3010_calibration_final\n");
		
		if ( (strict_strtoul(buf, 10, &val) < 0) )
			return -EINVAL;
		
		p_als_high_calibration_adc = (int)val;

		printk("[als_P01] al3010 Get Hight calibration adc value : %d\n", p_als_high_calibration_adc );

		/*Calibration operation*/
		g_al3010_light_calibration = 
			p_als_calibration_lux / ( p_als_high_calibration_adc - p_als_low_calibration_adc );

		g_al3010_light_shift_calibration = 
			1000 - ( p_als_high_calibration_adc*g_al3010_light_calibration );

		if ( g_al3010_light_calibration > 255 )
			g_al3010_light_calibration = 255;
		
		printk("[als_P01] al3010 Set shift calibration value : %d\n", g_al3010_light_shift_calibration);

		if ( g_al3010_light_shift_calibration >= 0 )
			p0_calibration_data = ( (0x00 << 24 ) | ((u32)g_al3010_light_shift_calibration << 8) | g_al3010_light_calibration) ;
		else
			p0_calibration_data = ( (0xff << 24 ) | ((u32)g_al3010_light_shift_calibration << 8) | g_al3010_light_calibration) ;

		printk("[als_P01] al3010 Set P03 calibration value : 0x%x\n", (uint32_t)p0_calibration_data);

		err = AX_MicroP_writeKDataOfLightSensor( (uint32_t)p0_calibration_data );
		if ( err == 0 )	{
			printk(DBGMSK_PRX_G2"[als_P01] al3010 calibration success\n");
			return p_als_high_calibration_adc;			
		}
		else	{
			printk("[als_P01] al3010 calibration fail\n");
			return -1;
		}
	}
	else	{
		printk("[als_P01] Without P03\n");
		return -1;
	}

	return p_als_high_calibration_adc;
}

static DEVICE_ATTR(calibration_1000, S_IRWXU | S_IRWXG,
		   al3010_show_calibration_1000, al3010_store_calibration_1000);
#endif


/* mode */
static ssize_t al3010_show_mode(struct device *dev, struct device_attribute *attr, char *buf)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		struct i2c_client *client = to_i2c_client(dev);
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_mode: %d\n", al3010_get_mode(client));

		return sprintf(buf, "%d\n", al3010_get_mode(client));
	}else
		return 0;
}

static ssize_t al3010_store_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		struct i2c_client *client = to_i2c_client(dev);
		unsigned long val;
		int ret;
		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_mode\n");

		if ((strict_strtoul(buf, 10, &val) < 0) || (val > 2))
			return -EINVAL;

		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_mode: %lu\n", val);
		ret = al3010_set_mode(client, val);
		if (ret < 0)
			return ret;

		return count;
	}else
		return 0;
}

static DEVICE_ATTR(mode, S_IWUSR | S_IRUGO,
		   al3010_show_mode, al3010_store_mode);


/* power state */
static ssize_t al3010_show_power_state(struct device *dev, struct device_attribute *attr, char *buf)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		struct i2c_client *client = to_i2c_client(dev);
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_power_state: %d\n", al3010_get_power_state(client));
		return sprintf(buf, "%d\n", al3010_get_power_state(client));
	}else
		return 0;
}

static ssize_t al3010_store_power_state(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		unsigned long val;
		int ret;
		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_power_state\n");

		if ((strict_strtoul(buf, 10, &val) < 0) || (val > 1))
			return -EINVAL;

		printk(DBGMSK_PRX_G2"[als_P01] al3010_store_power_state: %lu\n", val);
		ret = set_als_power_state_of_P01( val );

		return ret ? ret : count;
	}else
		return 0;
}

static DEVICE_ATTR(power_state, S_IWUSR | S_IRUGO,
		   al3010_show_power_state, al3010_store_power_state);


/* adc */
static int al3010_show_lux(struct device *dev,	 struct device_attribute *attr, char *buf)
{
	if ( g_AlsP01ProbeError == 0 && g_bIsP01Attached )	{
		int lux = 0;
		struct i2c_client *client = to_i2c_client(dev);
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_lux\n");

		/* No LUX data if not operational */
		if (al3010_get_power_state(client) != 0x01)
			return -EBUSY;

		lux = al3010_get_adc_value(client);
		printk(DBGMSK_PRX_G2"[als_P01] al3010_show_lux: %d\n", lux );

		return sprintf(buf, "%d\n", lux);
	}else
		return 0;
}

static DEVICE_ATTR(lux, S_IRWXU | S_IRWXG, al3010_show_lux, NULL);

static struct attribute *al3010_attributes[] = {
	&dev_attr_range.attr,
#ifdef ASUS_FACTORY_BUILD
	&dev_attr_calibration_200.attr,
	&dev_attr_calibration_1000.attr,
#endif
	&dev_attr_mode.attr,
	&dev_attr_power_state.attr,
	&dev_attr_lux.attr,
	NULL
};

static const struct attribute_group al3010_attr_group = {
    .name = "al3010",
	.attrs = al3010_attributes,
};

#if 0
static int al3010_init_client(struct i2c_client *client)
{
	struct al3010_data *data = i2c_get_clientdata(client);
	int i;
	printk(DBGMSK_PRX_G2"[als_P01]++al3010_init_client\n");

	/* read all the registers once to fill the cache.
	* if one of the reads fails, we consider the init failed */
	for (i = 0; i < ARRAY_SIZE(data->reg_cache); i++) {
		int v = i2c_smbus_read_byte_data(client, al3010_reg[i]);
		if (v < 0)
			return -ENODEV;

		data->reg_cache[i] = v;
	}

	/* set defaults */
	al3010_set_range(client, 0);
	al3010_set_mode(client, 0);
	//al3010_set_power_state(client, 0);

	printk(DBGMSK_PRX_G2"[als_P01]--al3010_init_client\n");

	return 0;
}
#endif

static void al3010_late_resume_delayed_work(struct work_struct *work)
{
	printk(DBGMSK_PRX_G2"[als_P01] al3010_late_resume, resume ALS\n");
	if (g_HAL_als_switch_on)
		set_als_power_state_of_P01(g_HAL_als_switch_on);
	else
		set_als_power_state_of_P01(g_al3010_suspend_switch_on || g_al3010_switch_on);
	msleep(1);

	/*Release interrupt trigger*/
	if ( g_al3010_suspend_switch_on || g_al3010_switch_on )
		queue_work(al3010light_workqueue ,&al3010_ISR_work);
	else{
		if ( g_microp_ver  >= 0x328 )
			AX_MicroP_getLightsensorADC();
		else
			i2c_smbus_read_byte_data(al3010_client, AL3010_ADC_MSB);
	}
	al3010_interrupt_busy = false;
	msleep(1);
	AX_MicroP_enablePinInterrupt( INTR_EN_ALS_INT, 1 );
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void al3010_early_suspend(struct early_suspend *handler)
{
	printk("[als_P01] ++al3010_early_suspend, als:%d\n", g_al3010_switch_on);
	g_al3010_switch_earlysuspend = 1;

	if( g_bIsP01Attached )
		AX_MicroP_enablePinInterrupt( INTR_EN_ALS_INT, 0 );
	
	if(1 == g_al3010_switch_on) {
		printk(DBGMSK_PRX_G2"[als_P01] al3010_early_suspend, turn off ambient\n");
		set_als_power_state_of_P01(0);
		
	}
	printk("[als_P01] --al3010_early_suspend\n");
}


static void al3010_late_resume(struct early_suspend *handler)
{
	printk("[als_P01] ++al3010_late_resume, als:%d\n", g_al3010_switch_on);

	if( g_bIsP01Attached ){	
		if(1 == g_al3010_switch_earlysuspend) {
			printk(DBGMSK_PRX_G2"[als_P01] al3010_late_resume, P01 attached: %d\n", g_bIsP01Attached);

			if( g_al3010_suspend_switch_on || g_al3010_switch_on ) {
				printk(DBGMSK_PRX_G2"[als_P01] al3010_late_resume, resume ALS +++\n");
				queue_delayed_work(Al3010light_delay_workqueue, &Al3010light_resume_work, 300 );
				//set_als_power_state_of_P01(g_al3010_switch_on);
			}
		}
	}
	g_al3010_switch_earlysuspend=0;
	printk("[als_P01]--al3010_late_resume\n");
}


static struct early_suspend al3010_early_suspend_desc = {
    .level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN,
    .suspend = al3010_early_suspend,
    .resume = al3010_late_resume,
};
#endif

/*
 * I2C layer
 */

static int __devinit al3010_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct al3010_data *data;
	int err = 0;
	g_AlsP01ProbeError = -1;

	printk(DBGMSK_PRX_G2"[als_P01]++al3010_probe\n");

	data = kzalloc(sizeof(struct al3010_data), GFP_KERNEL);
	if (!data)	{
		g_AlsP01ProbeError = -ENOMEM;
		return -ENOMEM;
	}

	// registered as switch device
	err = switch_dev_register(&ls_switch_dev);
	if (err < 0)
		goto exit_kfree;
   
	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))	{
		g_AlsP01ProbeError = -EIO;
		goto exit_kfree;
	}

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);

	//store i2c client structure
	al3010_client = client;

	printk(DBGMSK_PRX_G2"[als_P01]++al3010_probe: create_group\n");
	/* register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &al3010_attr_group);
	if (err)
		goto exit_kfree;

	err = dev_info(&client->dev, "driver version %s enabled\n", DRIVER_VERSION);

	if (err)
		printk(DBGMSK_PRX_G2"[als_P01] ambientdl create sysfile fail.\n");

#ifdef CONFIG_HAS_EARLYSUSPEND
	register_early_suspend( &al3010_early_suspend_desc );
#endif
	g_AlsP01ProbeError = 0;

#ifdef CONFIG_I2C_STRESS_TEST
       i2c_add_test_case(client, "Sensor_Al3010",ARRAY_AND_SIZE(gSensorTestCaseInfo));
#endif

	printk(DBGMSK_PRX_G2"[als_P01]--al3010_probe\n");
	return 0;

exit_kfree:
	g_AlsP01ProbeError = err;
	kfree(data);
	printk("[als_P01]--al3010_probe fail : %d\n", err);
	return err;
}

static int __devexit al3010_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &al3010_attr_group);
	al3010_set_power_state(client, 0);
	switch_dev_unregister(&ls_switch_dev);
	kfree(i2c_get_clientdata(client));

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend( &al3010_early_suspend_desc );
#endif
	return 0;
}

#ifdef CONFIG_PM
static int al3010_suspend(struct i2c_client *client, pm_message_t mesg)
{
    return 0;
}

static int al3010_resume(struct i2c_client *client)
{
    return 0;
}

#else
#define al3010_suspend	NULL
#define al3010_resume		NULL
#endif /* CONFIG_PM */

static const struct i2c_device_id al3010_id[] = {
	{ "al3010", 0 },
	{}
};
MODULE_DEVICE_TABLE(i2c, al3010_id);

static struct i2c_driver al3010_driver = {
	.driver = {
		.name	= AL3010_DRV_NAME,
		.owner	= THIS_MODULE,
	},
	.suspend = al3010_suspend,
	.resume	= al3010_resume,
	.probe	= al3010_probe,
	.remove	= __devexit_p(al3010_remove),
	.id_table = al3010_id,
};

//Disable P01 attached temporarily for 1st ICS check-in
static int lightsensor_p01_mp_event(struct notifier_block *this, unsigned long event, void *ptr);

static struct notifier_block lightsensor_p01_mp_notifier = {
       .notifier_call = lightsensor_p01_mp_event,
        .priority = AL3010_LIGHTSENSOR_MP_NOTIFY,
};

static int __init al3010_init(void)
{
	int err = 0;
	printk("[als_P01] al3010_init++\n");
	
	al3010light_workqueue = create_singlethread_workqueue("al3010light_wq");
	INIT_DELAYED_WORK(&al3010_attached_P02_work, lightsensor_attached_pad_P01);
	INIT_WORK(&al3010_ISR_work, mp_als_interrupt_handler);

	/*For resume and debounce I2C issue*/
	Al3010light_delay_workqueue = create_singlethread_workqueue("Al3010light_delay_wq");
	INIT_DELAYED_WORK( &Al3010light_resume_work, al3010_late_resume_delayed_work);
	INIT_DELAYED_WORK( &Al3010light_debounce_work, mp_als_interrupt_delay_work);


	err = i2c_add_driver(&al3010_driver);
	if(err != 0)	{
		printk("[als_P01] load al3010 driver failed, Error : %d\n",err);
		i2c_del_driver(&al3010_driver);
		printk("[als_P01]i2c_del_driver--\n");
	}

	//Disable P01 attached temporarily for 1st ICS check-in
	register_microp_notifier(&lightsensor_p01_mp_notifier);
	
	printk("[als_P01] al3010_init--\n");
	return err; 
}

static void __exit al3010_exit(void)
{
	destroy_workqueue(al3010light_workqueue);
	destroy_workqueue(Al3010light_delay_workqueue);
	i2c_del_driver(&al3010_driver);
}

// Disable P01 attached temporarily for 1st ICS check-in
static void lightsensor_attached_pad_P01(struct work_struct *work)
{
	int error;
	u32 p0_calibration_data = 0;

	printk(DBGMSK_PRX_G2"[als_P01] lightsensor_attached_pad()++\n");	

	/*Get calibration data*/
	p0_calibration_data = AX_MicroP_readKDataOfLightSensor();

	g_al3010_light_calibration = (p0_calibration_data & 0x00ff);

	if ( (0xff << 24 ) & p0_calibration_data )
		g_al3010_light_shift_calibration = (int)( (p0_calibration_data >> 8) | (0xff << 24 ) );
	else
		g_al3010_light_shift_calibration = (int)(p0_calibration_data >> 8);

	//printk("[als_P01] al3010_get_calibration and shift: %d , %d\n",g_al3010_light_calibration, g_al3010_light_shift_calibration );

	/*Check Calibration value
	if ( g_al3010_light_calibration > 255  || g_al3010_light_calibration <= 0 )
		g_al3010_light_calibration = 85;

	if ( g_al3010_light_shift_calibration >= 255  || g_al3010_light_shift_calibration <= -255 )
		g_al3010_light_shift_calibration = 35;
	*/
		
	printk("[als_P01] al3010 set calibration and shift: %d , %d\n",g_al3010_light_calibration, g_al3010_light_shift_calibration );
			
	g_bIsP01Attached = true;
	if ( g_AlsP01ProbeError != 0 )	{
		error = i2c_add_driver(&al3010_driver);
		if ( error != 0 )	{
			printk("[als_P01] Lightsensor add i2c error!\n");

			printk(DBGMSK_PRX_G0"[als_P01] i2c_del_driver++g_AlsPadProbeError=%d\n", g_AlsP01ProbeError);
			i2c_del_driver(&al3010_driver);
			printk(DBGMSK_PRX_G2"[als_P01]i2c_del_driver--\n");

			//[SCR] Add error handling code if i2c attaching failed
			printk("[als_P01] al3010 attach fails, i2c_del_driver\n");

			//report uevent if prob error
			printk("[als_P01] al3010 prob error, report uevent to framework\n");
			switch_set_state(&ls_switch_dev, P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR);
			g_AlsP01ProbeError = -1;

			return;
		}else	{
			printk(DBGMSK_PRX_G2"[als_P01] P01 Successfully added driver %s\n", al3010_driver.driver.name);
			printk(DBGMSK_PRX_G2"[als_P01] lightsensor_attached_pad(), driver already added\n");
			g_AlsP01ProbeError = 0;
		}
	}

	if (g_HAL_als_switch_on) {
		g_al3010_suspend_switch_on = 0;

		/*Switch Phone light value to Pad*/
		g_last_al3010_light = g_cm36283_light;
		
		/*Wait al3010 stable*/
		queue_delayed_work(Al3010light_delay_workqueue, &Al3010light_resume_work, 100 );

		/*
		msleep(600);
		error = set_als_power_state_of_P01(1);
		
		if (error == 0)	{
			switch_set_state(&ls_switch_dev, P01_EVENT_NOTIFY_LIGHTSENSOR_NO_ERROR);
			printk(DBGMSK_PRX_G2"[als_P01] lightsensor_attached_pad, attached! al3010 get switch\n");
		}else	{
			switch_set_state(&ls_switch_dev, P01_EVENT_NOTIFY_LIGHTSENSOR_ERROR);
			printk("[als_P01] lightsensor_attached_pad, attached! al3010 get switch fail--\n");
			return;
		}
		*/
	}

	printk(DBGMSK_PRX_G2"[als_P01] lightsensor_attached_pad()--\n");

	return;
}
EXPORT_SYMBOL(lightsensor_attached_pad_P01);

int lightsensor_detached_pad_P01(void)
{
	printk(DBGMSK_PRX_G2"[als_P01] lightsensor_detached_pad_P01()++\n");

	//turn al3010 off
	if( g_al3010_switch_on ) {
		set_als_power_state_of_P01(0);
		g_cm36283_light = g_al3010_light;
		printk(DBGMSK_PRX_G2"[als_P01] lightsensor_detached_pad, switch to cm36238 : %d lux\n", g_cm36283_light);
		g_al3010_switch_on = false;
	}

	g_bIsP01Attached = false;

	printk(DBGMSK_PRX_G2"[als_P01] lightsensor_detached_pad_P01()--\n");

	return 0;
}
EXPORT_SYMBOL(lightsensor_detached_pad_P01);

static int lightsensor_p01_mp_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	switch (event) {
		case P01_ADD:
			printk(DBGMSK_PRX_G2"[als_P01][MicroP] P01_ADD \r\n");                
			queue_delayed_work(al3010light_workqueue, &al3010_attached_P02_work, HZ );
			return NOTIFY_DONE;

		case P01_REMOVE:
			printk(DBGMSK_PRX_G2"[als_P01][MicroP] P01_REMOVE \r\n");
			lightsensor_detached_pad_P01();
			return NOTIFY_DONE;

		case P01_LIGHT_SENSOR:
			printk("[als_P01][MicroP] P01_ISR \r\n");
			if (work_pending(&al3010_ISR_work)){
				printk("[als_P01] Begin cancel work \r\n");
				cancel_work_sync(&al3010_ISR_work);
				printk("[als_P01] Finish cancel work \r\n");
			}
			if ( !al3010_interrupt_busy )
				queue_work(al3010light_workqueue ,&al3010_ISR_work);
			else
				printk(DBGMSK_PRX_G2"[als_P01] Inerrupt busy \r\n");

			return NOTIFY_DONE;
		default:
			return NOTIFY_DONE;
		}
}



MODULE_AUTHOR("ASUS");
MODULE_DESCRIPTION("test version v1.0");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRIVER_VERSION);

module_init(al3010_init);
module_exit(al3010_exit);

