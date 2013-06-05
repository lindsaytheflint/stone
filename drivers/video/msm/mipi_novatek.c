/* Copyright (c) 2010-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifdef CONFIG_SPI_QUP
#include <linux/spi/spi.h>
#endif
#include <linux/leds.h>
#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_novatek.h"
#include "mdp4.h"

#include <linux/kernel.h> //Louis: for A80 porting

//+++ ASUS_BSP: for JB-porting
#include <linux/mutex.h>
static char bl_value[] = {0x51, 0x64};      //write brightness
struct dcs_cmd_req bl_cmdreq;
extern int g_fb0_dsi_block;
//--- ASUS_BSP: for JB-porting

static struct mipi_dsi_panel_platform_data *mipi_novatek_pdata;

static struct dsi_buf novatek_tx_buf;
static struct dsi_buf novatek_rx_buf;
static int mipi_novatek_lcd_init(void);

static int wled_trigger_initialized;

#define MIPI_DSI_NOVATEK_SPI_DEVICE_NAME	"dsi_novatek_3d_panel_spi"
#define HPCI_FPGA_READ_CMD	0x84
#define HPCI_FPGA_WRITE_CMD	0x04

#ifdef CONFIG_SPI_QUP
static struct spi_device *panel_3d_spi_client;

static void novatek_fpga_write(uint8 addr, uint16 value)
{
	char tx_buf[32];
	int  rc;
	struct spi_message  m;
	struct spi_transfer t;
	u8 data[4] = {0x0, 0x0, 0x0, 0x0};

	if (!panel_3d_spi_client) {
		pr_err("%s panel_3d_spi_client is NULL\n", __func__);
		return;
	}
	data[0] = HPCI_FPGA_WRITE_CMD;
	data[1] = addr;
	data[2] = ((value >> 8) & 0xFF);
	data[3] = (value & 0xFF);

	memset(&t, 0, sizeof t);
	memset(tx_buf, 0, sizeof tx_buf);
	t.tx_buf = data;
	t.len = 4;
	spi_setup(panel_3d_spi_client);
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	rc = spi_sync(panel_3d_spi_client, &m);
	if (rc)
		pr_err("%s: SPI transfer failed\n", __func__);

	return;
}

static void novatek_fpga_read(uint8 addr)
{
	char tx_buf[32];
	int  rc;
	struct spi_message  m;
	struct spi_transfer t;
	struct spi_transfer rx;
	char rx_value[2];
	u8 data[4] = {0x0, 0x0};

	if (!panel_3d_spi_client) {
		pr_err("%s panel_3d_spi_client is NULL\n", __func__);
		return;
	}

	data[0] = HPCI_FPGA_READ_CMD;
	data[1] = addr;

	memset(&t, 0, sizeof t);
	memset(tx_buf, 0, sizeof tx_buf);
	memset(&rx, 0, sizeof rx);
	memset(rx_value, 0, sizeof rx_value);
	t.tx_buf = data;
	t.len = 2;
	rx.rx_buf = rx_value;
	rx.len = 2;
	spi_setup(panel_3d_spi_client);
	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	spi_message_add_tail(&rx, &m);

	rc = spi_sync(panel_3d_spi_client, &m);
	if (rc)
		pr_err("%s: SPI transfer failed\n", __func__);
	else
		pr_info("%s: rx_value = 0x%x, 0x%x\n", __func__,
						rx_value[0], rx_value[1]);

	return;
}

static int __devinit panel_3d_spi_probe(struct spi_device *spi)
{
	panel_3d_spi_client = spi;
	return 0;
}
static int __devexit panel_3d_spi_remove(struct spi_device *spi)
{
	panel_3d_spi_client = NULL;
	return 0;
}
static struct spi_driver panel_3d_spi_driver = {
	.probe         = panel_3d_spi_probe,
	.remove        = __devexit_p(panel_3d_spi_remove),
	.driver		   = {
		.name = "dsi_novatek_3d_panel_spi",
		.owner  = THIS_MODULE,
	}
};

#else

static void novatek_fpga_write(uint8 addr, uint16 value)
{
	return;
}

static void novatek_fpga_read(uint8 addr)
{
	return;
}

#endif


/* novatek blue panel */

#ifdef NOVETAK_COMMANDS_UNUSED
static char display_config_cmd_mode1[] = {
	/* TYPE_DCS_LWRITE */
	0x2A, 0x00, 0x00, 0x01,
	0x3F, 0xFF, 0xFF, 0xFF
};

static char display_config_cmd_mode2[] = {
	/* DTYPE_DCS_LWRITE */
	0x2B, 0x00, 0x00, 0x01,
	0xDF, 0xFF, 0xFF, 0xFF
};

static char display_config_cmd_mode3_666[] = {
	/* DTYPE_DCS_WRITE1 */
	0x3A, 0x66, 0x15, 0x80 /* 666 Packed (18-bits) */
};

static char display_config_cmd_mode3_565[] = {
	/* DTYPE_DCS_WRITE1 */
	0x3A, 0x55, 0x15, 0x80 /* 565 mode */
};

static char display_config_321[] = {
	/* DTYPE_DCS_WRITE1 */
	0x66, 0x2e, 0x15, 0x00 /* Reg 0x66 : 2E */
};

static char display_config_323[] = {
	/* DTYPE_DCS_WRITE */
	0x13, 0x00, 0x05, 0x00 /* Reg 0x13 < Set for Normal Mode> */
};

static char display_config_2lan[] = {
	/* DTYPE_DCS_WRITE */
	0x61, 0x01, 0x02, 0xff /* Reg 0x61 : 01,02 < Set for 2 Data Lane > */
};

static char display_config_exit_sleep[] = {
	/* DTYPE_DCS_WRITE */
	0x11, 0x00, 0x05, 0x80 /* Reg 0x11 < exit sleep mode> */
};

static char display_config_TE_ON[] = {
	/* DTYPE_DCS_WRITE1 */
	0x35, 0x00, 0x15, 0x80
};

static char display_config_39H[] = {
	/* DTYPE_DCS_WRITE */
	0x39, 0x00, 0x05, 0x80
};

static char display_config_set_tear_scanline[] = {
	/* DTYPE_DCS_LWRITE */
	0x44, 0x00, 0x00, 0xff
};

static char display_config_set_twolane[] = {
	/* DTYPE_DCS_WRITE1 */
	0xae, 0x03, 0x15, 0x80
};

static char display_config_set_threelane[] = {
	/* DTYPE_DCS_WRITE1 */
	0xae, 0x05, 0x15, 0x80
};

#else

static char sw_reset[2] = {0x01, 0x00}; /* DTYPE_DCS_WRITE */
static char enter_sleep[2] = {0x10, 0x00}; /* DTYPE_DCS_WRITE */
static char exit_sleep[2] = {0x11, 0x00}; /* DTYPE_DCS_WRITE */
static char display_off[2] = {0x28, 0x00}; /* DTYPE_DCS_WRITE */
static char display_on[2] = {0x29, 0x00}; /* DTYPE_DCS_WRITE */



static char rgb_888[2] = {0x3A, 0x77}; /* DTYPE_DCS_WRITE1 */

#if defined(NOVATEK_TWO_LANE)
static char set_num_of_lanes[2] = {0xae, 0x03}; /* DTYPE_DCS_WRITE1 */
#else  /* 1 lane */
static char set_num_of_lanes[2] = {0xae, 0x01}; /* DTYPE_DCS_WRITE1 */
#endif
/* commands by Novatke */
static char novatek_f4[2] = {0xf4, 0x55}; /* DTYPE_DCS_WRITE1 */
static char novatek_8c[16] = { /* DTYPE_DCS_LWRITE */
	0x8C, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x08, 0x08, 0x00, 0x30, 0xC0, 0xB7, 0x37};
static char novatek_ff[2] = {0xff, 0x55 }; /* DTYPE_DCS_WRITE1 */

static char set_width[5] = { /* DTYPE_DCS_LWRITE */
	0x2A, 0x00, 0x00, 0x02, 0x1B}; /* 540 - 1 */
static char set_height[5] = { /* DTYPE_DCS_LWRITE */
	0x2B, 0x00, 0x00, 0x03, 0xBF}; /* 960 - 1 */
#endif

static char led_pwm2[2] = {0x53, 0x24}; /* DTYPE_DCS_WRITE1 */
static char led_pwm3[2] = {0x55, 0x00}; /* DTYPE_DCS_WRITE1 */

static struct dsi_cmd_desc novatek_video_on_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 50,
		sizeof(sw_reset), sw_reset},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_on), display_on},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(set_num_of_lanes), set_num_of_lanes},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(rgb_888), rgb_888},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(led_pwm2), led_pwm2},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(led_pwm3), led_pwm3},
};

static struct dsi_cmd_desc novatek_cmd_on_cmds[] = {
	{DTYPE_DCS_WRITE, 1, 0, 0, 50,
		sizeof(sw_reset), sw_reset},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_on), display_on},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 50,
		sizeof(novatek_f4), novatek_f4},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 50,
		sizeof(novatek_8c), novatek_8c},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 50,
		sizeof(novatek_ff), novatek_ff},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(set_num_of_lanes), set_num_of_lanes},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 50,
		sizeof(set_width), set_width},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 50,
		sizeof(set_height), set_height},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 10,
		sizeof(rgb_888), rgb_888},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 1,
		sizeof(led_pwm2), led_pwm2},
	{DTYPE_DCS_WRITE1, 1, 0, 0, 1,
		sizeof(led_pwm3), led_pwm3},
};

static struct dsi_cmd_desc novatek_display_off_cmds[] = {
    {DTYPE_DCS_WRITE1,1, 0, 0, 10, sizeof(bl_value), bl_value},   //ASUS_BSP:Louis
	{DTYPE_DCS_WRITE, 1, 0, 0, 10,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 1, 0, 0, 120,
		sizeof(enter_sleep), enter_sleep}
};

//+++ ASUS_BSP for A68 sharp panel : miniporting
struct dcs_cmd_req cmdreq;  //ASUS_BSP: for JB porting
struct msm_fb_data_type *g_mfd;
static bool cabc_cmd_supend = false;
static int g_cabc_mode = 3;

//Mickey+++
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
static char MTP_no_reload_cmd[] = {0xFB,0x01};
static char cmd2_page0[]= {0xFF, 0x01};
static char cmd2_page1[]= {0xFF, 0x02};
static char cmd2_page2[]= {0xFF, 0x03};

static char enter_testmode[] = {0xFF,0xEE};
static char init_testmode1[] = {0x26,0x08};
static char init_testmode2[] = {0x26,0x00};
static char init_testmode3[] = {0xFF,0x05};
static char init_testmode4[] = {0xFB,0x01};
static char init_testmode5[] = {0x28,0x01};
static char init_testmode6[] = {0x2F,0x02};
static char init_testmode7[] = {0xFF,0x00};
static char init_testmode8[] = {0x12,0x50};
static char init_testmode9[] = {0x13,0x02};
static char init_testmode10[] = {0x6A,0x60};

static char init_cmd002[] = {0xC2,0x03};
static char init_cmd003[] = {0xBA,0x02};  //3 lane

//static char IE_mode[] = {0x25,0x40};        //smart mode

static char init_pwmfeq[] = {0x09, 0x20};   //Focs 85.9k
static char init_pwmdiv[] = {0x0A, 0x03};   //div 3
#endif
//Mickey---

static char init_cmd001[] = {0xFF,0x00};
static char init_cabc1[] = {0x53, 0x2C};    //BL ctrl & DD ctrl
static char IE_CABC[] = {0x55, 0x83};       //IE level / CABC mode

static char cmd2_page3[]= {0xFF, 0x04};
static char dimming_ctrl[]  = {0x05, 0x36};  //moving & still mode 128 steps
static char abc_ctrl[]  = {0x06, 0x01};    //2 frame

static struct dsi_cmd_desc novatek_brightness_set[] = {
    {DTYPE_DCS_WRITE1, 1, 0, 0, 10, sizeof(bl_value), bl_value},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(init_cabc1), init_cabc1},
};

static struct dsi_cmd_desc novatek_brightness_set_suspend[] = {
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(init_cabc1), init_cabc1},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(bl_value), bl_value},
};

static struct dsi_cmd_desc panel_display_on[] = {
    //{DTYPE_DCS_WRITE1, 1, 0, 0,  0, sizeof(bl_value), bl_value},
    //{DTYPE_DCS_WRITE1, 1, 0, 0,  0, sizeof(init_cabc1), init_cabc1},
    {DTYPE_DCS_WRITE1, 1, 0, 0,  0, sizeof(display_on), display_on},
};

static struct dsi_cmd_desc set_cabc_cmd[] = {
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(IE_CABC), IE_CABC},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(cmd2_page3),cmd2_page3},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(dimming_ctrl),dimming_ctrl},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(abc_ctrl),abc_ctrl},
    {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(init_cmd001),init_cmd001},
};

#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
static struct dsi_cmd_desc a68_init_cmds[] = {
{DTYPE_DCS_WRITE1,1, 0, 0, 30, sizeof(enter_testmode),enter_testmode},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode1),init_testmode1},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode2),init_testmode2},
//++ set MTP no-reload afer sleep out
{DTYPE_DCS_WRITE1,1, 0, 0, 35, sizeof(init_cmd001),init_cmd001},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page0),cmd2_page0},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page1),cmd2_page1},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page2),cmd2_page2},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page3),cmd2_page3},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(enter_testmode),enter_testmode},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(MTP_no_reload_cmd),MTP_no_reload_cmd},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_cmd001),init_cmd001},
//-- set MTP no-reload afer sleep out
{DTYPE_DCS_WRITE1,1, 0, 0, 35, sizeof(init_cmd002),init_cmd002},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode3),init_testmode3},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode4),init_testmode4},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode5),init_testmode5},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode6),init_testmode6},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode7),init_testmode7},
{DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(exit_sleep), exit_sleep},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_cmd003),init_cmd003},
{DTYPE_DCS_WRITE1,1, 0, 0, 120,sizeof(enter_testmode),enter_testmode},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode8),init_testmode8},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode9),init_testmode9},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_testmode10),init_testmode10},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_cmd001),init_cmd001},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(bl_value),bl_value},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_cabc1),init_cabc1},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(IE_CABC),IE_CABC},
//+++ color enhacement
//{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page2), cmd2_page2},
//{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(IE_mode),IE_mode},
//--- color enhacement
//+++ CABC
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(cmd2_page3),cmd2_page3},
{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(dimming_ctrl),dimming_ctrl},
{DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(abc_ctrl),abc_ctrl},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_pwmfeq),init_pwmfeq},
{DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(init_pwmdiv),init_pwmdiv},
//--- CABC
{DTYPE_DCS_WRITE1,1, 0, 0, 10, sizeof(init_cmd001),init_cmd001},
{DTYPE_DCS_WRITE, 1, 0, 0, 10, sizeof(display_on), display_on},
};
#endif

static struct dsi_cmd_desc novatek_display_on[] = {
    {DTYPE_DCS_WRITE, 1, 0, 0, 105, sizeof(exit_sleep), exit_sleep},
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
    {DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(bl_value),bl_value},
    {DTYPE_DCS_WRITE, 1, 0, 0, 10, sizeof(display_on), display_on},
#endif
};
//--- ASUS_BSP for A68 sharp panel : miniporting

//+++ ASUS_BSP: read config register for ESD test
#define NOVATEK_REG_FILE        "/data/.tmp/a68_display_reg.nv"

static char dsi_num_err_r[2] = {0x05, 0x00};
static char power_mode_r[2] = {0x0A, 0x00};
static char addr_mode_r[2] = {0x0B, 0x00};
static char pixel_mode_r[2] = {0x0C, 0x00};
static char display_mode_r[2] = {0x0D, 0x00};
static char signal_mode_r[2] = {0x0E, 0x00};
static char self_diagnostic_r[2] = {0x0F, 0x00};
static char memory_start_r[2] = {0x2E, 0x00};
static char bl_value_r[2] = {0x52, 0x00}; 
static char init_cabc1_r[2] = {0x54, 0x00};
static char IE_CABC_r[2] = {0x56, 0x00}; 

static struct dsi_cmd_desc dump_novatek_register_cmd[] = {
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(dsi_num_err_r), dsi_num_err_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(power_mode_r), power_mode_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(addr_mode_r), addr_mode_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(pixel_mode_r), pixel_mode_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(display_mode_r), display_mode_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(signal_mode_r), signal_mode_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(self_diagnostic_r), self_diagnostic_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(memory_start_r), memory_start_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(bl_value_r), bl_value_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(init_cabc1_r), init_cabc1_r},
    {DTYPE_DCS_READ, 1, 0, 1, 3, sizeof(IE_CABC_r), IE_CABC_r},
};

static bool write_lcd_reg_value(char addr, uint32 value)
{
    struct file *fp = NULL; 
    loff_t pos_lsts = 0;
    char write_dumpval[2];
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fp = filp_open(NOVATEK_REG_FILE, O_RDWR|O_CREAT|O_APPEND, 0644);
    if(IS_ERR_OR_NULL(fp)) {
        printk("[Display] write lcd register open (%s) fail\n", NOVATEK_REG_FILE);
        return false;
    }
    sprintf(write_dumpval, "0x%x: 0x%x\n", addr, value);
    fp->f_op->write(fp, write_dumpval, strlen(write_dumpval), &pos_lsts);

    pos_lsts = 0;

    set_fs(old_fs);
    filp_close(fp, NULL);

    return true;
}

static uint32 dump_mipi_novatek_register(struct msm_fb_data_type *mfd)
{
    struct dsi_buf *rp, *tp;
    //struct dsi_cmd_desc *cmd;
    uint32 *lp;
    int i;
    uint32 value;
    char addr;
    mutex_lock(&mfd->dma->ov_mutex);

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND) {
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND\n", __func__);
        mutex_unlock(&mfd->dma->ov_mutex);
        return -1;
    }

    tp = &novatek_tx_buf;
    rp = &novatek_rx_buf;

    for(i=0; i<ARRAY_SIZE(dump_novatek_register_cmd); i++) 
    {
        cmdreq.cmds = &dump_novatek_register_cmd[i];
        cmdreq.cmds_cnt = 1;
        cmdreq.flags = CMD_REQ_RX;
        cmdreq.rlen = 3;

        mipi_dsi_clk_cfg(1);
        mipi_dsi_cmds_rx_new(tp, rp, &cmdreq, cmdreq.rlen);
        mipi_dsi_clk_cfg(0);

        lp = (uint32 *)rp->data;
        value = (uint32) *lp;
        addr = (char) (dump_novatek_register_cmd[i].payload)[0];
        write_lcd_reg_value(addr, value);

        printk("[%s] novatek register addr (0x%x) = (0x%x)\n", __func__, addr, *lp);
    }
    mutex_unlock(&mfd->dma->ov_mutex);
    return *lp;
}
//--- ASUS_BSP: read config register for ESD test

//+++ for BMMI test
static struct dsi_cmd_desc read_display_pwrmode_cmd = {
    DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(power_mode_r), power_mode_r,
};
static uint32 g_display_sts = 0;
static uint32 lcd_pwrmode_read(struct msm_fb_data_type *mfd)
{
    struct dsi_buf *rp, *tp;
    uint32 *lp;
    mutex_lock(&mfd->dma->ov_mutex);

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND) {
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND\n", __func__);
        g_display_sts = 0;
        mutex_unlock(&mfd->dma->ov_mutex);
        return g_display_sts;
    }

    tp = &novatek_tx_buf;
    rp = &novatek_rx_buf;

    cmdreq.cmds = &read_display_pwrmode_cmd;
    cmdreq.cmds_cnt = 1;
    cmdreq.flags = CMD_REQ_RX;
    cmdreq.rlen = 3;

    mipi_dsi_clk_cfg(1);
    mipi_dsi_cmds_rx_new(tp, rp, &cmdreq, cmdreq.rlen);
    mipi_dsi_clk_cfg(0);

    lp = (uint32 *)rp->data;
    g_display_sts |= (((uint32) *lp) & 0x04) >> 2;    //lcd on/off

    printk("[Display][BMMI] LCD status (%d)\n", g_display_sts);

    mutex_unlock(&mfd->dma->ov_mutex);
    return g_display_sts;
}
//--- for BMMI test

static char manufacture_id[2] = {0x04, 0x00}; /* DTYPE_DCS_READ */

static struct dsi_cmd_desc novatek_manufacture_id_cmd = {
	DTYPE_DCS_READ, 1, 0, 1, 5, sizeof(manufacture_id), manufacture_id};

//struct dcs_cmd_req cmdreq;   //ASUS_BSP: Louis
static u32 manu_id;

static void mipi_novatek_manufature_cb(u32 data)
{
	manu_id = data;
	pr_info("%s: manufature_id=%x\n", __func__, manu_id);
}

static uint32 mipi_novatek_manufacture_id(struct msm_fb_data_type *mfd)
{
	cmdreq.cmds = &novatek_manufacture_id_cmd;
	cmdreq.cmds_cnt = 1;
	cmdreq.flags = CMD_REQ_RX | CMD_REQ_COMMIT;
	cmdreq.rlen = 3;
	cmdreq.cb = mipi_novatek_manufature_cb;
	mipi_dsi_cmdlist_put(&cmdreq);

	return manu_id;
}

static int fpga_addr;
static int fpga_access_mode;
static bool support_3d;

static void mipi_novatek_3d_init(int addr, int mode)
{
	fpga_addr = addr;
	fpga_access_mode = mode;
}

static void mipi_dsi_enable_3d_barrier(int mode)
{
	void __iomem *fpga_ptr;
	uint32_t ptr_value = 0;

	if (!fpga_addr && support_3d) {
		pr_err("%s: fpga_addr not set. Failed to enable 3D barrier\n",
					__func__);
		return;
	}

	if (fpga_access_mode == FPGA_SPI_INTF) {
		if (mode == LANDSCAPE)
			novatek_fpga_write(fpga_addr, 1);
		else if (mode == PORTRAIT)
			novatek_fpga_write(fpga_addr, 3);
		else
			novatek_fpga_write(fpga_addr, 0);

		mb();
		novatek_fpga_read(fpga_addr);
	} else if (fpga_access_mode == FPGA_EBI2_INTF) {
		fpga_ptr = ioremap_nocache(fpga_addr, sizeof(uint32_t));
		if (!fpga_ptr) {
			pr_err("%s: FPGA ioremap failed."
				"Failed to enable 3D barrier\n",
						__func__);
			return;
		}

		ptr_value = readl_relaxed(fpga_ptr);
		if (mode == LANDSCAPE)
			writel_relaxed(((0xFFFF0000 & ptr_value) | 1),
								fpga_ptr);
		else if (mode == PORTRAIT)
			writel_relaxed(((0xFFFF0000 & ptr_value) | 3),
								fpga_ptr);
		else
			writel_relaxed((0xFFFF0000 & ptr_value),
								fpga_ptr);

		mb();
		iounmap(fpga_ptr);
	} else
		pr_err("%s: 3D barrier not configured correctly\n",
					__func__);
}
// +++ ASUS_BSP: miniporting
bool g_panelOn = false;
bool bl_dimming = true;
static int g_bl_value = 0x64;
static int g_displayOn = false;

int sharp_set_brightness(int value)
{
    struct mipi_panel_info *mipi;

    mipi  = &g_mfd->panel_info.mipi;

    printk("[BL] brightness value = (%d)\n", value);
    bl_value[1] = (char) value;

    if (value > 0) {
        g_bl_value = value;
    }

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND || g_fb0_dsi_block) {
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND, g_fb0_dsi_block(%d)\n", __func__, g_fb0_dsi_block);
        return -1;
    }

    bl_cmdreq.cmds = novatek_brightness_set;
    bl_cmdreq.cmds_cnt = ARRAY_SIZE(novatek_brightness_set);

    if (value == 0 && bl_dimming == true) {
        novatek_brightness_set_suspend[0].payload[1] = 0x24;    //disable dimming ctrl
        bl_dimming = false;
        printk("[Display] turn off backlight dimming ctrl\n");

        bl_cmdreq.cmds = novatek_brightness_set_suspend;
        bl_cmdreq.cmds_cnt = ARRAY_SIZE(novatek_brightness_set_suspend);
    }
    else if (value != 0 && bl_dimming == false) {
        novatek_brightness_set[1].payload[1] = 0x2C;
        bl_dimming = true;
        printk("[Display] turn on backlight dimming ctrl\n");
    }

    bl_cmdreq.flags = CMD_REQ_COMMIT;
    bl_cmdreq.rlen = 0;
    bl_cmdreq.cb = NULL;

    mipi_dsi_cmdlist_put(&bl_cmdreq);

    return 0;
}

void sharp_panel_on(void)
{
    struct mipi_panel_info *mipi;
    mipi  = &g_mfd->panel_info.mipi;

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND) {
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND\n", __func__);
        return;
    }

    cmdreq.cmds = panel_display_on;
    cmdreq.cmds_cnt = ARRAY_SIZE(panel_display_on);
    cmdreq.flags = CMD_REQ_COMMIT;
    cmdreq.rlen = 0;
    cmdreq.cb = NULL;
    mipi_dsi_cmdlist_put(&cmdreq);

    if (bl_dimming == false) {
        sharp_set_brightness(g_bl_value);
    }

    if (cabc_cmd_supend) {
        sharp_set_cabc(g_cabc_mode);
    }

    g_panelOn = true;//Mickey+++, make sure the flag be set only when display on
    printk("[Display] display on due to screen update , g_panelOn=%d\n",g_panelOn);
}
EXPORT_SYMBOL(sharp_panel_on);
// --- ASUS_BSP: miniporting

//+++ ASUS_BSP: for A80 porting
static char a80_write_brightness[3] = {0x51, 0x00, 0x60};
static char a80_ctrl_display[2] = {0x53, 0x24};

static struct dsi_cmd_desc renesas_brightness_set[] = {
    {DTYPE_DCS_LWRITE, 1, 0, 0, 10, sizeof(a80_write_brightness), a80_write_brightness},
    {DTYPE_DCS_LWRITE,1, 0, 0, 0, sizeof(a80_ctrl_display), a80_ctrl_display},
};

int renesas_set_brightness(int value1, int value2)
{
    struct mipi_panel_info *mipi;

    mipi  = &g_mfd->panel_info.mipi;

    a80_write_brightness[1] = (char) value1;
    a80_write_brightness[2] = (char) value2;

    if (value2 > 0) {
        g_bl_value = value2;
    }

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND) {
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND\n", __func__);
        return -1;
    }

    bl_cmdreq.cmds = renesas_brightness_set;
    bl_cmdreq.cmds_cnt = ARRAY_SIZE(renesas_brightness_set);
    bl_cmdreq.flags = CMD_REQ_COMMIT;
    bl_cmdreq.rlen = 0;
    bl_cmdreq.cb = NULL;

    mipi_dsi_cmdlist_put(&bl_cmdreq);

    return 0;
}

static struct dsi_cmd_desc a80_panel_init_cmds[] = {
    {DTYPE_DCS_LWRITE,1, 0, 0, 0, sizeof(a80_write_brightness), a80_write_brightness},
    {DTYPE_DCS_WRITE1,1, 0, 0, 0, sizeof(a80_ctrl_display), a80_ctrl_display},
    {DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(exit_sleep), exit_sleep},
    {DTYPE_DCS_WRITE, 1, 0, 0, 0, sizeof(display_on), display_on},
};
//--- ASUS_BSP: for A80 porting

static int mipi_novatek_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
	struct msm_panel_info *pinfo;
	static bool bFirst = true; // +++ ASUS_BSP : miniporting

	mfd = platform_get_drvdata(pdev);
	if (!mfd)
    {
        printk("%s,-ENODEV\n",__func__);
		return -ENODEV;
    }
	if (mfd->key != MFD_KEY)
    {
        printk("%s,-EINVAL,key=0x%x\n",__func__,mfd->key);
		return -EINVAL;
    }

	pinfo = &mfd->panel_info;
	if (pinfo->is_3d_panel)
		support_3d = TRUE;

	mipi  = &mfd->panel_info.mipi;

//ASUS_BSP: miniporting +++
    cmdreq.flags = CMD_REQ_COMMIT;
    cmdreq.rlen = 0;
    cmdreq.cb = NULL;

    if (bFirst) {
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
        if (g_A68_hwID < A80_EVB)
        {
            cmdreq.cmds = a68_init_cmds;
            cmdreq.cmds_cnt = ARRAY_SIZE(a68_init_cmds);

            mipi_dsi_cmdlist_put(&cmdreq);
        }
#endif
        if (g_A68_hwID >= A80_EVB)
        {
            printk("[Display] A80 first initial command\n");

            cmdreq.cmds = a80_panel_init_cmds;
            cmdreq.cmds_cnt = ARRAY_SIZE(a80_panel_init_cmds);

            mipi_dsi_cmdlist_put(&cmdreq);
        }
        printk("[Display] sharp panel first init cmd\n");

        bFirst = false;
    }
    else if (g_A68_hwID < A80_EVB) {
        cmdreq.cmds = novatek_display_on;
        cmdreq.cmds_cnt = ARRAY_SIZE(novatek_display_on);

        mipi_dsi_cmdlist_put(&cmdreq);
    }
    else {
        cmdreq.cmds = a80_panel_init_cmds;
        cmdreq.cmds_cnt = ARRAY_SIZE(a80_panel_init_cmds);

        mipi_dsi_cmdlist_put(&cmdreq);
    }

    g_displayOn = true;

    printk("[Display] novatek LCD on\n");
    return 0;
//ASUS_BSP: miniporting ---

	if (mipi->mode == DSI_VIDEO_MODE) {
		cmdreq.cmds = novatek_video_on_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_video_on_cmds);
		cmdreq.flags = CMD_REQ_COMMIT;
		cmdreq.rlen = 0;
		cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&cmdreq);
	} else {
		cmdreq.cmds = novatek_cmd_on_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cmd_on_cmds);
		cmdreq.flags = CMD_REQ_COMMIT;
		cmdreq.rlen = 0;
		cmdreq.cb = NULL;
		mipi_dsi_cmdlist_put(&cmdreq);

		/* clean up ack_err_status */
		mipi_dsi_cmd_bta_sw_trigger();
		mipi_novatek_manufacture_id(mfd);
	}

	return 0;
}

static int mipi_novatek_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	mfd = platform_get_drvdata(pdev);

	if (!mfd)
    {
        printk("%s,-ENODEV\n",__func__);
		return -ENODEV;
    }
	if (mfd->key != MFD_KEY)
    {
        printk("%s,-EINVAL,key=0x%x\n",__func__,mfd->key);
		return -EINVAL;
    }

//++ ASUS_BSP: for JB porting
    cmdreq.cmds = novatek_display_off_cmds;
    cmdreq.cmds_cnt = ARRAY_SIZE(novatek_display_off_cmds);
    cmdreq.flags = CMD_REQ_COMMIT;
    cmdreq.rlen = 0;
    cmdreq.cb = NULL;

    mipi_dsi_cmdlist_put(&cmdreq);

    g_panelOn = false;
    g_displayOn = false;
    bl_dimming = false;

    printk("[Display] panel off , g_panelOn=%d\n",g_panelOn);
//-- ASUS_BSP: for JB porting

	return 0;
}

//Louis +++
void sharp_set_cabc(int mode)
{
    struct mipi_panel_info *mipi;
    struct dsi_cmd_desc cabc_function_off[] = {
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(init_cabc1), init_cabc1},
        {DTYPE_DCS_WRITE1, 1, 0, 0, 0, sizeof(IE_CABC), IE_CABC},
    };

    mipi  = &g_mfd->panel_info.mipi;

    g_cabc_mode = mode;

    if (mdp4_overlay_dsi_state_get() == ST_DSI_SUSPEND) {
        cabc_cmd_supend = true;
        printk("[Display] %s: unable to send DCS command due to ST_DSI_SUSPEND, cabc_cmd_supend(%d)\n", __func__, cabc_cmd_supend);
        return;
    }

    if (mode == 0) {
        dimming_ctrl[1] = 0x12; //32 steps
        abc_ctrl[1] = 0x0;
    }
    else {
        dimming_ctrl[1] = 0x36;
        abc_ctrl[1] = 0x1;
    }

    if (mode == 4) {
        cabc_function_off[0].payload[1] = 0x24;
        cabc_function_off[1].payload[1] = IE_CABC[1] & 0xf0;

        printk("[Display] turn off CABC all function\n");
        cmdreq.cmds = cabc_function_off;
        cmdreq.cmds_cnt = ARRAY_SIZE(cabc_function_off);

    }
    else {
        IE_CABC[1] = IE_CABC[1] & 0xf0;
        IE_CABC[1] += mode;

        printk("[Display][CABC] write cabc mode = 0x%x\n", IE_CABC[1]);

        cmdreq.cmds = set_cabc_cmd;
        cmdreq.cmds_cnt = ARRAY_SIZE(set_cabc_cmd);
    }

    cmdreq.flags = CMD_REQ_COMMIT;
    cmdreq.rlen = 0;
    cmdreq.cb = NULL;
    mipi_dsi_cmdlist_put(&cmdreq);

    cabc_cmd_supend = false;

}

#define SHARP_CABC_PROC_FILE  "driver/cabc"
#define DUMP_LCD_REGISTER  "driver/lcd_reg"

static struct proc_dir_entry *cabc_proc_file;

#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/file.h>
static mm_segment_t oldfs;
static void initKernelEnv(void)
{
    oldfs = get_fs();
    set_fs(KERNEL_DS);
}

static void deinitKernelEnv(void)
{
    set_fs(oldfs);
}

static ssize_t cabc_proc_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
    char messages[256];

    memset(messages, 0, sizeof(messages));

    if (len > 256)
        len = 256;
    if (copy_from_user(messages, buff, len))
        return -EFAULT;

    initKernelEnv();
    if (g_A68_hwID >= A68_SR2)
    {
        if(strncmp(messages, "0", 1) == 0)  //off
            sharp_set_cabc(0);
        else if(strncmp(messages, "1", 1) == 0) //ui
            sharp_set_cabc(1);
        else if(strncmp(messages, "2", 1) == 0) //still
            sharp_set_cabc(2);
        else if(strncmp(messages, "3", 1) == 0) //moving
            sharp_set_cabc(3);
        else if(strncmp(messages, "off", 3) == 0) //turn off cabc all function
            sharp_set_cabc(4);
    }
    deinitKernelEnv(); 
    return len;
}

static struct file_operations cabc_proc_ops = {
    .write = cabc_proc_write,
};

static void create_cabc_proc_file(void)
{
    cabc_proc_file = create_proc_entry(SHARP_CABC_PROC_FILE, 0666, NULL);
    if (cabc_proc_file) {
        cabc_proc_file->proc_fops = &cabc_proc_ops;
    }
}

static ssize_t lcd_proc_write(struct file *filp, const char __user *buff, 
                unsigned long len, void *data)
{
    char messages[256];

    memset(messages, 0, sizeof(messages));

    if (len > 256)
        len = 256;
    if (copy_from_user(messages, buff, len))
        return -EFAULT;

    initKernelEnv();

    if(strncmp(messages, "on", 2) == 0) {
        dump_mipi_novatek_register(g_mfd);
    }

    deinitKernelEnv(); 
    return len;
}

//++ for BMMI test
static ssize_t lcd_status_read(char *page, char **start, off_t off, int count,
                int *eof, void *data)
{
    ssize_t ret;

    if (off > 0) {
        /* we have finished to read, return 0 */
        ret  = 0;
    } else {
        /* read panel state, return panel on/off state */
        lcd_pwrmode_read(g_mfd);
        ret = sprintf(page, "%d\n", g_display_sts);
    }

    return ret;
}
//-- for BMMI test

static void create_lcd_proc_file(void)
{
    struct proc_dir_entry *lcd_proc_file = create_proc_entry(DUMP_LCD_REGISTER, 0666, NULL);

    if (lcd_proc_file) {
        lcd_proc_file->read_proc = lcd_status_read;
        lcd_proc_file->write_proc = lcd_proc_write;
    }
}
//Louis ---

DEFINE_LED_TRIGGER(bkl_led_trigger);

static char led_pwm1[2] = {0x51, 0x0};	/* DTYPE_DCS_WRITE1 */
static struct dsi_cmd_desc backlight_cmd = {
	DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_pwm1), led_pwm1};

static void mipi_novatek_set_backlight(struct msm_fb_data_type *mfd)
{
    return; // +++ ASUS_BSP : miniporting

	if ((mipi_novatek_pdata->enable_wled_bl_ctrl)
	    && (wled_trigger_initialized)) {
		led_trigger_event(bkl_led_trigger, mfd->bl_level);
		return;
	}

	led_pwm1[1] = (unsigned char)mfd->bl_level;

	cmdreq.cmds = &backlight_cmd;
	cmdreq.cmds_cnt = 1;
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;

	mipi_dsi_cmdlist_put(&cmdreq);
}

static int mipi_dsi_3d_barrier_sysfs_register(struct device *dev);
static int barrier_mode;

static int __devinit mipi_novatek_lcd_probe(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
	struct platform_device *current_pdev;
	static struct mipi_dsi_phy_ctrl *phy_settings;
	static char dlane_swap;

	if (pdev->id == 0) {
		mipi_novatek_pdata = pdev->dev.platform_data;

		if (mipi_novatek_pdata
			&& mipi_novatek_pdata->phy_ctrl_settings) {
			phy_settings = (mipi_novatek_pdata->phy_ctrl_settings);
		}

		if (mipi_novatek_pdata
			&& mipi_novatek_pdata->dlane_swap) {
			dlane_swap = (mipi_novatek_pdata->dlane_swap);
		}

		if (mipi_novatek_pdata
			 && mipi_novatek_pdata->fpga_3d_config_addr)
			mipi_novatek_3d_init(mipi_novatek_pdata
	->fpga_3d_config_addr, mipi_novatek_pdata->fpga_ctrl_mode);

		/* create sysfs to control 3D barrier for the Sharp panel */
		if (mipi_dsi_3d_barrier_sysfs_register(&pdev->dev)) {
			pr_err("%s: Failed to register 3d Barrier sysfs\n",
						__func__);
			return -ENODEV;
		}
		barrier_mode = 0;

		return 0;
	}

	current_pdev = msm_fb_add_device(pdev);

	if (current_pdev) {
		mfd = platform_get_drvdata(current_pdev);
		if (!mfd)
			return -ENODEV;
		if (mfd->key != MFD_KEY)
			return -EINVAL;

		mipi  = &mfd->panel_info.mipi;

		if (phy_settings != NULL)
			mipi->dsi_phy_db = phy_settings;

		if (dlane_swap)
			mipi->dlane_swap = dlane_swap;
        g_mfd = mfd;// +++ ASUS_BSP : miniporting
	}

// +++ ASUS_BSP: Louis
    create_cabc_proc_file();
    create_lcd_proc_file();
// --- ASUS_BSP: Louis

	return 0;
}

static struct platform_driver this_driver = {
	.probe  = mipi_novatek_lcd_probe,
	.driver = {
		.name   = "mipi_novatek",
	},
};

static struct msm_fb_panel_data novatek_panel_data = {
	.on		= mipi_novatek_lcd_on,
	.off		= mipi_novatek_lcd_off,
	.set_backlight = mipi_novatek_set_backlight,
};

static ssize_t mipi_dsi_3d_barrier_read(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	return snprintf((char *)buf, sizeof(buf), "%u\n", barrier_mode);
}

static ssize_t mipi_dsi_3d_barrier_write(struct device *dev,
				struct device_attribute *attr,
				const char *buf,
				size_t count)
{
	int ret = -1;
	u32 data = 0;

	if (sscanf((char *)buf, "%u", &data) != 1) {
		dev_err(dev, "%s\n", __func__);
		ret = -EINVAL;
	} else {
		barrier_mode = data;
		if (data == 1)
			mipi_dsi_enable_3d_barrier(LANDSCAPE);
		else if (data == 2)
			mipi_dsi_enable_3d_barrier(PORTRAIT);
		else
			mipi_dsi_enable_3d_barrier(0);
	}

	return count;
}

static struct device_attribute mipi_dsi_3d_barrier_attributes[] = {
	__ATTR(enable_3d_barrier, 0664, mipi_dsi_3d_barrier_read,
					 mipi_dsi_3d_barrier_write),
};

static int mipi_dsi_3d_barrier_sysfs_register(struct device *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mipi_dsi_3d_barrier_attributes); i++)
		if (device_create_file(dev, mipi_dsi_3d_barrier_attributes + i))
			goto error;

	return 0;

error:
	for (; i >= 0 ; i--)
		device_remove_file(dev, mipi_dsi_3d_barrier_attributes + i);
	pr_err("%s: Unable to create interface\n", __func__);

	return -ENODEV;
}

static int ch_used[3];

int mipi_novatek_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	ret = mipi_novatek_lcd_init();
	if (ret) {
		pr_err("mipi_novatek_lcd_init() failed with ret %u\n", ret);
		return ret;
	}

	pdev = platform_device_alloc("mipi_novatek", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	novatek_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &novatek_panel_data,
		sizeof(novatek_panel_data));
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}

static int mipi_novatek_lcd_init(void)
{
#ifdef CONFIG_SPI_QUP
	int ret;
	ret = spi_register_driver(&panel_3d_spi_driver);

	if (ret) {
		pr_err("%s: spi register failed: rc=%d\n", __func__, ret);
		platform_driver_unregister(&this_driver);
	} else
		pr_info("%s: SUCCESS (SPI)\n", __func__);
#endif

	led_trigger_register_simple("bkl_trigger", &bkl_led_trigger);
	pr_info("%s: SUCCESS (WLED TRIGGER)\n", __func__);
	wled_trigger_initialized = 1;

	mipi_dsi_buf_alloc(&novatek_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&novatek_rx_buf, DSI_BUF_SIZE);

	return platform_driver_register(&this_driver);
}
