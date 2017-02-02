/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 */

#ifndef __MAINBOARD_GPIO_H__
#define __MAINBOARD_GPIO_H__

#include <soc/gpe.h>
#include <soc/gpio.h>

/* EC in RW */
#define GPIO_EC_IN_RW		GPP_C6

/* BIOS Flash Write Protect */
#define GPIO_PCH_WP		GPP_C23

/* Memory configuration board straps */
#define GPIO_MEM_CONFIG_0	GPP_C12
#define GPIO_MEM_CONFIG_1	GPP_C13
#define GPIO_MEM_CONFIG_2	GPP_C14
#define GPIO_MEM_CONFIG_3	GPP_C15

/* EC wake is LAN_WAKE# which is a special DeepSX wake pin */
#define GPE_EC_WAKE		GPE0_LAN_WAK

/* eSPI virtual wire reporting */
#define EC_SCI_GPI		GPE0_ESPI

#ifndef __ACPI__
/* Pad configuration in ramstage */
/* Leave eSPI pins untouched from default settings */
static const struct pad_config gpio_table[] = {
/* RCIN# */		PAD_CFG_NC(GPP_A0), /* TP41 */
/* ESPI_IO0 */
/* ESPI_IO1 */
/* ESPI_IO2 */
/* ESPI_IO3 */
/* ESPI_CS# */
/* SERIRQ */		PAD_CFG_NC(GPP_A6), /* TP44 */
/* PIRQA# */		PAD_CFG_NC(GPP_A7),
/* CLKRUN# */		PAD_CFG_NC(GPP_A8), /* TP45 */
/* ESPI_CLK */
/* CLKOUT_LPC1 */	PAD_CFG_NC(GPP_A10),
/* PME# */		PAD_CFG_NC(GPP_A11), /* TP67 */
/* BM_BUSY# */		PAD_CFG_NC(GPP_A12),
/* SUSWARN# */		PAD_CFG_NC(GPP_A13),
/* ESPI_RESET# */
/* SUSACK# */		PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1),
/* SD_1P8_SEL */	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
/* SD_PWR_EN# */	PAD_CFG_NF(GPP_A17, NONE, DEEP, NF1),
/* ISH_GP0 */		PAD_CFG_NC(GPP_A18),
/* ISH_GP1 */		PAD_CFG_NC(GPP_A19),
/* ISH_GP2 */		PAD_CFG_GPI_APIC(GPP_A20, NONE,
					PLTRST), /* ACCEL_GYRO_INT_L */
/* ISH_GP3 */		PAD_CFG_NC(GPP_A21),
/* ISH_GP4 */		PAD_CFG_NC(GPP_A22),
/* ISH_GP5 */		PAD_CFG_NC(GPP_A23),

/* CORE_VID0 */		PAD_CFG_NC(GPP_B0), /* TP42 */
/* CORE_VID1 */		PAD_CFG_NC(GPP_B1), /* TP43 */
/* VRALERT# */		PAD_CFG_NC(GPP_B2),
/* CPU_GP2 */		PAD_CFG_NC(GPP_B3),
/* CPU_GP3 */		PAD_CFG_NC(GPP_B4),
/* SRCCLKREQ0# */	PAD_CFG_NC(GPP_B5),
/* SRCCLKREQ1# */	PAD_CFG_NF(GPP_B6, NONE, DEEP, NF1), /* WLAN CLKREQ */
/* SRCCLKREQ2# */	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF1), /* WWAN CLKREQ */
/* SRCCLKREQ3# */	PAD_CFG_NC(GPP_B8),
/* SRCCLKREQ4# */	PAD_CFG_NF(GPP_B9, NONE, DEEP, NF1), /* NVME CLKREQ */
/* SRCCLKREQ5# */	PAD_CFG_NC(GPP_B10),
/* EXT_PWR_GATE# */	PAD_CFG_NC(GPP_B11),
/* SLP_S0# */		PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
/* PLTRST# */		PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
/* SPKR */		PAD_CFG_NC(GPP_B14),
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1), /* TPM */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1), /* TPM */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1), /* TPM */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1), /* TPM */
/* GSPI1_CS# */		PAD_CFG_NF(GPP_B19, NONE, DEEP, NF1), /* FP */
/* GSPI1_CLK */		PAD_CFG_NF(GPP_B20, NONE, DEEP, NF1), /* FP */
/* GSPI1_MISO */	PAD_CFG_NF(GPP_B21, NONE, DEEP, NF1), /* FP */
/* GSPI1_MOSI */	PAD_CFG_NF(GPP_B22, NONE, DEEP, NF1), /* FP */
/* SM1ALERT# */		PAD_CFG_NC(GPP_B23),

/* SMBCLK */		PAD_CFG_NC(GPP_C0),
/* SMBDATA */		PAD_CFG_NC(GPP_C1),
/* SMBALERT# */		PAD_CFG_NC(GPP_C2),
/* SML0CLK */		PAD_CFG_NC(GPP_C3),
/* SML0DATA */		PAD_CFG_NC(GPP_C4),
/* SML0ALERT# */	PAD_CFG_NC(GPP_C5),
/* SM1CLK */		PAD_CFG_GPI(GPP_C6, 20K_PU, DEEP), /* EC_IN_RW */
/* SM1DATA */		PAD_CFG_NC(GPP_C7),
/* UART0_RXD */		PAD_CFG_NC(GPP_C8),
/* UART0_TXD */		PAD_CFG_NC(GPP_C9),
/* UART0_RTS# */	PAD_CFG_NC(GPP_C10),
/* UART0_CTS# */	PAD_CFG_NC(GPP_C11),
/* UART1_RXD */		PAD_CFG_GPI(GPP_C12, NONE, DEEP), /* MEM_CONFIG[0] */
/* UART1_TXD */		PAD_CFG_GPI(GPP_C13, NONE, DEEP), /* MEM_CONFIG[1] */
/* UART1_RTS# */	PAD_CFG_GPI(GPP_C14, NONE, DEEP), /* MEM_CONFIG[2] */
/* UART1_CTS# */	PAD_CFG_GPI(GPP_C15, NONE, DEEP), /* MEM_CONFIG[3] */
/* I2C0_SDA */		PAD_CFG_NF(GPP_C16, NONE, DEEP, NF1), /* TOUCHSCREEN */
/* I2C0_SCL */		PAD_CFG_NF(GPP_C17, NONE, DEEP, NF1), /* TOUCHSCREEN */
/* I2C1_SDA */		PAD_CFG_NF(GPP_C18, NONE, DEEP, NF1), /* NFC */
/* I2C1_SCL */		PAD_CFG_NF(GPP_C19, NONE, DEEP, NF1), /* NFC */
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
/* UART2_RTS# */	PAD_CFG_GPO(GPP_C22, 1,
				DEEP), /* EN_PP3300_DX_TOUCHSCREEN */
/* UART2_CTS# */	PAD_CFG_GPI(GPP_C23, 20K_PU, DEEP), /* PCH_WP */

/* SPI1_CS# */		PAD_CFG_NC(GPP_D0),
/* SPI1_CLK */		PAD_CFG_GPI_APIC(GPP_D1, NONE, PLTRST), /* PEN_IRQ_L */
/* SPI1_MISO */		PAD_CFG_GPI(GPP_D2, NONE, DEEP), /* PEN_PDCT_L */
/* SPI1_MOSI */		PAD_CFG_GPO(GPP_D3, 0, DEEP), /* PEN_RESET */
/* FASHTRIG */		PAD_CFG_NC(GPP_D4),
/* ISH_I2C0_SDA */	PAD_CFG_NF_1V8(GPP_D5, NONE, DEEP,
				NF1), /* ISH_SENSOR */
/* ISH_I2C0_SCL */	PAD_CFG_NF_1V8(GPP_D6, NONE, DEEP,
				NF1), /* ISH_SENSOR */
/* ISH_I2C1_SDA */	PAD_CFG_NC(GPP_D7),
/* ISH_I2C1_SCL */	PAD_CFG_NC(GPP_D8),
/* ISH_SPI_CS# */	PAD_CFG_GPI_APIC(GPP_D9, NONE,
					PLTRST), /* HP_IRQ_GPIO */
/* ISH_SPI_CLK */	PAD_CFG_GPO(GPP_D10, 1, DEEP), /* SPKR_RST_L */
/* ISH_SPI_MISO */	PAD_CFG_GPI_APIC(GPP_D11, NONE,
					PLTRST), /* SPKR_INT_L */
/* ISH_SPI_MOSI */	PAD_CFG_NC(GPP_D12),
/* ISH_UART0_RXD */	PAD_CFG_GPI_APIC(GPP_D13, NONE, PLTRST), /* FP_INT */
/* ISH_UART0_TXD */	PAD_CFG_GPO(GPP_D14, 0, DEEP), /* FP_RST_ODL */
/* ISH_UART0_RTS# */	PAD_CFG_GPI_APIC(GPP_D15, NONE, PLTRST), /* MIC_IRQ_L */
/* ISH_UART0_CTS# */	PAD_CFG_NC(GPP_D16),
/* DMIC_CLK1 */		PAD_CFG_NF(GPP_D17, NONE, DEEP, NF1), /* DMIC_CLK1 */
/* DMIC_DATA1 */	PAD_CFG_NF(GPP_D18, NONE, DEEP, NF1), /* DMIC_DATA1 */
/* DMIC_CLK0 */		PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1), /* DMIC_CLK0 */
/* DMIC_DATA0 */	PAD_CFG_NF(GPP_D20, NONE, DEEP, NF1), /* DMIC_DATA0 */
/* SPI1_IO2 */		PAD_CFG_NC(GPP_D21),
/* SPI1_IO3 */		PAD_CFG_GPO(GPP_D22, 1, DEEP), /* I2S2 BUFFER */
/* I2S_MCLK */		PAD_CFG_NF(GPP_D23, NONE, DEEP, NF1), /* MCLK */

/* SATAXPCI0 */		PAD_CFG_GPI_APIC_INVERT(GPP_E0, NONE,
							PLTRST), /* TPM_INT_L */
/* SATAXPCIE1 */	PAD_CFG_NC(GPP_E1),
/* SATAXPCIE2 */	PAD_CFG_NC(GPP_E2),
/* CPU_GP0 */		PAD_CFG_NC(GPP_E3),
/* SATA_DEVSLP0 */	PAD_CFG_GPO(GPP_E4, 0, DEEP), /* NFC_RESET_ODL */
/* SATA_DEVSLP1 */	PAD_CFG_GPI_APIC(GPP_E5, NONE, PLTRST), /* NFC_INT_L */
/* SATA_DEVSLP2 */	PAD_CFG_GPO(GPP_E6, 0, DEEP), /* NFC_FW_DL */
/* CPU_GP1 */		PAD_CFG_GPI_APIC(GPP_E7, NONE,
					PLTRST), /* TOUCHSCREEN_INT_L */
/* SATALED# */		PAD_CFG_NC(GPP_E8),
/* USB2_OCO# */		PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1), /* USB_C0_OC_ODL */
/* USB2_OC1# */		PAD_CFG_NF(GPP_E10, NONE, DEEP,
					NF1), /* USB_C1_OC_ODL */
/* USB2_OC2# */		PAD_CFG_GPO(GPP_E11, 0, DEEP), /* TOUCHSCREEN_RESET_L */
/* USB2_OC3# */		PAD_CFG_NF(GPP_E12, NONE, DEEP, NF1), /* USB2_OC3_L */
/* DDPB_HPD0 */		PAD_CFG_NF(GPP_E13, NONE, DEEP,
					NF1), /* USB_C0_DP_HPD */
/* DDPC_HPD1 */		PAD_CFG_NF(GPP_E14, NONE, DEEP,
					NF1), /* USB_C1_DP_HPD */
/* DDPD_HPD2 */		PAD_CFG_NC(GPP_E15), /* TP48 */
/* DDPE_HPD3 */		PAD_CFG_NC(GPP_E16), /* TP244 */
/* EDP_HPD */		PAD_CFG_NF(GPP_E17, NONE, DEEP, NF1),
/* DDPB_CTRLCLK */	PAD_CFG_NC(GPP_E18),
/* DDPB_CTRLDATA */	PAD_CFG_NC(GPP_E19),
/* DDPC_CTRLCLK */	PAD_CFG_NC(GPP_E20),
/* DDPC_CTRLDATA */	PAD_CFG_NC(GPP_E21),
/* DDPD_CTRLCLK */	PAD_CFG_NC(GPP_E22),
/* DDPD_CTRLDATA */	PAD_CFG_NC(GPP_E23),

/* The next 4 pads are for bit banging the amplifiers, default to I2S */
/* I2S2_SCLK */		PAD_CFG_GPI(GPP_F0, NONE, DEEP),
/* I2S2_SFRM */		PAD_CFG_GPI(GPP_F1, NONE, DEEP),
/* I2S2_TXD */		PAD_CFG_GPI(GPP_F2, NONE, DEEP),
/* I2S2_RXD */		PAD_CFG_GPI(GPP_F3, NONE, DEEP),
/* I2C2_SDA */		PAD_CFG_NF_1V8(GPP_F4, NONE, DEEP, NF1), /* CAM_PMIC */
/* I2C2_SCL */		PAD_CFG_NF_1V8(GPP_F5, NONE, DEEP, NF1), /* CAM_PMIC */
/* I2C3_SDA */		PAD_CFG_NF_1V8(GPP_F6, NONE, DEEP, NF1), /* PEN */
/* I2C3_SCL */		PAD_CFG_NF_1V8(GPP_F7, NONE, DEEP, NF1), /* PEN */
/* I2C4_SDA */		PAD_CFG_NF_1V8(GPP_F8, NONE, DEEP, NF1), /* UFCAM */
/* I2C4_SCL */		PAD_CFG_NF_1V8(GPP_F9, NONE, DEEP, NF1), /* UFCAM*/
/* I2C5_SDA */		PAD_CFG_NF_1V8(GPP_F10, NONE, DEEP, NF1), /* AUDIO */
/* I2C5_SCL */		PAD_CFG_NF_1V8(GPP_F11, NONE, DEEP, NF1), /* AUDIO */
/* EMMC_CMD */		PAD_CFG_NF(GPP_F12, NONE, DEEP, NF1),
/* EMMC_DATA0 */	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF1),
/* EMMC_DATA1 */	PAD_CFG_NF(GPP_F14, NONE, DEEP, NF1),
/* EMMC_DATA2 */	PAD_CFG_NF(GPP_F15, NONE, DEEP, NF1),
/* EMMC_DATA3 */	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF1),
/* EMMC_DATA4 */	PAD_CFG_NF(GPP_F17, NONE, DEEP, NF1),
/* EMMC_DATA5 */	PAD_CFG_NF(GPP_F18, NONE, DEEP, NF1),
/* EMMC_DATA6 */	PAD_CFG_NF(GPP_F19, NONE, DEEP, NF1),
/* EMMC_DATA7 */	PAD_CFG_NF(GPP_F20, NONE, DEEP, NF1),
/* EMMC_RCLK */		PAD_CFG_NF(GPP_F21, NONE, DEEP, NF1),
/* EMMC_CLK */		PAD_CFG_NF(GPP_F22, NONE, DEEP, NF1),
/* RSVD */		PAD_CFG_NC(GPP_F23),

/* SD_CMD */		PAD_CFG_NF(GPP_G0, NONE, DEEP, NF1),
/* SD_DATA0 */		PAD_CFG_NF(GPP_G1, NONE, DEEP, NF1),
/* SD_DATA1 */		PAD_CFG_NF(GPP_G2, NONE, DEEP, NF1),
/* SD_DATA2 */		PAD_CFG_NF(GPP_G3, NONE, DEEP, NF1),
/* SD_DATA3 */		PAD_CFG_NF(GPP_G4, NONE, DEEP, NF1),
/* SD_CD# */		PAD_CFG_NF(GPP_G5, NONE, DEEP, NF1),
/* SD_CLK */		PAD_CFG_NF(GPP_G6, NONE, DEEP, NF1),
/* SD_WP */		PAD_CFG_NF(GPP_G7, 20K_PD, DEEP, NF1),

/* BATLOW# */		PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
/* ACPRESENT */		PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
/* LAN_WAKE# */		PAD_CFG_NF(GPD2, NONE, DEEP, NF1), /* EC_PCH_WAKE_L */
/* PWRBTN# */		PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
/* SLP_S3# */		PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
/* SLP_S4# */		PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
/* SLP_A# */		PAD_CFG_NC(GPD6), /* TP26 */
/* RSVD */		PAD_CFG_NC(GPD7),
/* SUSCLK */		PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
/* SLP_WLAN# */		PAD_CFG_NC(GPD9), /* TP25 */
/* SLP_S5# */		PAD_CFG_NC(GPD10), /* TP15 */
/* LANPHYC */		PAD_CFG_NC(GPD11),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
/* GSPI0_CS# */		PAD_CFG_NF(GPP_B15, NONE, DEEP, NF1), /* TPM */
/* GSPI0_CLK */		PAD_CFG_NF(GPP_B16, NONE, DEEP, NF1), /* TPM */
/* GSPI0_MISO */	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF1), /* TPM */
/* GSPI0_MOSI */	PAD_CFG_NF(GPP_B18, NONE, DEEP, NF1), /* TPM */
/* UART2_CTS# */	PAD_CFG_GPI(GPP_C23, 20K_PU, DEEP), /* PCH_WP */
/* SATAXPCI0 */		PAD_CFG_GPI_APIC_INVERT(GPP_E0, NONE,
							PLTRST), /* TPM_INT_L */
/* Ensure UART pins are in native mode for H1. */
/* UART2_RXD */		PAD_CFG_NF(GPP_C20, NONE, DEEP, NF1), /* SERVO */
/* UART2_TXD */		PAD_CFG_NF(GPP_C21, NONE, DEEP, NF1), /* SERVO */
};

#endif

#endif
