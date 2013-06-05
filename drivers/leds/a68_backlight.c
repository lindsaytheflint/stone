/*
 * leds-msm-pmic.c - MSM PMIC LEDs driver.
 *
 * Copyright (c) 2009, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <mach/pmic.h>
#include <linux/pwm.h>
#include <linux/mfd/pm8xxx/pm8921.h>
#include <linux/time.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <mach/board.h>
#include <linux/leds.h>
#include <mach/gpio.h>
#include <mach/irqs.h>
#include <linux/microp_notify.h>
#include "../video/msm/mipi_novatek.h"
#include <linux/microp.h>
#include <linux/microp_api.h>
#include <linux/microp_pin_def.h>

#define A68_PWM_FREQ_HZ 22000L
#define A68_PWM_PERIOD_USEC (USEC_PER_SEC / A68_PWM_FREQ_HZ)
#define A68_PWM_LEVEL 255L
#define A68_PWM_DUTY_LEVEL \
    (A68_PWM_PERIOD_USEC * 2550L / A68_PWM_LEVEL)

#define MAX_BACKLIGHT_BRIGHTNESS 255
#define MIN_BACKLIGHT_BRIGHTNESS 0
#define PM8921_GPIO_BASE        NR_GPIO_IRQS
#define PM8921_GPIO_PM_TO_SYS(pm_gpio)  (pm_gpio - 1 + PM8921_GPIO_BASE)

int a68_set_backlight(int);
int p03_set_backlight(int);
static int a80_set_backlight(int);
static struct a68_backlight_data *backlight_pdata;
static struct pwm_device *bl_lpm;
static int backlight_value = 11;
int backlight_mode_state = 0;

extern int AX_MicroP_setPWMValue(uint8_t);

static struct workqueue_struct *backlight_workqueue;
static struct delayed_work turn_off_panel_work;

enum backlight_mode {
    phone = 0,
    pad,
};

static int a80_set_backlight(value)
{
    int index = 0;

    index = value;
    if (value >= 255)
        index = 255;
    renesas_set_brightness(0, index);

    return 0;
}

int a68_set_backlight(value)
{
    int ret, duty_us;
    int index = 0;
    static bool CABC_On = true;

    if(value >= 2000 && value <= 2255) {
        value -= 2000;
    }

    if (g_A68_hwID >= A68_SR2)  //driver ic support
    {
        if (value == 0 || value == 1000) {
            printk("[BL] turn off A68 backlight\n");
            sharp_set_brightness(0);
            return 0;
        }

#ifdef ASUS_FACTORY_BUILD
        if (g_A68_hwID == A68_SR2) 
        {
            index = ((value - 20) * ((153*10000)/ 235)) / 10000 + 8;
            //factory: 20~550nits

            if (index >= 160) {
                index = 160;
            }
            else if (index <= 0) {
                index = 0;
            }
        }
        else    //for ER
        {
            index = ((value - 20) * ((245*10000)/ 235)) / 10000 + 11;
            //20~255 mapping 11~255
            if (index >= 255) {
                index = 255;
            }
            else if (index <= 0) {
                index = 0;
            }
        }
#else
        if (value <= 255)   //normal mode
        {
            if (g_A68_hwID == A68_SR2) 
            {
                index = ((value - 20) * ((80*10000)/ 235)) / 10000 + 8;
                //20~255 mapping 8~87; max:300nits, min:20nits (3%), default:100nits (12%)

                if (index >= 87) {
                    index = 87;
                }
                else if (index <= 0) {
                    index = 0;
                }
            }
            else 
            {
                index = ((value - 20) * ((125*10000)/ 235)) / 10000 + 11;
                //20~255 mapping 11~135; max:300nits, min:20nits, default:100nits(17%)

                if (index >= 135) {
                    index = 135;
                }
                else if (index <= 0) {
                    index = 0;
                }
            }
        }
        else if (value > 1000 && value <= 1255) //outdoor mode
        {
            if (g_A68_hwID == A68_SR2) 
            {
                index = ((value - 1020) * ((120*10000)/ 235)) / 10000 + 41;
                //1020~1255 mapping 41~160; max:550nits, min:140nits(16%)

                if (index >= 160) {
                    index = 160;
                }
                else if (index <= 0) {
                    index = 0;
                }
            }
            else
            {
                index = ((value - 1020) * ((192*10000)/ 235)) / 10000 + 64;
                //1020~1255 mapping 64~255; max:550nits, min:140nits(25%)

                if (index >= 255) {
                    index = 255;
                }
                else if (index <= 0) {
                    index = 0;
                }
            }
        }
#endif
// ++ cabc on/off
        if (index <= 28 && CABC_On == true)
        {
            sharp_set_cabc(0);
            CABC_On = false;
        }
        else if (index > 28 && CABC_On == false)
        {
            sharp_set_cabc(3);
            CABC_On = true;
        }
// -- cabc on/off

        sharp_set_brightness(index);
    }

    else  //pmic support
    {
        if (bl_lpm) 
        {
            if(value == MAX_BACKLIGHT_BRIGHTNESS) {
                duty_us = A68_PWM_PERIOD_USEC;
                ret = pwm_config(bl_lpm, 
                        duty_us, A68_PWM_PERIOD_USEC);
            }
            else {
                ret = pwm_config(bl_lpm, 
                        A68_PWM_DUTY_LEVEL * (long) value / 2550L, A68_PWM_PERIOD_USEC);
            }

            if (ret) {
                pr_err("pwm_config on lpm failed %d\n", ret);
                return ret;
            }

            if (value) {
                ret = pwm_enable(bl_lpm);
                if (ret)
                    pr_err("pwm enable/disable on lpm failed"
                        "for bl =(%d)\n",  value);
            } else {
                pwm_disable(bl_lpm);
            }
        }
    }
    return 0;
}

int p03_set_backlight(int value)
{
    int ret, index = 0;
	static int previous_value;
    if (value == 0 || value == 1000 || value == 2000) {
        printk("[BL] turn off P03 backlight\n");
        AX_MicroP_setPWMValue(0);
        queue_delayed_work(backlight_workqueue, &turn_off_panel_work, msecs_to_jiffies(3000));
        previous_value = 0;
        return 0;
    }

    if (value > 2000 && value <= 2255)  //auto mode 30~300nits
    {
        value -= 2000;
        index = ((value - 20) * ((230*10000)/ 235)) / 10000 + 32;

        if (index >= 255) {
            index = 255;
        }
        else if (index <= 0) {
            index = 0;
        }
    }
    else if (value <= 255)   //normal mode
    {
        index = ((value - 20) * ((136*10000)/ 235)) / 10000 + 18;
        //20~255 mapping 18~154; max:180nits, min:20nits (7%), default:100nits (33%)

        if (index >= 154) {
            index = 154;
        }
        else if (index <= 0) {
            index = 0;
        }
    }
    else if (value > 1000 && value <= 1255) //outdoor mode
    {
        index = ((value - 1020) * ((137*10000)/ 235)) / 10000 + 118;
        //1020~1255 mapping 118~255; max:300nits, min:140nits (46%)

        if (index >= 255) {
            index = 255;
        }
        else if (index <= 0) {
            index = 0;
        }
    }

    ret = AX_MicroP_setPWMValue(index);

    if (ret < 0) {
        printk("(%s): P03 set backlight fail\n", __func__);
    }

    if ((previous_value == 0) && (index > 0))
    {
        if (delayed_work_pending(&turn_off_panel_work))
        {
            cancel_delayed_work_sync(&turn_off_panel_work);
        }
        AX_MicroP_setGPIOOutputPin(OUT_uP_LCD_EN,1);
        printk("[BL] (%s): P03 turn on panel\n", __func__);
    }
    previous_value = index;

    return ret;
}

static int lcd_backlight_registered;
static void set_bl_brightness(struct led_classdev *led_cdev,
                    enum led_brightness value)
{
    static bool bFirst = true;
    int rc;
    struct pm_gpio gpio26_param = {
        .direction = PM_GPIO_DIR_OUT,
        .output_buffer = PM_GPIO_OUT_BUF_CMOS,
        .output_value = 0,
        .pull = PM_GPIO_PULL_NO,
        .vin_sel = 2,
        .out_strength = PM_GPIO_STRENGTH_HIGH,
        .function = PM_GPIO_FUNC_2,
        .inv_int_pol = 0,
        .disable_pin = 0,
    };

    if (g_A68_hwID < A68_SR2)
    {
        if(bFirst) 
        {
            rc = pm8xxx_gpio_config(PM8921_GPIO_PM_TO_SYS(26), &gpio26_param);
            if (rc) {
                pr_err("gpio_config 26 failed (2), rc=%d\n", rc);
                return;
            }
            bFirst = false;
        }
    }

    backlight_value = value;

    if (g_A68_hwID < A80_EVB) 
    {
        if (backlight_mode_state == phone) {
            a68_set_backlight(backlight_value);
        }
        else if (backlight_mode_state == pad) {
            p03_set_backlight(backlight_value);
        }
    }
    else
    {
        if (backlight_mode_state == phone) {
            a80_set_backlight(backlight_value);
        }
        else if (backlight_mode_state == pad) {

        }
    }
}

static void set_p03_panel_off_func(struct work_struct *work)
{
    printk("[BL] (%s): P03 turn off panel\n", __func__);
    AX_MicroP_setGPIOOutputPin(OUT_uP_LCD_EN,0);
    AX_MicroP_setGPIOOutputPin(OUT_uP_PAD_LOW_BAT,0);
}

static struct led_classdev a68_backlight_led = {
    .name       = "lcd-backlight",
    .brightness = MAX_BACKLIGHT_BRIGHTNESS,
    .brightness_set = set_bl_brightness,
};

static int __devinit a68_backlight_probe(struct platform_device *pdev)
{
    backlight_pdata = pdev->dev.platform_data;

    if (backlight_pdata == NULL) {
        pr_err("%s.invalid platform data.\n", __func__);
        return -ENODEV;
    }

    if (backlight_pdata != NULL) {
        bl_lpm = pwm_request(backlight_pdata->gpio[0],
            "backlight");
    }

    if (bl_lpm == NULL || IS_ERR(bl_lpm)) {
        pr_err("%s pwm_request() failed\n", __func__);
        bl_lpm = NULL;
    }
    pr_debug("bl_lpm = %p lpm = %d\n", bl_lpm,
        backlight_pdata->gpio[0]);

    if (led_classdev_register(&pdev->dev, &a68_backlight_led))
    {
        printk(KERN_ERR "led_classdev_register failed\n");            
    }
    else
    {
        lcd_backlight_registered = 1;
    }

    backlight_workqueue  = create_singlethread_workqueue("P03BACKLIGHTWORKQUEUE");
    INIT_DELAYED_WORK(&turn_off_panel_work, set_p03_panel_off_func);

    return 0;
}

static int a68_backlight_remove(struct platform_device *pdev)
{
    if (lcd_backlight_registered) {
        lcd_backlight_registered = 0;
        led_classdev_unregister(&a68_backlight_led);
    }
    return 0;
}

static int change_backlight_mode(struct notifier_block *this, unsigned long event, void *ptr)
{
        switch (event) {
        case P01_ADD:
                backlight_mode_state = pad;
                //p03_set_backlight(backlight_value);   //plug-in/out set bl from led-class
                return NOTIFY_DONE;

        case P01_REMOVE:
                backlight_mode_state = phone;
                //a68_set_backlight(backlight_value);   //plug-in/out set bl from led-class
                return NOTIFY_DONE;

        default:
                return NOTIFY_DONE;
        }
}

static struct notifier_block my_hs_notifier = {
        .notifier_call = change_backlight_mode,
        .priority = VIBRATOR_MP_NOTIFY,
};

static struct platform_driver this_driver = {
    .probe  = a68_backlight_probe,
    .remove = a68_backlight_remove,
    .driver = {
        .name   = "a68_backlight",
    },
};

static int __init msm_pmic_led_init(void)
{
    register_microp_notifier(&my_hs_notifier);
    return platform_driver_register(&this_driver);
}
module_init(msm_pmic_led_init);

static void __exit msm_pmic_led_exit(void)
{
    platform_driver_unregister(&this_driver);
}
module_exit(msm_pmic_led_exit);

MODULE_DESCRIPTION("MSM PMIC8921 A68 backlight driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:board-8064");
