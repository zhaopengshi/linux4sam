/*
 * imx25 pinctrl driver.
 *
 * Copyright 2013 Eukréa Electromatique <denis@eukrea.com>
 *
 * This driver was mostly copied from the imx51 pinctrl driver which has:
 *
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro, Inc.
 *
 * Author: Denis Carikli <denis@eukrea.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <linux/err.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/pinctrl/pinctrl.h>

#include "pinctrl-imx.h"

enum imx25_pads {
	MX25_PAD_RESERVE0 = 1,
	MX25_PAD_RESERVE1 = 2,
	MX25_PAD_A10 = 3,
	MX25_PAD_A13 = 4,
	MX25_PAD_A14 = 5,
	MX25_PAD_A15 = 6,
	MX25_PAD_A16 = 7,
	MX25_PAD_A17 = 8,
	MX25_PAD_A18 = 9,
	MX25_PAD_A19 = 10,
	MX25_PAD_A20 = 11,
	MX25_PAD_A21 = 12,
	MX25_PAD_A22 = 13,
	MX25_PAD_A23 = 14,
	MX25_PAD_A24 = 15,
	MX25_PAD_A25 = 16,
	MX25_PAD_EB0 = 17,
	MX25_PAD_EB1 = 18,
	MX25_PAD_OE = 19,
	MX25_PAD_CS0 = 20,
	MX25_PAD_CS1 = 21,
	MX25_PAD_CS4 = 22,
	MX25_PAD_CS5 = 23,
	MX25_PAD_NF_CE0 = 24,
	MX25_PAD_ECB = 25,
	MX25_PAD_LBA = 26,
	MX25_PAD_BCLK = 27,
	MX25_PAD_RW = 28,
	MX25_PAD_NFWE_B = 29,
	MX25_PAD_NFRE_B = 30,
	MX25_PAD_NFALE = 31,
	MX25_PAD_NFCLE = 32,
	MX25_PAD_NFWP_B = 33,
	MX25_PAD_NFRB = 34,
	MX25_PAD_D15 = 35,
	MX25_PAD_D14 = 36,
	MX25_PAD_D13 = 37,
	MX25_PAD_D12 = 38,
	MX25_PAD_D11 = 39,
	MX25_PAD_D10 = 40,
	MX25_PAD_D9 = 41,
	MX25_PAD_D8 = 42,
	MX25_PAD_D7 = 43,
	MX25_PAD_D6 = 44,
	MX25_PAD_D5 = 45,
	MX25_PAD_D4 = 46,
	MX25_PAD_D3 = 47,
	MX25_PAD_D2 = 48,
	MX25_PAD_D1 = 49,
	MX25_PAD_D0 = 50,
	MX25_PAD_LD0 = 51,
	MX25_PAD_LD1 = 52,
	MX25_PAD_LD2 = 53,
	MX25_PAD_LD3 = 54,
	MX25_PAD_LD4 = 55,
	MX25_PAD_LD5 = 56,
	MX25_PAD_LD6 = 57,
	MX25_PAD_LD7 = 58,
	MX25_PAD_LD8 = 59,
	MX25_PAD_LD9 = 60,
	MX25_PAD_LD10 = 61,
	MX25_PAD_LD11 = 62,
	MX25_PAD_LD12 = 63,
	MX25_PAD_LD13 = 64,
	MX25_PAD_LD14 = 65,
	MX25_PAD_LD15 = 66,
	MX25_PAD_HSYNC = 67,
	MX25_PAD_VSYNC = 68,
	MX25_PAD_LSCLK = 69,
	MX25_PAD_OE_ACD = 70,
	MX25_PAD_CONTRAST = 71,
	MX25_PAD_PWM = 72,
	MX25_PAD_CSI_D2 = 73,
	MX25_PAD_CSI_D3 = 74,
	MX25_PAD_CSI_D4 = 75,
	MX25_PAD_CSI_D5 = 76,
	MX25_PAD_CSI_D6 = 77,
	MX25_PAD_CSI_D7 = 78,
	MX25_PAD_CSI_D8 = 79,
	MX25_PAD_CSI_D9 = 80,
	MX25_PAD_CSI_MCLK = 81,
	MX25_PAD_CSI_VSYNC = 82,
	MX25_PAD_CSI_HSYNC = 83,
	MX25_PAD_CSI_PIXCLK = 84,
	MX25_PAD_I2C1_CLK = 85,
	MX25_PAD_I2C1_DAT = 86,
	MX25_PAD_CSPI1_MOSI = 87,
	MX25_PAD_CSPI1_MISO = 88,
	MX25_PAD_CSPI1_SS0 = 89,
	MX25_PAD_CSPI1_SS1 = 90,
	MX25_PAD_CSPI1_SCLK = 91,
	MX25_PAD_CSPI1_RDY = 92,
	MX25_PAD_UART1_RXD = 93,
	MX25_PAD_UART1_TXD = 94,
	MX25_PAD_UART1_RTS = 95,
	MX25_PAD_UART1_CTS = 96,
	MX25_PAD_UART2_RXD = 97,
	MX25_PAD_UART2_TXD = 98,
	MX25_PAD_UART2_RTS = 99,
	MX25_PAD_UART2_CTS = 100,
	MX25_PAD_SD1_CMD = 101,
	MX25_PAD_SD1_CLK = 102,
	MX25_PAD_SD1_DATA0 = 103,
	MX25_PAD_SD1_DATA1 = 104,
	MX25_PAD_SD1_DATA2 = 105,
	MX25_PAD_SD1_DATA3 = 106,
	MX25_PAD_KPP_ROW0 = 107,
	MX25_PAD_KPP_ROW1 = 108,
	MX25_PAD_KPP_ROW2 = 109,
	MX25_PAD_KPP_ROW3 = 110,
	MX25_PAD_KPP_COL0 = 111,
	MX25_PAD_KPP_COL1 = 112,
	MX25_PAD_KPP_COL2 = 113,
	MX25_PAD_KPP_COL3 = 114,
	MX25_PAD_FEC_MDC = 115,
	MX25_PAD_FEC_MDIO = 116,
	MX25_PAD_FEC_TDATA0 = 117,
	MX25_PAD_FEC_TDATA1 = 118,
	MX25_PAD_FEC_TX_EN = 119,
	MX25_PAD_FEC_RDATA0 = 120,
	MX25_PAD_FEC_RDATA1 = 121,
	MX25_PAD_FEC_RX_DV = 122,
	MX25_PAD_FEC_TX_CLK = 123,
	MX25_PAD_RTCK = 124,
	MX25_PAD_DE_B = 125,
	MX25_PAD_GPIO_A = 126,
	MX25_PAD_GPIO_B = 127,
	MX25_PAD_GPIO_C = 128,
	MX25_PAD_GPIO_D = 129,
	MX25_PAD_GPIO_E = 130,
	MX25_PAD_GPIO_F = 131,
	MX25_PAD_EXT_ARMCLK = 132,
	MX25_PAD_UPLL_BYPCLK = 133,
	MX25_PAD_VSTBY_REQ = 134,
	MX25_PAD_VSTBY_ACK = 135,
	MX25_PAD_POWER_FAIL  = 136,
	MX25_PAD_CLKO = 137,
	MX25_PAD_BOOT_MODE0 = 138,
	MX25_PAD_BOOT_MODE1 = 139,
};

/* Pad names for the pinmux subsystem */
static const struct pinctrl_pin_desc imx25_pinctrl_pads[] = {
	IMX_PINCTRL_PIN(MX25_PAD_RESERVE0),
	IMX_PINCTRL_PIN(MX25_PAD_RESERVE1),
	IMX_PINCTRL_PIN(MX25_PAD_A10),
	IMX_PINCTRL_PIN(MX25_PAD_A13),
	IMX_PINCTRL_PIN(MX25_PAD_A14),
	IMX_PINCTRL_PIN(MX25_PAD_A15),
	IMX_PINCTRL_PIN(MX25_PAD_A16),
	IMX_PINCTRL_PIN(MX25_PAD_A17),
	IMX_PINCTRL_PIN(MX25_PAD_A18),
	IMX_PINCTRL_PIN(MX25_PAD_A19),
	IMX_PINCTRL_PIN(MX25_PAD_A20),
	IMX_PINCTRL_PIN(MX25_PAD_A21),
	IMX_PINCTRL_PIN(MX25_PAD_A22),
	IMX_PINCTRL_PIN(MX25_PAD_A23),
	IMX_PINCTRL_PIN(MX25_PAD_A24),
	IMX_PINCTRL_PIN(MX25_PAD_A25),
	IMX_PINCTRL_PIN(MX25_PAD_EB0),
	IMX_PINCTRL_PIN(MX25_PAD_EB1),
	IMX_PINCTRL_PIN(MX25_PAD_OE),
	IMX_PINCTRL_PIN(MX25_PAD_CS0),
	IMX_PINCTRL_PIN(MX25_PAD_CS1),
	IMX_PINCTRL_PIN(MX25_PAD_CS4),
	IMX_PINCTRL_PIN(MX25_PAD_CS5),
	IMX_PINCTRL_PIN(MX25_PAD_NF_CE0),
	IMX_PINCTRL_PIN(MX25_PAD_ECB),
	IMX_PINCTRL_PIN(MX25_PAD_LBA),
	IMX_PINCTRL_PIN(MX25_PAD_BCLK),
	IMX_PINCTRL_PIN(MX25_PAD_RW),
	IMX_PINCTRL_PIN(MX25_PAD_NFWE_B),
	IMX_PINCTRL_PIN(MX25_PAD_NFRE_B),
	IMX_PINCTRL_PIN(MX25_PAD_NFALE),
	IMX_PINCTRL_PIN(MX25_PAD_NFCLE),
	IMX_PINCTRL_PIN(MX25_PAD_NFWP_B),
	IMX_PINCTRL_PIN(MX25_PAD_NFRB),
	IMX_PINCTRL_PIN(MX25_PAD_D15),
	IMX_PINCTRL_PIN(MX25_PAD_D14),
	IMX_PINCTRL_PIN(MX25_PAD_D13),
	IMX_PINCTRL_PIN(MX25_PAD_D12),
	IMX_PINCTRL_PIN(MX25_PAD_D11),
	IMX_PINCTRL_PIN(MX25_PAD_D10),
	IMX_PINCTRL_PIN(MX25_PAD_D9),
	IMX_PINCTRL_PIN(MX25_PAD_D8),
	IMX_PINCTRL_PIN(MX25_PAD_D7),
	IMX_PINCTRL_PIN(MX25_PAD_D6),
	IMX_PINCTRL_PIN(MX25_PAD_D5),
	IMX_PINCTRL_PIN(MX25_PAD_D4),
	IMX_PINCTRL_PIN(MX25_PAD_D3),
	IMX_PINCTRL_PIN(MX25_PAD_D2),
	IMX_PINCTRL_PIN(MX25_PAD_D1),
	IMX_PINCTRL_PIN(MX25_PAD_D0),
	IMX_PINCTRL_PIN(MX25_PAD_LD0),
	IMX_PINCTRL_PIN(MX25_PAD_LD1),
	IMX_PINCTRL_PIN(MX25_PAD_LD2),
	IMX_PINCTRL_PIN(MX25_PAD_LD3),
	IMX_PINCTRL_PIN(MX25_PAD_LD4),
	IMX_PINCTRL_PIN(MX25_PAD_LD5),
	IMX_PINCTRL_PIN(MX25_PAD_LD6),
	IMX_PINCTRL_PIN(MX25_PAD_LD7),
	IMX_PINCTRL_PIN(MX25_PAD_LD8),
	IMX_PINCTRL_PIN(MX25_PAD_LD9),
	IMX_PINCTRL_PIN(MX25_PAD_LD10),
	IMX_PINCTRL_PIN(MX25_PAD_LD11),
	IMX_PINCTRL_PIN(MX25_PAD_LD12),
	IMX_PINCTRL_PIN(MX25_PAD_LD13),
	IMX_PINCTRL_PIN(MX25_PAD_LD14),
	IMX_PINCTRL_PIN(MX25_PAD_LD15),
	IMX_PINCTRL_PIN(MX25_PAD_HSYNC),
	IMX_PINCTRL_PIN(MX25_PAD_VSYNC),
	IMX_PINCTRL_PIN(MX25_PAD_LSCLK),
	IMX_PINCTRL_PIN(MX25_PAD_OE_ACD),
	IMX_PINCTRL_PIN(MX25_PAD_CONTRAST),
	IMX_PINCTRL_PIN(MX25_PAD_PWM),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D2),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D3),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D4),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D5),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D6),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D7),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D8),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_D9),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_MCLK),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_VSYNC),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_HSYNC),
	IMX_PINCTRL_PIN(MX25_PAD_CSI_PIXCLK),
	IMX_PINCTRL_PIN(MX25_PAD_I2C1_CLK),
	IMX_PINCTRL_PIN(MX25_PAD_I2C1_DAT),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_MOSI),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_MISO),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_SS0),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_SS1),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_SCLK),
	IMX_PINCTRL_PIN(MX25_PAD_CSPI1_RDY),
	IMX_PINCTRL_PIN(MX25_PAD_UART1_RXD),
	IMX_PINCTRL_PIN(MX25_PAD_UART1_TXD),
	IMX_PINCTRL_PIN(MX25_PAD_UART1_RTS),
	IMX_PINCTRL_PIN(MX25_PAD_UART1_CTS),
	IMX_PINCTRL_PIN(MX25_PAD_UART2_RXD),
	IMX_PINCTRL_PIN(MX25_PAD_UART2_TXD),
	IMX_PINCTRL_PIN(MX25_PAD_UART2_RTS),
	IMX_PINCTRL_PIN(MX25_PAD_UART2_CTS),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_CMD),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_CLK),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_DATA0),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_DATA1),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_DATA2),
	IMX_PINCTRL_PIN(MX25_PAD_SD1_DATA3),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_ROW0),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_ROW1),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_ROW2),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_ROW3),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_COL0),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_COL1),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_COL2),
	IMX_PINCTRL_PIN(MX25_PAD_KPP_COL3),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_MDC),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_MDIO),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_TDATA0),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_TDATA1),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_TX_EN),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_RDATA0),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_RDATA1),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_RX_DV),
	IMX_PINCTRL_PIN(MX25_PAD_FEC_TX_CLK),
	IMX_PINCTRL_PIN(MX25_PAD_RTCK),
	IMX_PINCTRL_PIN(MX25_PAD_DE_B),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_A),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_B),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_C),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_D),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_E),
	IMX_PINCTRL_PIN(MX25_PAD_GPIO_F),
	IMX_PINCTRL_PIN(MX25_PAD_EXT_ARMCLK),
	IMX_PINCTRL_PIN(MX25_PAD_UPLL_BYPCLK),
	IMX_PINCTRL_PIN(MX25_PAD_VSTBY_REQ),
	IMX_PINCTRL_PIN(MX25_PAD_VSTBY_ACK),
	IMX_PINCTRL_PIN(MX25_PAD_POWER_FAIL),
	IMX_PINCTRL_PIN(MX25_PAD_CLKO),
	IMX_PINCTRL_PIN(MX25_PAD_BOOT_MODE0),
	IMX_PINCTRL_PIN(MX25_PAD_BOOT_MODE1),
};

static struct imx_pinctrl_soc_info imx25_pinctrl_info = {
	.pins = imx25_pinctrl_pads,
	.npins = ARRAY_SIZE(imx25_pinctrl_pads),
};

static const struct of_device_id imx25_pinctrl_of_match[] = {
	{ .compatible = "fsl,imx25-iomuxc", },
	{ /* sentinel */ }
};

static int imx25_pinctrl_probe(struct platform_device *pdev)
{
	return imx_pinctrl_probe(pdev, &imx25_pinctrl_info);
}

static struct platform_driver imx25_pinctrl_driver = {
	.driver = {
		.name = "imx25-pinctrl",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(imx25_pinctrl_of_match),
	},
	.probe = imx25_pinctrl_probe,
	.remove = imx_pinctrl_remove,
};

static int __init imx25_pinctrl_init(void)
{
	return platform_driver_register(&imx25_pinctrl_driver);
}
arch_initcall(imx25_pinctrl_init);

static void __exit imx25_pinctrl_exit(void)
{
	platform_driver_unregister(&imx25_pinctrl_driver);
}
module_exit(imx25_pinctrl_exit);
MODULE_AUTHOR("Denis Carikli <denis@eukrea.com>");
MODULE_DESCRIPTION("Freescale IMX25 pinctrl driver");
MODULE_LICENSE("GPL v2");
