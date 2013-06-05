
//                     ASUSTek Computer Inc.
//         Copyright (c) 2010 ASUSTek Computer inc, Taipei.

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <mach/gpio.h>

static struct i2c_client *p03_scaler_info_client;
unsigned char g_scaler_ver;

bool read_scaler_version(unsigned char *ver)
{
    unsigned char buf[5];
    int address = 0x6E;
    unsigned char value[11];
    int retry;

	int scaler_err1 = 0, scaler_err2 = 0;

    buf[0] = 0x51;
    buf[1] = 0x82;  
    buf[2] = 0x01;
    buf[3] = 0xE1;      //VCP code:FW version
    buf[4] = address ^ buf[0] ^ buf[1] ^ buf[2] ^ buf[3];

	for(retry=0; retry<5; retry++)
	{
		buf[4] = address ^ buf[0] ^ buf[1] ^ buf[2] ^ buf[3];
		memset(value, 0x0, 11);
		
		scaler_err1 =  i2c_master_send(p03_scaler_info_client, buf, 5);
		msleep(200);    
		scaler_err2 =  i2c_master_recv(p03_scaler_info_client, value ,11);

		if( (scaler_err1 < 0) || (scaler_err2 < 0)  || (value[4] != 0xE1))
		{
			*ver = 0;
			printk("[p03_scaler_info]read scaler version fail, retry = %d !!\n\n", retry);
		}
		else
		{
			*ver = value[9];
			
			if(value[9] <= 0 || value[9] >=255)
			{
				printk("[p03_scaler_info]read scaler version fail, retry = %d !!\n\n", retry);
			}
			else
			{
				break;
			}
		}
	}

	if(retry >= 5){
		return false;
	}
	else{
		return true;    
	}
}

static bool switch_backlight_and_panel(int on)
{
    unsigned char buf[7];
    int ret;
    int address = 0x6E;
    //int i;
    buf[0] = 0X51;//Source address
    buf[1] = 0x84;//lenght
    buf[2] = 0x03;//set vcp feature
    buf[3] = 0xE3;//vcp opcode
    buf[4] = 0x00;//high byte
    buf[5] = on;//low byte
    buf[6] = address ^ buf[0] ^ buf[1] ^ buf[2] ^ buf[3] ^ buf[4] ^ buf[5] ;
    //msleep(100);

    ret = i2c_master_send(p03_scaler_info_client, buf, 7);
    if (ret < 0)
        return ret;

    return 0;
}

extern int set_gsbi1_i2c_clk(int clk_freq);

static int scaler_ver_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    int len=0;

	set_gsbi1_i2c_clk(100000);
   
	if (read_scaler_version(&g_scaler_ver) == 0)
	{
		printk("[p03_scaler_info]read scaler version fail !!\n\n");
		g_scaler_ver = 0;
	}
	len=sprintf(page, "%d\n", g_scaler_ver);

	set_gsbi1_i2c_clk(400000);

	return len;
}

static int scaler_ver_write_proc(struct file *filp, const char __user *buff, unsigned long len, void *data)
{
	return 0;
}

static int scaler_panel_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	return 0;
}

static int scaler_panel_write_proc(struct file *filp, const char __user *buff, unsigned long len, void *data)
{
	char msg[16];
	if (len > 16)
		len = 16;

	if (copy_from_user(msg, buff, len))
		return -EFAULT;

     switch (msg[0]) {
	 case '0':
		 switch_backlight_and_panel(0);
		 break;
	 case '1':
		 switch_backlight_and_panel(1);
		 break;
     default:
		 break;
     }

	return len;
}

static int p03_scaler_info_probe(struct i2c_client *client,
            const struct i2c_device_id *id)
{
	struct proc_dir_entry *entry;
    
	printk("[p03_scaler_info] p03_scaler_info_probe\n");
	p03_scaler_info_client = client;
	
	entry = create_proc_entry("scaler_ver", 0666, NULL);
	if (entry == NULL) {
		printk("[p03_scaler_info] create_proc_entry fail\r\n");
	}
	else {
		entry->read_proc = scaler_ver_read_proc;
		entry->write_proc = scaler_ver_write_proc;
	}

	entry = create_proc_entry("scaler_panel", 0666, NULL);
	if (entry == NULL) {
		printk("[p03_scaler_info] create_proc_entry fail\r\n");
	}
	else {
		entry->read_proc = scaler_panel_read_proc;
		entry->write_proc = scaler_panel_write_proc;
	}

    return 0;
}

static const struct i2c_device_id p03_scaler_info_id[] = {
    { "p03_scaler_info", 0 },
    { }
};

static struct i2c_driver p03_scaler_info_i2c_driver = {
    .driver = {
        .name   = "p03_scaler_info",
    },
    .id_table   = p03_scaler_info_id,
    .probe      = p03_scaler_info_probe,
};

static int __init p03_scaler_info_init(void)
{
    printk("[p03_scaler_info] p03_scaler_info_init\n");
    return i2c_add_driver(&p03_scaler_info_i2c_driver);
}

static void __exit p03_scaler_info_exit(void)
{
    printk("[p03_scaler_info] p03_scaler_info_exit\n");
    i2c_del_driver(&p03_scaler_info_i2c_driver);
}

module_init(p03_scaler_info_init);
module_exit(p03_scaler_info_exit);

MODULE_DESCRIPTION("p03 scaler info driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lenter_Chang");




