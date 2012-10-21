/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  publishhed by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/mfp-pxa910.h>
#include <mach/pxa910.h>
#include <mach/irqs.h>

#include <plat/generic.h>
#include <plat/i2c.h>
#include <linux/spi/spi.h>

#include "../common.h"
#include <mach/pxa910fb.h>

static void (*spi_send)(struct pxa910fb_info *, void *, int , unsigned int );
#define WVGA_SHARP
#ifdef WVGA_SHARP

static unsigned long sharp_lcd_pin_config[] = {
	GPIO104_LCD_DD18,
	GPIO105_LCD_DD19,
	GPIO106_LCD_DD20,
	GPIO107_LCD_DD21,
	GPIO108_LCD_DD22,
	GPIO109_LCD_DD23,

	GPIO81_LCD_FCLK,
	GPIO82_LCD_LCLK,
	GPIO84_LCD_DENA,
};

static unsigned long sharp_lcd_gpio_pin_config[] = {
#define GPIO_SPI
#ifndef GPIO_SPI
	//GPIO106_LCD_SDI,
	//GPIO107_LCD_SDO,
	GPIO108_LCD_DCLK,
	//GPIO105_LCD_SDO,
#else
	GPIO106_GPIO106,
	GPIO108_GPIO108,
#endif

	GPIO81_GPIO81,
	GPIO82_GPIO82,
	GPIO84_GPIO84,
};

/* Sharp LS035 WVGA LCD power on cmd */
static u16 ls035_spi_cmdon1[] = {
//display on
	0x29,
//sleep out
        0x11,
};
static u16 ls035_spi_cmdon2[] = {
//addr mode setting
        0x36,
        0x100,
//pixel format setting
        0x3a,
        0x170, /*0x70(24bit), 0x60(18bit)*/
//cmd access enable
        0xb0,
        0x103,
//blc setting
        0xb8,
        0x100,
//led on/off
	0xb9, /*led, brightness*/
	0x100,
	0x1ff,
//cmd disable
	0xb0,
	0x103,
};

/* SPI emulated by GPIO. CS control and GPIOs request should be done by caller */
static void gpio_spi_send(u32 clk_gpio, u32 d_gpio, u16 *dat, u32 size, u32 bit_len)
{
	u32 bit_cnt = bit_len;
	u16 *val = dat;

	for(; size; size --){
		bit_cnt = bit_len;
		while(bit_cnt){
			bit_cnt --;
			gpio_set_value(clk_gpio, 0);
			gpio_set_value(d_gpio, (*val >> bit_cnt) & 1);
			udelay(1);
			gpio_set_value(clk_gpio, 1);
			udelay(1);
		}
		val ++;
	}
}

static void ls035_lcd_power(struct pxa910fb_info *fbi, unsigned int spi_gpio_cs, unsigned int spi_gpio_reset, int on)
{
	int cs_gpio, rst_gpio;

	printk("enter <%s>.......\n", __func__);
#define SCK_PIN 108
#define SDO_PIN 106

	if (on) {
		printk("power on WVGA LCD..\n");
		mfp_config(ARRAY_AND_SIZE(sharp_lcd_gpio_pin_config));
		rst_gpio = mfp_to_gpio(MFP_PIN_GPIO16);
		cs_gpio = mfp_to_gpio(MFP_PIN_GPIO18);
		gpio_request(rst_gpio, "LCD RST");
		gpio_request(cs_gpio, "LCD CS");

		gpio_direction_output(rst_gpio, 0);
		gpio_direction_output(cs_gpio, 0);
		gpio_set_value(rst_gpio, 0);
		msleep(2);
		gpio_set_value(rst_gpio, 1);
		msleep(6);

#ifdef GPIO_SPI
		gpio_request(SCK_PIN, "LCD SPICLK");
		gpio_request(SDO_PIN, "LCD SDO");
		gpio_direction_output(SCK_PIN, 1);
		gpio_direction_output(SDO_PIN, 1);
		gpio_spi_send (SCK_PIN, SDO_PIN, ls035_spi_cmdon1, ARRAY_SIZE(ls035_spi_cmdon1), 9);
#else
		spi_send(fbi, ls035_spi_cmdon1,
				ARRAY_SIZE(ls035_spi_cmdon1), spi_gpio_cs);
#endif
		msleep(120);
#ifdef GPIO_SPI
		gpio_spi_send (SCK_PIN, SDO_PIN, ls035_spi_cmdon2, ARRAY_SIZE(ls035_spi_cmdon2), 9);
#else
		spi_send(fbi, ls035_spi_cmdon2,
				ARRAY_SIZE(ls035_spi_cmdon2), spi_gpio_cs);
#endif
		msleep(1);
		gpio_set_value(cs_gpio, 1);
		gpio_free(rst_gpio);
		gpio_free(cs_gpio);
#ifdef GPIO_SPI
		gpio_free(SDO_PIN);
		gpio_free(SCK_PIN);
#endif
		mfp_config(ARRAY_AND_SIZE(sharp_lcd_pin_config));
	} else {
		printk("power off lcd\n");
	}
}

static struct fb_videomode sharp_video_modes[] = {
	/* ls035 WVGA mode info */
	[0] = {
		.pixclock       = 38483,
		.refresh        = 60,
		.xres           = 480,
		.yres           = 800,
		.hsync_len      = 16,
		.left_margin    = 24,
		.right_margin   = 16,
		.vsync_len      = 2,
		.upper_margin   = 2,
		.lower_margin   = 4,
		.sync           = FB_SYNC_VERT_HIGH_ACT | FB_SYNC_HOR_HIGH_ACT,
	},
};

/* SPI Control Register. */
#define     CFG_SCLKCNT(div)                    (div<<24)  /* 0xFF~0x2 */
#define     CFG_RXBITS(rx)                      ((rx - 1)<<16)   /* 0x1F~0x1 */
#define     CFG_TXBITS(tx)                      ((tx - 1)<<8)    /* 0x1F~0x1, 0x1: 2bits ... 0x1F: 32bits */
#define     CFG_SPI_ENA(spi)                    (spi<<3)
#define     CFG_SPI_SEL(spi)                    (spi<<2)   /* 1: port1; 0: port0 */
#define     CFG_SPI_3W4WB(wire)                 (wire<<1)  /* 1: 3-wire; 0: 4-wire */


static struct pxa910fb_mach_info sharp_lcd_info  = {
	.id                     = "Base",
	.modes                  = sharp_video_modes,
	.num_modes              = ARRAY_SIZE(sharp_video_modes),
	.pix_fmt                = PIX_FMT_RGB888PACK,
	.io_pin_allocation_mode = PIN_MODE_DUMB_24,
	.dumb_mode              = DUMB_MODE_RGB888,
	.active                 = 1,
	.spi_ctrl               = CFG_SCLKCNT(16) | CFG_TXBITS(9) | CFG_SPI_SEL(0) | CFG_SPI_3W4WB(1) | CFG_SPI_ENA(1),
	.spi_gpio_cs            = -1, //44,
	.spi_gpio_reset		 = GPIO_EXT0(3),
	.pxa910fb_lcd_power	= ls035_lcd_power,
	.invert_pixclock	= 1,
	.panel_rbswap		= 1,
	.max_fb_size		= 800 * 480 * 8,
};

static struct pxa910fb_mach_info sharp_lcd_ovly_info = {
	.id                     = "Ovly",
	.modes                  = sharp_video_modes,
	.num_modes              = ARRAY_SIZE(sharp_video_modes),
	.pix_fmt                = PIX_FMT_RGB888PACK,
	.io_pin_allocation_mode = PIN_MODE_DUMB_24,
	.dumb_mode              = DUMB_MODE_RGB888,
	.active                 = 1,
        .spi_ctrl               = CFG_SCLKCNT(16) | CFG_TXBITS(9) | CFG_SPI_SEL(0) | CFG_SPI_3W4WB(1) | CFG_SPI_ENA(1),
        .spi_gpio_cs            = -1,
        .pxa910fb_lcd_power     = ls035_lcd_power,
	.invert_pixclock	= 1,
	.panel_rbswap		= 1,
};
#endif

void __init dkb_add_lcd_sharp(void)
{
	struct pxa910fb_mach_info *fb = &sharp_lcd_info, *ovly = &sharp_lcd_ovly_info;

	spi_send = pxa910fb_spi_send;
	pxa910_add_fb(fb);
	pxa910_add_fb_ovly(ovly);
}

