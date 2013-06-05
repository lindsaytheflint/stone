/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
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

#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/bootmem.h>
#include <linux/ion.h>
#include <asm/mach-types.h>
#include <mach/msm_memtypes.h>
#include <mach/board.h>
#include <mach/gpiomux.h>
#include <mach/ion.h>
#include <mach/msm_bus_board.h>
#include <mach/socinfo.h>

#include "devices.h"
#include "board-8064.h"
// +++ ASUS_BSP : Miniporting
//Mickey+++, change for DDS architecture
#ifdef CONFIG_FB_MSM_TRIPLE_BUFFER
/* prim = 1366 x 768 x 3(bpp) x 3(pages) */
//#define MSM_FB_PRIM_BUF_SIZE roundup(1920 * 1080 * 4 * 3, 0x10000)
#define MSM_FB_PRIM_BUF_SIZE roundup( ALIGN(1280,32) * 1280 * 4 * 3, 0x10000) //Mickey, add for DDS transformation
#define MSM_FB_PRIM_BUF_SIZE_A80 roundup( ALIGN(1920,32) * 1920 * 4 * 3, 0x10000) //Mickey, add for a80 DDS transformation
#else
/* prim = 1366 x 768 x 3(bpp) x 2(pages) */
//#define MSM_FB_PRIM_BUF_SIZE roundup(1920 * 1080 * 4 * 2, 0x10000)
#define MSM_FB_PRIM_BUF_SIZE roundup( ALIGN(1280,32) * 1280 * 4 * 2, 0x10000) //Mickey, add for DDS transformation
#define MSM_FB_PRIM_BUF_SIZE_A80 roundup( ALIGN(1920,32) * 1920 * 4 * 2, 0x10000) //Mickey, add for a80 DDS transformation
#endif
//Mickey---

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL
#define MSM_FB_EXT_BUF_SIZE \
		(roundup(( ALIGN(1920,32) * 1280 * 2), 4096) * 1) /* 2 bpp x 1 page */ //Mickey modified for 1920x1200 support
#elif defined(CONFIG_FB_MSM_TVOUT)
#define MSM_FB_EXT_BUF_SIZE \
		(roundup((720 * 576 * 2), 4096) * 2) /* 2 bpp x 2 pages */
#else
#define MSM_FB_EXT_BUF_SIZE	0
#endif

#ifdef CONFIG_FB_MSM_WRITEBACK_MSM_PANEL
#define MSM_FB_WFD_BUF_SIZE \
		(roundup((1280 * 736 * 2), 4096) * 1) /* 2 bpp x 1 page */
#else
#define MSM_FB_WFD_BUF_SIZE     0
#endif

#define MSM_FB_SIZE \
	roundup(MSM_FB_PRIM_BUF_SIZE + \
		MSM_FB_EXT_BUF_SIZE + MSM_FB_WFD_BUF_SIZE, 4096)

//Mickey+++, add for A80 support
#define MSM_FB_SIZE_A80 \
    roundup(MSM_FB_PRIM_BUF_SIZE_A80 + \
        MSM_FB_EXT_BUF_SIZE + MSM_FB_WFD_BUF_SIZE, 4096)
//Mickey---
// --- ASUS_BSP : Miniporting

#ifdef CONFIG_FB_MSM_OVERLAY0_WRITEBACK
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE roundup((1376 * 768 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE (0)
#endif  /* CONFIG_FB_MSM_OVERLAY0_WRITEBACK */

#ifdef CONFIG_FB_MSM_OVERLAY1_WRITEBACK
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE roundup((1920 * 1088 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE (0)
#endif  /* CONFIG_FB_MSM_OVERLAY1_WRITEBACK */


static struct resource msm_fb_resources[] = {
	{
		.flags = IORESOURCE_DMA,
	}
};

#define LVDS_CHIMEI_PANEL_NAME "lvds_chimei_wxga"
#define LVDS_FRC_PANEL_NAME "lvds_frc_fhd"
#define MIPI_VIDEO_TOSHIBA_WSVGA_PANEL_NAME "mipi_video_toshiba_wsvga"
#define MIPI_VIDEO_CHIMEI_WXGA_PANEL_NAME "mipi_video_chimei_wxga"
#define HDMI_PANEL_NAME "hdmi_msm"
#define TVOUT_PANEL_NAME "tvout_msm"

#define LVDS_PIXEL_MAP_PATTERN_1	1
#define LVDS_PIXEL_MAP_PATTERN_2	2

#ifdef CONFIG_FB_MSM_HDMI_AS_PRIMARY
static unsigned char hdmi_is_primary = 1;
#else
static unsigned char hdmi_is_primary;
#endif

unsigned char apq8064_hdmi_as_primary_selected(void)
{
	return hdmi_is_primary;
}

static void set_mdp_clocks_for_wuxga(void);

static int msm_fb_detect_panel(const char *name)
{
	u32 version;
	
//++ ASUS_BSP: Louis: avoid mdp underrun
    if (g_A68_hwID >= A80_EVB) {
        printk("[Display] increase bus speed for A80 panel");
        hdmi_is_primary = 1;
        set_mdp_clocks_for_wuxga();
        return 0;
    }
//-- ASUS_BSPL Louis: avoid mdp underrun

	if (machine_is_apq8064_liquid()) {
		version = socinfo_get_platform_version();
		if ((SOCINFO_VERSION_MAJOR(version) == 1) &&
			(SOCINFO_VERSION_MINOR(version) == 1)) {
			if (!strncmp(name, MIPI_VIDEO_CHIMEI_WXGA_PANEL_NAME,
				strnlen(MIPI_VIDEO_CHIMEI_WXGA_PANEL_NAME,
					PANEL_NAME_MAX_LEN)))
				return 0;
		} else {
			if (!strncmp(name, LVDS_CHIMEI_PANEL_NAME,
				strnlen(LVDS_CHIMEI_PANEL_NAME,
					PANEL_NAME_MAX_LEN)))
				return 0;
		}
	} else if (machine_is_apq8064_mtp()) {
		if (!strncmp(name, MIPI_VIDEO_TOSHIBA_WSVGA_PANEL_NAME,
			strnlen(MIPI_VIDEO_TOSHIBA_WSVGA_PANEL_NAME,
				PANEL_NAME_MAX_LEN)))
			return 0;
	} else if (machine_is_apq8064_cdp()) {
		if (!strncmp(name, LVDS_CHIMEI_PANEL_NAME,
			strnlen(LVDS_CHIMEI_PANEL_NAME,
				PANEL_NAME_MAX_LEN)))
			return 0;
	} else if (machine_is_mpq8064_dtv()) {
		if (!strncmp(name, LVDS_FRC_PANEL_NAME,
			strnlen(LVDS_FRC_PANEL_NAME,
			PANEL_NAME_MAX_LEN))) {
			set_mdp_clocks_for_wuxga();
			return 0;
		}
	}

	if (!strncmp(name, HDMI_PANEL_NAME,
			strnlen(HDMI_PANEL_NAME,
				PANEL_NAME_MAX_LEN))) {
		if (apq8064_hdmi_as_primary_selected())
			set_mdp_clocks_for_wuxga();
		return 0;
	}


	return -ENODEV;
}

static struct msm_fb_platform_data msm_fb_pdata = {
	.detect_client = msm_fb_detect_panel,
};

static struct platform_device msm_fb_device = {
	.name              = "msm_fb",
	.id                = 0,
	.num_resources     = ARRAY_SIZE(msm_fb_resources),
	.resource          = msm_fb_resources,
	.dev.platform_data = &msm_fb_pdata,
};

void __init apq8064_allocate_fb_region(void)
{
	void *addr;
	unsigned long size;

    //Mickey+++, add for A80 support
    if (g_A68_hwID >= A80_EVB)
        size = MSM_FB_SIZE_A80;
    else
        size = MSM_FB_SIZE;
    //Mickey---
	addr = alloc_bootmem_align(size, 0x1000);
	msm_fb_resources[0].start = __pa(addr);
	msm_fb_resources[0].end = msm_fb_resources[0].start + size - 1;
	pr_info("allocating %lu bytes at %p (%lx physical) for fb\n",
			size, addr, __pa(addr));
}

#define MDP_VSYNC_GPIO 0

static struct msm_bus_vectors mdp_init_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = 0,
	},
};

static struct msm_bus_vectors mdp_ui_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 216000000 * 2,
		.ib = 270000000 * 2,
	},
};

static struct msm_bus_vectors mdp_vga_vectors[] = {
	/* VGA and less video */
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 216000000 * 2,
		.ib = 270000000 * 2,
	},
};

static struct msm_bus_vectors mdp_720p_vectors[] = {
	/* 720p and less video */
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 230400000 * 2,
		.ib = 288000000 * 2,
	},
};

static struct msm_bus_vectors mdp_1080p_vectors[] = {
	/* 1080p and less video */
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 334080000 * 2,
		.ib = 417600000 * 2,
	},
};

static struct msm_bus_paths mdp_bus_scale_usecases[] = {
	{
		ARRAY_SIZE(mdp_init_vectors),
		mdp_init_vectors,
	},
	{
		ARRAY_SIZE(mdp_ui_vectors),
		mdp_ui_vectors,
	},
	{
		ARRAY_SIZE(mdp_ui_vectors),
		mdp_ui_vectors,
	},
	{
		ARRAY_SIZE(mdp_vga_vectors),
		mdp_vga_vectors,
	},
	{
		ARRAY_SIZE(mdp_720p_vectors),
		mdp_720p_vectors,
	},
	{
		ARRAY_SIZE(mdp_1080p_vectors),
		mdp_1080p_vectors,
	},
};

static struct msm_bus_scale_pdata mdp_bus_scale_pdata = {
	mdp_bus_scale_usecases,
	ARRAY_SIZE(mdp_bus_scale_usecases),
	.name = "mdp",
};

static struct msm_panel_common_pdata mdp_pdata = {
	.gpio = MDP_VSYNC_GPIO,
	.mdp_max_clk = 200000000,
	.mdp_bus_scale_table = &mdp_bus_scale_pdata,
	.mdp_rev = MDP_REV_44,
#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
	.mem_hid = BIT(ION_CP_MM_HEAP_ID),
#else
	.mem_hid = MEMTYPE_EBI1,
#endif
	.mdp_iommu_split_domain = 1,
    .cont_splash_enabled = 0x1, //Louis: for A80 miniporting
};

void __init apq8064_mdp_writeback(struct memtype_reserve* reserve_table)
{
	mdp_pdata.ov0_wb_size = MSM_FB_OVERLAY0_WRITEBACK_SIZE;
	mdp_pdata.ov1_wb_size = MSM_FB_OVERLAY1_WRITEBACK_SIZE;
#if defined(CONFIG_ANDROID_PMEM) && !defined(CONFIG_MSM_MULTIMEDIA_USE_ION)
	reserve_table[mdp_pdata.mem_hid].size +=
		mdp_pdata.ov0_wb_size;
	reserve_table[mdp_pdata.mem_hid].size +=
		mdp_pdata.ov1_wb_size;
#endif
}

static struct resource hdmi_msm_resources[] = {
	{
		.name  = "hdmi_msm_qfprom_addr",
		.start = 0x00700000,
		.end   = 0x007060FF,
		.flags = IORESOURCE_MEM,
	},
	{
		.name  = "hdmi_msm_hdmi_addr",
		.start = 0x04A00000,
		.end   = 0x04A00FFF,
		.flags = IORESOURCE_MEM,
	},
	{
		.name  = "hdmi_msm_irq",
		.start = HDMI_IRQ,
		.end   = HDMI_IRQ,
		.flags = IORESOURCE_IRQ,
	},
};

static int hdmi_enable_5v(int on);
static int hdmi_core_power(int on, int show);
#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL_CEC_SUPPORT
static int hdmi_cec_power(int on);
#endif
static int hdmi_gpio_config(int on);
static int hdmi_panel_power(int on);

static struct msm_hdmi_platform_data hdmi_msm_data = {
	.irq = HDMI_IRQ,
	.enable_5v = hdmi_enable_5v,
	.core_power = hdmi_core_power,
#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL_CEC_SUPPORT
	.cec_power = hdmi_cec_power,
#endif
	.panel_power = hdmi_panel_power,
	.gpio_config = hdmi_gpio_config,
};

static struct platform_device hdmi_msm_device = {
	.name = "hdmi_msm",
	.id = 0,
	.num_resources = ARRAY_SIZE(hdmi_msm_resources),
	.resource = hdmi_msm_resources,
	.dev.platform_data = &hdmi_msm_data,
};

#ifdef CONFIG_FB_MSM_WRITEBACK_MSM_PANEL	//ASUS_BSP: fix for miniporting++
static char wfd_check_mdp_iommu_split_domain(void)
{
	return mdp_pdata.mdp_iommu_split_domain;
}

static struct msm_wfd_platform_data wfd_pdata = {
	.wfd_check_mdp_iommu_split = wfd_check_mdp_iommu_split_domain,
};

static struct platform_device wfd_panel_device = {
	.name = "wfd_panel",
	.id = 0,
	.dev.platform_data = NULL,
};

static struct platform_device wfd_device = {
	.name          = "msm_wfd",
	.id            = -1,
	.dev.platform_data = &wfd_pdata,
};
#endif

/* HDMI related GPIOs */
#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL_CEC_SUPPORT
#define HDMI_CEC_VAR_GPIO	69
#endif
#define HDMI_DDC_CLK_GPIO	70
#define HDMI_DDC_DATA_GPIO	71
#define HDMI_HPD_GPIO		72

#if 0 // +++ ASUS_BSP : A68 miniporting
static bool dsi_power_on;
static int mipi_dsi_panel_power(int on)
{
	static struct regulator *reg_lvs7, *reg_l2, *reg_l11, *reg_ext_3p3v;
	static int gpio36, gpio25, gpio26, mpp3;
	int rc;

	pr_debug("%s: on=%d\n", __func__, on);

	if (!dsi_power_on) {
		reg_lvs7 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi1_vddio");
		if (IS_ERR_OR_NULL(reg_lvs7)) {
			pr_err("could not get 8921_lvs7, rc = %ld\n",
				PTR_ERR(reg_lvs7));
			return -ENODEV;
		}

		reg_l2 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi1_pll_vdda");
		if (IS_ERR_OR_NULL(reg_l2)) {
			pr_err("could not get 8921_l2, rc = %ld\n",
				PTR_ERR(reg_l2));
			return -ENODEV;
		}

		rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
		if (rc) {
			pr_err("set_voltage l2 failed, rc=%d\n", rc);
			return -EINVAL;
		}
		reg_l11 = regulator_get(&msm_mipi_dsi1_device.dev,
						"dsi1_avdd");
		if (IS_ERR(reg_l11)) {
				pr_err("could not get 8921_l11, rc = %ld\n",
						PTR_ERR(reg_l11));
				return -ENODEV;
		}
		rc = regulator_set_voltage(reg_l11, 3000000, 3000000);
		if (rc) {
				pr_err("set_voltage l11 failed, rc=%d\n", rc);
				return -EINVAL;
		}

		if (machine_is_apq8064_liquid()) {
			reg_ext_3p3v = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi1_vccs_3p3v");
			if (IS_ERR_OR_NULL(reg_ext_3p3v)) {
				pr_err("could not get reg_ext_3p3v, rc = %ld\n",
					PTR_ERR(reg_ext_3p3v));
				reg_ext_3p3v = NULL;
				return -ENODEV;
			}
			mpp3 = PM8921_MPP_PM_TO_SYS(3);
			rc = gpio_request(mpp3, "backlight_en");
			if (rc) {
				pr_err("request mpp3 failed, rc=%d\n", rc);
				return -ENODEV;
			}
		}

		gpio25 = PM8921_GPIO_PM_TO_SYS(25);
		rc = gpio_request(gpio25, "disp_rst_n");
		if (rc) {
			pr_err("request gpio 25 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		gpio26 = PM8921_GPIO_PM_TO_SYS(26);
		rc = gpio_request(gpio26, "pwm_backlight_ctrl");
		if (rc) {
			pr_err("request gpio 26 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		gpio36 = PM8921_GPIO_PM_TO_SYS(36); /* lcd1_pwr_en_n */
		rc = gpio_request(gpio36, "lcd1_pwr_en_n");
		if (rc) {
			pr_err("request gpio 36 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		dsi_power_on = true;
	}

	if (on) {
		rc = regulator_enable(reg_lvs7);
		if (rc) {
			pr_err("enable lvs7 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_set_optimum_mode(reg_l11, 110000);
		if (rc < 0) {
			pr_err("set_optimum_mode l11 failed, rc=%d\n", rc);
			return -EINVAL;
		}
		rc = regulator_enable(reg_l11);
		if (rc) {
			pr_err("enable l11 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_set_optimum_mode(reg_l2, 100000);
		if (rc < 0) {
			pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			return -EINVAL;
		}
		rc = regulator_enable(reg_l2);
		if (rc) {
			pr_err("enable l2 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		if (machine_is_apq8064_liquid()) {
			rc = regulator_enable(reg_ext_3p3v);
			if (rc) {
				pr_err("enable reg_ext_3p3v failed, rc=%d\n",
					rc);
				return -ENODEV;
			}
			gpio_set_value_cansleep(mpp3, 1);
		}

		gpio_set_value_cansleep(gpio36, 0);
		gpio_set_value_cansleep(gpio25, 1);
	} else {
		gpio_set_value_cansleep(gpio25, 0);
		gpio_set_value_cansleep(gpio36, 1);

		if (machine_is_apq8064_liquid()) {
			gpio_set_value_cansleep(mpp3, 0);

			rc = regulator_disable(reg_ext_3p3v);
			if (rc) {
				pr_err("disable reg_ext_3p3v failed, rc=%d\n",
					rc);
				return -ENODEV;
			}
		}

		rc = regulator_disable(reg_l11);
		if (rc) {
			pr_err("disable reg_l1 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_disable(reg_lvs7);
		if (rc) {
			pr_err("disable reg_lvs7 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_disable(reg_l2);
		if (rc) {
			pr_err("disable reg_l2 failed, rc=%d\n", rc);
			return -ENODEV;
		}
	}

	return 0;
}
#endif // --- ASUS_BSP : A68 miniporting

// +++ ASUS_BSP : A68 & A80 miniporting
static bool dsi_power_on = false;
static int a68_mipi_dsi_sharp_panel_power(int on)
{
    static struct regulator *reg_l11, *reg_l2;
    static struct regulator *reg_lvs5; // should be 1.8V
    int rc;
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
    static int gpio51 = 51;
#endif

    if (!dsi_power_on) {

        reg_l11 = regulator_get(&msm_mipi_dsi1_device.dev,"dsi_vdc");
        if (IS_ERR(reg_l11)) {
            pr_err("could not get 8921_l11, rc = %ld\n",PTR_ERR(reg_l11));
            return -ENODEV;
        }

        reg_lvs5 = regulator_get(&msm_mipi_dsi1_device.dev,
                "dsi_vddio");
        if (IS_ERR_OR_NULL(reg_lvs5)) {
            pr_err("could not get dsi_vddio, rc = %ld\n",
                PTR_ERR(reg_lvs5));
            return -ENODEV;
        }

        reg_l2 = regulator_get(&msm_mipi_dsi1_device.dev,"dsi_vdda");
        if (IS_ERR(reg_l2)) {
            pr_err("could not get 8921_l2, rc = %ld\n",
                PTR_ERR(reg_l2));
            return -ENODEV;
        }
        rc = regulator_set_voltage(reg_l11, 3100000, 3100000);
        if (rc) {
            pr_err("set_voltage l11 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
        if (rc) {
            pr_err("set_voltage l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }
#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
        rc = gpio_request(gpio51, "disp_rst_n");
        if (rc) {
            pr_err("request gpio 51 failed, rc=%d\n", rc);
            return -ENODEV;
        }
#endif
        rc = regulator_set_optimum_mode(reg_l11, 100000);
        if (rc < 0) {
            pr_err("set_optimum_mode l11 failed, rc=%d\n", rc); 
            return -EINVAL;
        }

        rc = regulator_set_optimum_mode(reg_l2, 100000);
        if (rc < 0) {
            pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_enable(reg_l11);
        if (rc) {
            pr_err("enable l11 failed, rc=%d\n", rc);
            return -ENODEV;
        }
        udelay(5);

        rc = regulator_enable(reg_lvs5);
        if (rc) {
            pr_err("enable lvs5 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = regulator_enable(reg_l2);
        if (rc) {
            pr_err("enable l2 failed, rc=%d\n", rc);
            return -ENODEV;
        }

#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
        msleep(20);
        gpio_set_value_cansleep(gpio51, 0);
        msleep(50);
        gpio_set_value_cansleep(gpio51, 1);
#endif

        dsi_power_on = true;
        return 0;
    }

    if (on) {

        rc = regulator_set_optimum_mode(reg_l2, 100000);
        if (rc < 0) {
            pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_enable(reg_l2);
        if (rc) {
            pr_err("enable l2 failed, rc=%d\n", rc);
            return -ENODEV;
        }
    }

    else {

        rc = regulator_disable(reg_l2);
        if (rc) {
            printk("disable reg_l2 failed, rc=%d\n", rc);
            return -ENODEV;
        }

#if 0
        rc = regulator_disable(reg_l11);
        if (rc) {
            printk("disable reg_l8 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = regulator_disable(reg_lvs5);
        if (rc) {
            pr_err("disable reg_lvs5 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = regulator_set_optimum_mode(reg_l11, 100);
        if (rc < 0) {
            printk("set_optimum_mode l11 failed, rc=%d\n", rc);
            return -EINVAL;
        }
#endif

        rc = regulator_set_optimum_mode(reg_l2, 100);
        if (rc < 0) {
            printk("set_optimum_mode l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

#ifdef CONFIG_FB_MSM_MIPI_NOVATEK_VIDEO_MODE
        gpio_set_value_cansleep(gpio51, 0);
#endif
    }

    return 0;
}

static int a80_mipi_dsi_sharp_panel_power(int on)
{
    static struct regulator *reg_l11, *reg_l2;
    static struct regulator *reg_lvs5; // should be 1.8V
    int rc;
    static int gpio51 = 51, gpio2 = 2, gpio37 = 37, gpio56 = 56;

    if (!dsi_power_on) {

        reg_l11 = regulator_get(&msm_mipi_dsi1_device.dev,"dsi_vdc");
        if (IS_ERR(reg_l11)) {
            pr_err("could not get 8921_l11, rc = %ld\n",PTR_ERR(reg_l11));
            return -ENODEV;
        }

        reg_lvs5 = regulator_get(&msm_mipi_dsi1_device.dev,
                "dsi_vddio");
        if (IS_ERR_OR_NULL(reg_lvs5)) {
            pr_err("could not get dsi_vddio, rc = %ld\n",
                PTR_ERR(reg_lvs5));
            return -ENODEV;
        }

        reg_l2 = regulator_get(&msm_mipi_dsi1_device.dev,"dsi_vdda");
        if (IS_ERR(reg_l2)) {
            pr_err("could not get 8921_l2, rc = %ld\n",
                PTR_ERR(reg_l2));
            return -ENODEV;
        }
        rc = regulator_set_voltage(reg_l11, 3100000, 3100000);
        if (rc) {
            pr_err("set_voltage l11 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
        if (rc) {
            pr_err("set_voltage l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = gpio_request(gpio2, "bl_en");
        if (rc) {
            pr_err("request gpio 2 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = gpio_request(gpio51, "disp_rst_n");
        if (rc) {
            pr_err("request gpio 51 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = gpio_request(gpio37, " STB1_EN");
        if (rc) {
            pr_err("request gpio 37 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = gpio_request(gpio56, "STB2_EN");
        if (rc) {
            pr_err("request gpio 56 failed, rc=%d\n", rc);
            return -ENODEV;
        }

    }

    if (on) {

        rc = regulator_set_optimum_mode(reg_l11, 100000);
        if (rc < 0) {
            pr_err("set_optimum_mode l11 failed, rc=%d\n", rc); 
            return -EINVAL;
        }

        rc = regulator_set_optimum_mode(reg_l2, 100000);
        if (rc < 0) {
            pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_enable(reg_l11);
        if (rc) {
            pr_err("enable l11 failed, rc=%d\n", rc);
            return -ENODEV;
        }
        udelay(5);

        rc = regulator_enable(reg_lvs5);
        if (rc) {
            pr_err("enable lvs5 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        msleep(15);
        gpio_set_value(gpio2, 1);

        msleep(180);
        gpio_set_value_cansleep(gpio56, 1);     //AVDD +5V
        msleep(15);
        gpio_set_value_cansleep(gpio37, 1);     //AVDD -5V

        rc = regulator_enable(reg_l2);
        if (rc) {
            pr_err("enable l2 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        gpio_set_value_cansleep(gpio51, 0);
        msleep(50);
        gpio_set_value_cansleep(gpio51, 1);
        msleep(20);

        dsi_power_on = true;
    }

    else {
        rc = regulator_disable(reg_l2);
        if (rc) {
            pr_err("disable reg_l2 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = regulator_disable(reg_l11);
        if (rc) {
            printk("disable reg_l8 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        gpio_set_value_cansleep(gpio37, 0);     //AVDD -5V
        msleep(12);
        gpio_set_value_cansleep(gpio56, 0);     //AVDD +5V
        msleep(12);

        rc = regulator_disable(reg_lvs5);
        if (rc) {
            pr_err("disable reg_lvs5 failed, rc=%d\n", rc);
            return -ENODEV;
        }

        rc = regulator_set_optimum_mode(reg_l11, 100);
        if (rc < 0) {
            printk("set_optimum_mode l11 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        rc = regulator_set_optimum_mode(reg_l2, 100);
        if (rc < 0) {
            printk("set_optimum_mode l2 failed, rc=%d\n", rc);
            return -EINVAL;
        }

        gpio_set_value_cansleep(gpio2, 0);
        gpio_set_value_cansleep(gpio51, 0);

     }

    return 0;
}

static int mipi_dsi_panel_power(int on)
{
    //pr_info("%s: on=%d\n", __func__, on);
    if (g_A68_hwID < A80_EVB) {
        pr_info("++. A68 mipi_dsi_panel_power on=%d\n", on);
        a68_mipi_dsi_sharp_panel_power(on);
        pr_info("--. A68 mipi_dsi_panel_power on=%d\n", on);
    }
    else {
        pr_info("++. A80 mipi_dsi_panel_power on=%d\n", on);
        a80_mipi_dsi_sharp_panel_power(on);
        pr_info("--. A80 mipi_dsi_panel_power on=%d\n", on);
    }
    return 0;
}
// --- ASUS_BSP : A68 & A80 miniporting

static char mipi_dsi_splash_is_enabled(void);   //Louis: porting for A80
static struct mipi_dsi_platform_data mipi_dsi_pdata = {
	.dsi_power_save = mipi_dsi_panel_power,
    .splash_is_enabled = mipi_dsi_splash_is_enabled, //Louis: porting for A80
};

#if 0 // +++ ASUS_miniporting :Louis
static bool lvds_power_on;
static int lvds_panel_power(int on)
{
	static struct regulator *reg_lvs7, *reg_l2, *reg_ext_3p3v;
	static int gpio36, gpio26, mpp3;
	int rc;

	pr_debug("%s: on=%d\n", __func__, on);

	if (!lvds_power_on) {
		reg_lvs7 = regulator_get(&msm_lvds_device.dev,
				"lvds_vdda");
		if (IS_ERR_OR_NULL(reg_lvs7)) {
			pr_err("could not get 8921_lvs7, rc = %ld\n",
				PTR_ERR(reg_lvs7));
			return -ENODEV;
		}

		reg_l2 = regulator_get(&msm_lvds_device.dev,
				"lvds_pll_vdda");
		if (IS_ERR_OR_NULL(reg_l2)) {
			pr_err("could not get 8921_l2, rc = %ld\n",
				PTR_ERR(reg_l2));
			return -ENODEV;
		}

		rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
		if (rc) {
			pr_err("set_voltage l2 failed, rc=%d\n", rc);
			return -EINVAL;
		}

		reg_ext_3p3v = regulator_get(&msm_lvds_device.dev,
			"lvds_vccs_3p3v");
		if (IS_ERR_OR_NULL(reg_ext_3p3v)) {
			pr_err("could not get reg_ext_3p3v, rc = %ld\n",
			       PTR_ERR(reg_ext_3p3v));
		    return -ENODEV;
		}

		gpio26 = PM8921_GPIO_PM_TO_SYS(26);
		rc = gpio_request(gpio26, "pwm_backlight_ctrl");
		if (rc) {
			pr_err("request gpio 26 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		gpio36 = PM8921_GPIO_PM_TO_SYS(36); /* lcd1_pwr_en_n */
		rc = gpio_request(gpio36, "lcd1_pwr_en_n");
		if (rc) {
			pr_err("request gpio 36 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		mpp3 = PM8921_MPP_PM_TO_SYS(3);
		rc = gpio_request(mpp3, "backlight_en");
		if (rc) {
			pr_err("request mpp3 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		lvds_power_on = true;
	}

	if (on) {
		rc = regulator_enable(reg_lvs7);
		if (rc) {
			pr_err("enable lvs7 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_set_optimum_mode(reg_l2, 100000);
		if (rc < 0) {
			pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
			return -EINVAL;
		}
		rc = regulator_enable(reg_l2);
		if (rc) {
			pr_err("enable l2 failed, rc=%d\n", rc);
			return -ENODEV;
		}

		rc = regulator_enable(reg_ext_3p3v);
		if (rc) {
			pr_err("enable reg_ext_3p3v failed, rc=%d\n", rc);
			return -ENODEV;
		}

		gpio_set_value_cansleep(gpio36, 0);
		gpio_set_value_cansleep(mpp3, 1);
	} else {
		gpio_set_value_cansleep(mpp3, 0);
		gpio_set_value_cansleep(gpio36, 1);

		rc = regulator_disable(reg_lvs7);
		if (rc) {
			pr_err("disable reg_lvs7 failed, rc=%d\n", rc);
			return -ENODEV;
		}
		rc = regulator_disable(reg_l2);
		if (rc) {
			pr_err("disable reg_l2 failed, rc=%d\n", rc);
			return -ENODEV;
		}
		rc = regulator_disable(reg_ext_3p3v);
		if (rc) {
			pr_err("disable reg_ext_3p3v failed, rc=%d\n", rc);
			return -ENODEV;
		}
	}

	return 0;
}

static int lvds_pixel_remap(void)
{
	if (machine_is_apq8064_cdp() ||
	    machine_is_apq8064_liquid()) {
		u32 ver = socinfo_get_platform_version(); //+++ ASUS_BSP : miniporting
		if ((SOCINFO_VERSION_MAJOR(ver) == 1) &&
		    (SOCINFO_VERSION_MINOR(ver) == 0))
			return LVDS_PIXEL_MAP_PATTERN_1;
	} else if (machine_is_mpq8064_dtv()) {
		return LVDS_PIXEL_MAP_PATTERN_2;
	}
	return 0;
}

static struct lcdc_platform_data lvds_pdata = {
	.lcdc_power_save = lvds_panel_power,
	.lvds_pixel_remap = lvds_pixel_remap
};

#define LPM_CHANNEL 2
static int lvds_chimei_gpio[] = {LPM_CHANNEL};

static struct lvds_panel_platform_data lvds_chimei_pdata = {
	.gpio = lvds_chimei_gpio,
};

static struct platform_device lvds_chimei_panel_device = {
	.name = "lvds_chimei_wxga",
	.id = 0,
	.dev = {
		.platform_data = &lvds_chimei_pdata,
	}
};

#define FRC_GPIO_UPDATE	(SX150X_EXP4_GPIO_BASE + 8)
#define FRC_GPIO_RESET	(SX150X_EXP4_GPIO_BASE + 9)
#define FRC_GPIO_PWR	(SX150X_EXP4_GPIO_BASE + 10)

static int lvds_frc_gpio[] = {FRC_GPIO_UPDATE, FRC_GPIO_RESET, FRC_GPIO_PWR};
static struct lvds_panel_platform_data lvds_frc_pdata = {
	.gpio = lvds_frc_gpio,
};

static struct platform_device lvds_frc_panel_device = {
	.name = "lvds_frc_fhd",
	.id = 0,
	.dev = {
		.platform_data = &lvds_frc_pdata,
	}
};

static int dsi2lvds_gpio[2] = {
	LPM_CHANNEL,/* Backlight PWM-ID=0 for PMIC-GPIO#24 */
	0x1F08 /* DSI2LVDS Bridge GPIO Output, mask=0x1f, out=0x08 */
};
static struct msm_panel_common_pdata mipi_dsi2lvds_pdata = {
	.gpio_num = dsi2lvds_gpio,
};

static struct platform_device mipi_dsi2lvds_bridge_device = {
	.name = "mipi_tc358764",
	.id = 0,
	.dev.platform_data = &mipi_dsi2lvds_pdata,
};

static int toshiba_gpio[] = {LPM_CHANNEL};
static struct mipi_dsi_panel_platform_data toshiba_pdata = {
	.gpio = toshiba_gpio,
};

static struct platform_device mipi_dsi_toshiba_panel_device = {
	.name = "mipi_toshiba",
	.id = 0,
	.dev = {
			.platform_data = &toshiba_pdata,
	}
};
#endif  // --- ASUS_miniporting: Louis

//+++ ASUS_BSP: miniporting
static struct mipi_dsi_phy_ctrl dsi_novatek_cmd_mode_phy_db = {
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

static struct mipi_dsi_panel_platform_data novatek_pdata = {
    .phy_ctrl_settings = &dsi_novatek_cmd_mode_phy_db,
};

static struct platform_device mipi_dsi_novatek_panel_device = {
    .name = "mipi_novatek",
    .id = 0,
    .dev = {
        .platform_data = &novatek_pdata,
    }
};
//--- ASUS_BSP: miniporting 

//+++ ASUS_BSP: A80 miniporting 
static struct mipi_dsi_phy_ctrl dsi_renesas_video_mode_phy_db = {
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

static struct mipi_dsi_panel_platform_data renesas_pdata = {
    .phy_ctrl_settings = &dsi_renesas_video_mode_phy_db,
};

static struct platform_device mipi_dsi_renesas_panel_device = {
    .name = "mipi_novatek", //Louis: use novatek panel driver
    .id = 0,
    .dev = {
        .platform_data = &renesas_pdata,
    }
};
//--- ASUS_BSP: A80 miniporting 

static struct msm_bus_vectors dtv_bus_init_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = 0,
	},
};

static struct msm_bus_vectors dtv_bus_def_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 566092800 * 2,
		.ib = 707616000 * 2,
	},
};

static struct msm_bus_paths dtv_bus_scale_usecases[] = {
	{
		ARRAY_SIZE(dtv_bus_init_vectors),
		dtv_bus_init_vectors,
	},
	{
		ARRAY_SIZE(dtv_bus_def_vectors),
		dtv_bus_def_vectors,
	},
};
static struct msm_bus_scale_pdata dtv_bus_scale_pdata = {
	dtv_bus_scale_usecases,
	ARRAY_SIZE(dtv_bus_scale_usecases),
	.name = "dtv",
};

static struct lcdc_platform_data dtv_pdata = {
	.bus_scale_table = &dtv_bus_scale_pdata,
	.lcdc_power_save = hdmi_panel_power,
};

static int hdmi_panel_power(int on)
{
	int rc;

	pr_debug("%s: HDMI Core: %s\n", __func__, (on ? "ON" : "OFF"));
	rc = hdmi_core_power(on, 1);
#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL_CEC_SUPPORT
	if (rc)
		rc = hdmi_cec_power(on);
#endif
	pr_debug("%s: HDMI Core: %s Success\n", __func__, (on ? "ON" : "OFF"));
	return rc;
}

static int hdmi_enable_5v(int on)
{
#if 0 //Mickey+++
	/* TBD: PM8921 regulator instead of 8901 */
	static struct regulator *reg_8921_hdmi_mvs;	/* HDMI_5V */
	static int prev_on;
	int rc;

	if (on == prev_on)
		return 0;

	if (!reg_8921_hdmi_mvs) {
		reg_8921_hdmi_mvs = regulator_get(&hdmi_msm_device.dev,
			"hdmi_mvs");
		if (IS_ERR(reg_8921_hdmi_mvs)) {
			pr_err("could not get reg_8921_hdmi_mvs, rc = %ld\n",
				PTR_ERR(reg_8921_hdmi_mvs));
			reg_8921_hdmi_mvs = NULL;
			return -ENODEV;
		}
	}

	if (on) {
		rc = regulator_enable(reg_8921_hdmi_mvs);
		if (rc) {
			pr_err("'%s' regulator enable failed, rc=%d\n",
				"8921_hdmi_mvs", rc);
			return rc;
		}
		pr_debug("%s(on): success\n", __func__);
	} else {
		rc = regulator_disable(reg_8921_hdmi_mvs);
		if (rc)
			pr_warning("'%s' regulator disable failed, rc=%d\n",
				"8921_hdmi_mvs", rc);
		pr_debug("%s(off): success\n", __func__);
	}

	prev_on = on;
#endif //Mickey---
	return 0;
}

//Mickey+++, porting for A68
static int hdmi_core_power(int on, int show)
{
	static struct regulator *reg_8921_lvs7, *reg_8921_s4;//, *reg_ext_3p3v;
	static int prev_on;
	int rc;

	if (on == prev_on)
		return 0;

#if 0
	/* TBD: PM8921 regulator instead of 8901 */
	if (!reg_ext_3p3v) {
		reg_ext_3p3v = regulator_get(&hdmi_msm_device.dev,
					     "hdmi_mux_vdd");
		if (IS_ERR_OR_NULL(reg_ext_3p3v)) {
			pr_err("could not get reg_ext_3p3v, rc = %ld\n",
			       PTR_ERR(reg_ext_3p3v));
			reg_ext_3p3v = NULL;
			return -ENODEV;
		}
	}
#endif
	if (!reg_8921_lvs7) {
		reg_8921_lvs7 = regulator_get(&hdmi_msm_device.dev,
					      "hdmi_vdda");
		if (IS_ERR(reg_8921_lvs7)) {
			pr_err("could not get reg_8921_lvs7, rc = %ld\n",
				PTR_ERR(reg_8921_lvs7));
			reg_8921_lvs7 = NULL;
			return -ENODEV;
		}
	}
	if (!reg_8921_s4) {
		reg_8921_s4 = regulator_get(&hdmi_msm_device.dev,
					    "hdmi_lvl_tsl");
		if (IS_ERR(reg_8921_s4)) {
			pr_err("could not get reg_8921_s4, rc = %ld\n",
				PTR_ERR(reg_8921_s4));
			reg_8921_s4 = NULL;
			return -ENODEV;
		}
		rc = regulator_set_voltage(reg_8921_s4, 1800000, 1800000);
		if (rc) {
			pr_err("set_voltage failed for 8921_s4, rc=%d\n", rc);
			return -EINVAL;
		}
	}

	if (on) {
#if 0
		/*
		 * Configure 3P3V_BOOST_EN as GPIO, 8mA drive strength,
		 * pull none, out-high
		 */
		rc = regulator_set_optimum_mode(reg_ext_3p3v, 290000);
		if (rc < 0) {
			pr_err("set_optimum_mode ext_3p3v failed, rc=%d\n", rc);
			return -EINVAL;
		}

		rc = regulator_enable(reg_ext_3p3v);
		if (rc) {
			pr_err("enable reg_ext_3p3v failed, rc=%d\n", rc);
			return rc;
		}
#endif
		rc = regulator_enable(reg_8921_lvs7);
		if (rc) {
			pr_err("'%s' regulator enable failed, rc=%d\n",
				"hdmi_vdda", rc);
			goto error1;
		}
		rc = regulator_enable(reg_8921_s4);
		if (rc) {
			pr_err("'%s' regulator enable failed, rc=%d\n",
				"hdmi_lvl_tsl", rc);
			goto error2;
		}
		pr_debug("%s(on): success\n", __func__);
	} else {
#if 0
		rc = regulator_disable(reg_ext_3p3v);
		if (rc) {
			pr_err("disable reg_ext_3p3v failed, rc=%d\n", rc);
			return -ENODEV;
		}
#endif
		rc = regulator_disable(reg_8921_lvs7);
		if (rc) {
			pr_err("disable reg_8921_l23 failed, rc=%d\n", rc);
			return -ENODEV;
		}
		rc = regulator_disable(reg_8921_s4);
		if (rc) {
			pr_err("disable reg_8921_s4 failed, rc=%d\n", rc);
			return -ENODEV;
		}
		pr_debug("%s(off): success\n", __func__);
	}

	prev_on = on;

	return 0;

error2:
	regulator_disable(reg_8921_lvs7);
error1:
	//regulator_disable(reg_ext_3p3v);
	return rc;
}

static int hdmi_gpio_config(int on)
{
	int rc = 0;
	static int prev_on;
	//int pmic_gpio14 = PM8921_GPIO_PM_TO_SYS(14);

	if (on == prev_on)
		return 0;

	if (on) {
		rc = gpio_request(HDMI_DDC_CLK_GPIO, "HDMI_DDC_CLK");
		if (rc) {
			pr_err("'%s'(%d) gpio_request failed, rc=%d\n",
				"HDMI_DDC_CLK", HDMI_DDC_CLK_GPIO, rc);
			goto error1;
		}
		rc = gpio_request(HDMI_DDC_DATA_GPIO, "HDMI_DDC_DATA");
		if (rc) {
			pr_err("'%s'(%d) gpio_request failed, rc=%d\n",
				"HDMI_DDC_DATA", HDMI_DDC_DATA_GPIO, rc);
			goto error2;
		}
		rc = gpio_request(HDMI_HPD_GPIO, "HDMI_HPD");
		if (rc) {
			pr_err("'%s'(%d) gpio_request failed, rc=%d\n",
				"HDMI_HPD", HDMI_HPD_GPIO, rc);
			goto error3;
		}
#if 0
		if (machine_is_apq8064_liquid()) {
			rc = gpio_request(pmic_gpio14, "PMIC_HDMI_MUX_SEL");
			if (rc) {
				pr_err("'%s'(%d) gpio_request failed, rc=%d\n",
					"PMIC_HDMI_MUX_SEL", 14, rc);
				goto error4;
			}
			gpio_set_value_cansleep(pmic_gpio14, 0);
		}
#endif
		pr_debug("%s(on): success\n", __func__);
	} else {
		gpio_free(HDMI_DDC_CLK_GPIO);
		gpio_free(HDMI_DDC_DATA_GPIO);
		gpio_free(HDMI_HPD_GPIO);
#if 0
		if (machine_is_apq8064_liquid()) {
			gpio_set_value_cansleep(pmic_gpio14, 1);
			gpio_free(pmic_gpio14);
		}
#endif
		pr_debug("%s(off): success\n", __func__);
	}

	prev_on = on;
	return 0;

//error4:
//	gpio_free(HDMI_HPD_GPIO);
error3:
	gpio_free(HDMI_DDC_DATA_GPIO);
error2:
	gpio_free(HDMI_DDC_CLK_GPIO);
error1:
	return rc;
}
//Mickey---

// +++ Louis
#include <linux/fb.h> 

struct fb_info * asus_get_fb_info(int fb_num);
void asus_update_screen(struct fb_var_screeninfo *var, struct fb_info *info);
bool update_screen_flag = false;
extern void asus_mdp_dsi_clk_ctrl(struct fb_info *info, int enable);

void asus_draw_last_screen(u32 img_color)
{
    unsigned char *src_addr, *dest_addr;
    char img_col[4];
    unsigned int pixels_num = 0;
    struct fb_info * fbi = asus_get_fb_info(0);
    u32 tmp_yoffset;
    u32 tmp_ysride;

    update_screen_flag = true;

    img_col[0] = (img_color & 0xFF000000) >> 24;
    img_col[1] = (img_color & 0x00FF0000) >> 16;
    img_col[2] = (img_color & 0x0000FF00) >> 8;
    img_col[3] = (img_color & 0x000000FF) ;

    tmp_yoffset = fbi->var.yoffset;
    tmp_ysride = fbi->fix.line_length;

    fbi->fix.line_length = 720; //ystride
    fbi->var.yoffset = 1280 * 3;

    src_addr = (unsigned char *) __va((fbi->fix.smem_start)) +  fbi->var.yoffset * fbi->fix.line_length;

    dest_addr = src_addr;

    memcpy(dest_addr, img_col, sizeof(img_col)); //copy first 4 byte
    pixels_num += 1;    //handle first pixel

    while (pixels_num < 720 * 1280 / 2)
    {
        memcpy(dest_addr + 4 * pixels_num, src_addr, 4 * pixels_num);
        pixels_num = pixels_num * 2;
    }

    if (pixels_num < 720 * 1280) {
        memcpy(dest_addr + 4 * pixels_num, src_addr, 4 * (720 * 1280 - pixels_num));
    }

    //mdp4_overlay_vsync_ctrl(fbi, 1);
    asus_mdp_dsi_clk_ctrl(fbi, 1);
    asus_update_screen(&(fbi->var),fbi);
    asus_mdp_dsi_clk_ctrl(fbi, 0);
    //mdp4_overlay_vsync_ctrl(fbi, 0);

    fbi->var.yoffset = tmp_yoffset;
    fbi->fix.line_length = tmp_ysride;

    update_screen_flag = false; //make sure to set false for sending vsync
    return;
}
EXPORT_SYMBOL(asus_draw_last_screen);
// --- Louis

#ifdef CONFIG_FB_MSM_HDMI_MSM_PANEL_CEC_SUPPORT
static int hdmi_cec_power(int on)
{
	static int prev_on;
	int rc;

	if (on == prev_on)
		return 0;

	if (on) {
		rc = gpio_request(HDMI_CEC_VAR_GPIO, "HDMI_CEC_VAR");
		if (rc) {
			pr_err("'%s'(%d) gpio_request failed, rc=%d\n",
				"HDMI_CEC_VAR", HDMI_CEC_VAR_GPIO, rc);
			goto error;
		}
		pr_debug("%s(on): success\n", __func__);
	} else {
		gpio_free(HDMI_CEC_VAR_GPIO);
		pr_debug("%s(off): success\n", __func__);
	}

	prev_on = on;

	return 0;
error:
	return rc;
}
#endif

void __init apq8064_init_fb(void)
{
	platform_device_register(&msm_fb_device);
//ASUS_BSP: miniporting +++
    if (g_A68_hwID < A80_EVB) {
        printk("[Display][A68] mipi_dsi_novatek_panel_device :platform_device_register\n");
        platform_device_register(&mipi_dsi_novatek_panel_device);
    }
    else { 
        printk("[Display][A80] mipi_dsi_renesas_panel_device :platform_device_register\n");
        platform_device_register(&mipi_dsi_renesas_panel_device);
    }
//	platform_device_register(&lvds_chimei_panel_device);
//ASUS_BSP: miniporting ---
#ifdef CONFIG_FB_MSM_WRITEBACK_MSM_PANEL
	platform_device_register(&wfd_panel_device);
	platform_device_register(&wfd_device);
#endif
#if 0 //+++ ASUS_BSP: miniporting
	if (machine_is_apq8064_liquid())
		platform_device_register(&mipi_dsi2lvds_bridge_device);
	if (machine_is_apq8064_mtp())
		platform_device_register(&mipi_dsi_toshiba_panel_device);
	if (machine_is_mpq8064_dtv())
		platform_device_register(&lvds_frc_panel_device);
#endif //--- ASUS_BSP: miniporting
	msm_fb_register_device("mdp", &mdp_pdata);
//	msm_fb_register_device("lvds", &lvds_pdata);    //+++ ASUS_BSP miniporting
	msm_fb_register_device("mipi_dsi", &mipi_dsi_pdata);
	platform_device_register(&hdmi_msm_device);
	msm_fb_register_device("dtv", &dtv_pdata);
}

/**
 * Set MDP clocks to high frequency to avoid DSI underflow
 * when using high resolution 1200x1920 WUXGA panels
 */
static void set_mdp_clocks_for_wuxga(void)
{
	mdp_ui_vectors[0].ab = 2000000000;
	mdp_ui_vectors[0].ib = 2000000000;
	mdp_vga_vectors[0].ab = 2000000000;
	mdp_vga_vectors[0].ib = 2000000000;
	mdp_720p_vectors[0].ab = 2000000000;
	mdp_720p_vectors[0].ib = 2000000000;
	mdp_1080p_vectors[0].ab = 2000000000;
	mdp_1080p_vectors[0].ib = 2000000000;

	if (apq8064_hdmi_as_primary_selected()) {
		dtv_bus_def_vectors[0].ab = 2000000000;
		dtv_bus_def_vectors[0].ib = 2000000000;
	}
}

void __init apq8064_set_display_params(char *prim_panel, char *ext_panel,
		unsigned char resolution)
{
	/*
	 * For certain MPQ boards, HDMI should be set as primary display
	 * by default, with the flexibility to specify any other panel
	 * as a primary panel through boot parameters.
	 */
	if (machine_is_mpq8064_hrd() || machine_is_mpq8064_cdp()) {
		pr_debug("HDMI is the primary display by default for MPQ\n");
		if (!strnlen(prim_panel, PANEL_NAME_MAX_LEN))
			strlcpy(msm_fb_pdata.prim_panel_name, HDMI_PANEL_NAME,
				PANEL_NAME_MAX_LEN);
	}

	if (strnlen(prim_panel, PANEL_NAME_MAX_LEN)) {
		strlcpy(msm_fb_pdata.prim_panel_name, prim_panel,
			PANEL_NAME_MAX_LEN);
		pr_debug("msm_fb_pdata.prim_panel_name %s\n",
			msm_fb_pdata.prim_panel_name);

		if (!strncmp((char *)msm_fb_pdata.prim_panel_name,
			HDMI_PANEL_NAME, strnlen(HDMI_PANEL_NAME,
				PANEL_NAME_MAX_LEN))) {
			pr_debug("HDMI is the primary display by"
				" boot parameter\n");
			hdmi_is_primary = 1;
			set_mdp_clocks_for_wuxga();
		}
	}
	if (strnlen(ext_panel, PANEL_NAME_MAX_LEN)) {
		strlcpy(msm_fb_pdata.ext_panel_name, ext_panel,
			PANEL_NAME_MAX_LEN);
		pr_debug("msm_fb_pdata.ext_panel_name %s\n",
			msm_fb_pdata.ext_panel_name);
	}

	msm_fb_pdata.ext_resolution = resolution;
}

//+++ Louis: A80 miniporting
static char mipi_dsi_splash_is_enabled(void)
{
    return mdp_pdata.cont_splash_enabled;
}
//--- Louis: A80 miniporting
