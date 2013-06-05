/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
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

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_novatek.h"
#include <linux/kernel.h>   //ASUS_BSP: for A80 porting

static struct msm_panel_info pinfo;

static struct mipi_dsi_phy_ctrl dsi_720p_phy_db = {
    /* regulator */
    {0x03, 0x0a, 0x04, 0x00, 0x20},
    /* timing */
    {0xC2, 0x26, 0x25, 0x00, 0x55, 0x99, 0x27,
    0x92, 0x29, 0x03, 0x04, 0xa0},
    /* phy ctrl */
    {0x5f, 0x00, 0x00, 0x10},
    /* strength */
    {0xff, 0x00, 0x06, 0x00},
    /* pll control */
    {0x0, 
    0xf9, 0xb0, 0xda, 
    0x00, 0x50, 0x48, 0x63,
    0x30, 0x07, 0x00,
    0x00, 0x14, 0x03, 0x00, 0x02, 
    0x00, 0x20, 0x00, 0x01 },
};

//++ for A80 porting
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
    /* 1920*1080, RGB888, 4 Lane 60 fps video mode */
    /* regulator */
    {0x03, 0x0a, 0x04, 0x00, 0x20},
    /* timing */
    {0xE8, 0x9B, 0x3B, 0x00, 0x78, 0xA6, 0x3D, 0x9C,
    0x42, 0x03, 0x04, 0xa0},
    /* phy ctrl */
    {0x5f, 0x00, 0x00, 0x10},
    /* strength */
    {0xff, 0x00, 0x06, 0x00},
    /* pll control */
    {0x0, 0xB3, 0x1, 0x19, 0x00, 0x50, 0x48, 0x63,
    0x41, 0x0f, 0x01,
    0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};
//-- for A80 porting

static int __init mipi_novatek_blue_720p_pt_init(void)
{
	int ret;

    if (g_A68_hwID < A80_EVB)
    {
        printk("[Display] ++++ A68 panel driver init\n");
        pinfo.xres = 720;
        pinfo.yres = 1280;
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_CMD_MODE
        pinfo.type = MIPI_CMD_PANEL;
        pinfo.bl_max = 255;
        pinfo.clk_rate = 575000000;
        pinfo.lcd.vsync_enable = TRUE;
        pinfo.lcd.hw_vsync_mode = TRUE;
        pinfo.lcd.refx100 = 5830; /* adjust refx100 to prevent tearing */
        pinfo.lcd.v_back_porch = 4;
        pinfo.lcd.v_front_porch = 14;
        pinfo.lcd.v_pulse_width = 2;

        pinfo.mipi.mode = DSI_CMD_MODE;
        pinfo.mipi.dst_format = DSI_CMD_DST_FORMAT_RGB888;
        pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_NONE;
        pinfo.mipi.te_sel = 1; /* TE from vsycn gpio */
        pinfo.mipi.interleave_max = 1;
        pinfo.mipi.insert_dcs_cmd = TRUE;
        pinfo.mipi.wr_mem_continue = 0x3c;
        pinfo.mipi.wr_mem_start = 0x2c;
#elif  defined(CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE)
        pinfo.type = MIPI_VIDEO_PANEL;
        pinfo.bl_max = 15;
        pinfo.mipi.mode = DSI_VIDEO_MODE;
        pinfo.mipi.pulse_mode_hsa_he = TRUE;
        pinfo.mipi.hfp_power_stop = FALSE;
        pinfo.mipi.hbp_power_stop = FALSE;
        pinfo.mipi.hsa_power_stop = FALSE;
        pinfo.mipi.eof_bllp_power_stop = TRUE;
        pinfo.mipi.bllp_power_stop = TRUE;
        pinfo.mipi.traffic_mode = DSI_NON_BURST_SYNCH_PULSE;
        pinfo.mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
        pinfo.mipi.rgb_swap = DSI_RGB_SWAP_BGR;
        pinfo.mipi.tx_eot_append = TRUE;
        pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
        pinfo.mipi.frame_rate = 60;
#endif
        pinfo.pdest = DISPLAY_1;
        pinfo.wait_cycle = 0;
        pinfo.bpp = 24;
        pinfo.lcdc.h_back_porch = 96;
        pinfo.lcdc.h_front_porch = 96;
        pinfo.lcdc.h_pulse_width = 8;
        pinfo.lcdc.v_back_porch = 4;
        pinfo.lcdc.v_front_porch = 14;
        pinfo.lcdc.v_pulse_width = 2;
        pinfo.lcdc.border_clr = 0;	/* blk */
        pinfo.lcdc.underflow_clr = 0xff;	/* blue */
        pinfo.lcdc.hsync_skew = 0;

        pinfo.bl_min = 1;
        pinfo.fb_num = 2;

        pinfo.mipi.vc = 0;
        pinfo.mipi.data_lane0 = TRUE;
        pinfo.mipi.data_lane1 = TRUE;
        pinfo.mipi.data_lane2 = TRUE;

        pinfo.mipi.t_clk_post = 0x0C;
        pinfo.mipi.t_clk_pre = 0x28;
        pinfo.mipi.stream = 0;	/* dma_p */
        pinfo.mipi.esc_byte_ratio = 4;

        pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;

        pinfo.mipi.dsi_phy_db = &dsi_720p_phy_db;

//Mickey+++, add for DDS architecture
        pinfo.asus_dds_xres = 1280;
        pinfo.asus_dds_yres = 1280;
//Mickey---

        ret = mipi_novatek_device_register(&pinfo, MIPI_DSI_PRIM,
                            MIPI_DSI_PANEL_720P_PT);
    }
    else
    {
        printk("[Display] ++++ A80 panel driver init\n");
        pinfo.xres = 1080;
        pinfo.yres = 1920;

        pinfo.type = MIPI_VIDEO_PANEL;
        pinfo.pdest = DISPLAY_1;
        pinfo.wait_cycle = 0;
        pinfo.bpp = 24;
        pinfo.lcdc.h_back_porch = 50;
        pinfo.lcdc.h_front_porch = 160;
        pinfo.lcdc.h_pulse_width = 10;
        pinfo.lcdc.v_back_porch = 4;
        pinfo.lcdc.v_front_porch = 4;
        pinfo.lcdc.v_pulse_width = 2;
        pinfo.lcdc.border_clr = 0;  /* blk */
        pinfo.lcdc.underflow_clr = 0xff;    /* blue */
        pinfo.lcdc.hsync_skew = 0;
        pinfo.bl_max = 255;
        pinfo.bl_min = 1;
        pinfo.fb_num = 2;
        pinfo.clk_rate = 905000000;//981560000;

        pinfo.mipi.mode = DSI_VIDEO_MODE;
        pinfo.mipi.pulse_mode_hsa_he = TRUE;
        pinfo.mipi.hfp_power_stop = FALSE;
        pinfo.mipi.hbp_power_stop = FALSE;
        pinfo.mipi.hsa_power_stop = FALSE;
        pinfo.mipi.eof_bllp_power_stop = TRUE;
        pinfo.mipi.bllp_power_stop = TRUE;
        pinfo.mipi.traffic_mode = DSI_NON_BURST_SYNCH_PULSE;
        pinfo.mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
        pinfo.mipi.vc = 0;
        pinfo.mipi.rgb_swap = DSI_RGB_SWAP_BGR;
        pinfo.mipi.data_lane0 = TRUE;
        pinfo.mipi.data_lane1 = TRUE;
        pinfo.mipi.data_lane2 = TRUE;
        pinfo.mipi.data_lane3 = TRUE;
        pinfo.mipi.tx_eot_append = TRUE;
        pinfo.mipi.t_clk_post = 0x1A;//0x04;
        pinfo.mipi.t_clk_pre = 0x32;//0x1c;
        pinfo.mipi.stream = 0; /* dma_p */
        pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
        pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
        pinfo.mipi.frame_rate = 60;
        pinfo.mipi.dsi_phy_db = &dsi_video_mode_phy_db;
        pinfo.mipi.esc_byte_ratio = 13;
    //Mickey+++, add for a80 DDS architecture
        pinfo.asus_dds_xres = 1920;
        pinfo.asus_dds_yres = 1920;
    //Mickey---
        ret = mipi_novatek_device_register(&pinfo, MIPI_DSI_PRIM,
                            MIPI_DSI_PANEL_WUXGA);
    }

	if (ret)
		pr_err("%s: failed to register device!\n", __func__);

	return ret;
}

module_init(mipi_novatek_blue_720p_pt_init);

