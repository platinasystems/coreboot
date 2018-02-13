/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2008 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#ifndef _SOC_CHIP_H_
#define _SOC_CHIP_H_

#include <arch/acpi_device.h>
#include <device/i2c.h>
#include <intelblocks/gspi.h>
#include <stdint.h>
#include <soc/gpio_defs.h>
#include <soc/gpe.h>
#include <soc/irq.h>
#include <soc/intel/common/lpss_i2c.h>
#include <soc/pci_devs.h>
#include <soc/pmc.h>
#include <soc/serialio.h>
#include <soc/usb.h>
#include <soc/vr_config.h>

#define SKYLAKE_I2C_DEV_MAX 6

enum skylake_i2c_voltage {
	I2C_VOLTAGE_3V3,
	I2C_VOLTAGE_1V8
};

struct skylake_i2c_config {
	/* Bus speed in Hz, default is I2C_SPEED_FAST (400 KHz) */
	enum i2c_speed speed;
	/* Bus should be enabled prior to ramstage with temporary base */
	int early_init;
	/* Custom bus speed configuration { scl_lcnt, scl_hcnt, sda_hold } */
	struct lpss_i2c_speed_config speed_config[LPSS_I2C_SPEED_CONFIG_COUNT];
};

struct soc_intel_skylake_config {
	/*
	 * Interrupt Routing configuration
	 * If bit7 is 1, the interrupt is disabled.
	 */
	uint8_t pirqa_routing;
	uint8_t pirqb_routing;
	uint8_t pirqc_routing;
	uint8_t pirqd_routing;
	uint8_t pirqe_routing;
	uint8_t pirqf_routing;
	uint8_t pirqg_routing;
	uint8_t pirqh_routing;

	/* GPE configuration */
	uint32_t gpe0_en_1; /* GPE0_EN_31_0 */
	uint32_t gpe0_en_2; /* GPE0_EN_63_32 */
	uint32_t gpe0_en_3; /* GPE0_EN_95_64 */
	uint32_t gpe0_en_4; /* GPE0_EN_127_96 / GPE_STD */
	/* Gpio group routed to each dword of the GPE0 block. Values are
	 * of the form GPP_[A:G] or GPD. */
	uint8_t gpe0_dw0; /* GPE0_31_0 STS/EN */
	uint8_t gpe0_dw1; /* GPE0_63_32 STS/EN */
	uint8_t gpe0_dw2; /* GPE0_95_64 STS/EN */

	/* Generic IO decode ranges */
	uint32_t gen1_dec;
	uint32_t gen2_dec;
	uint32_t gen3_dec;
	uint32_t gen4_dec;

	/* Enable S0iX support */
	int s0ix_enable;

	/* Enable DPTF support */
	int dptf_enable;

	/* Deep SX enables */
	int deep_s3_enable_ac;
	int deep_s3_enable_dc;
	int deep_s5_enable_ac;
	int deep_s5_enable_dc;

	/*
	 * Deep Sx Configuration
	 *  DSX_EN_WAKE_PIN       - Enable WAKE# pin
	 *  DSX_EN_LAN_WAKE_PIN   - Enable LAN_WAKE# pin
	 *  DSX_EN_AC_PRESENT_PIN - Enable AC_PRESENT pin
	 */
	uint32_t deep_sx_config;

	/* TCC activation offset */
	int tcc_offset;

	/*
	 * The following fields come from FspUpdVpd.h.
	 * These are configuration values that are passed to FSP during
	 * MemoryInit.
	 */
	u64 PlatformMemorySize;
	u8 SmramMask;
	u8 MrcFastBoot;
	u32 TsegSize;
	u16 MmioSize;

	/*
	 * DDR Frequency Limit
	 * 0(Auto), 1067, 1333, 1600, 1867, 2133, 2400
	 */
	u16 DdrFreqLimit;

	/* Probeless Trace function */
	u8 ProbelessTrace;

	/*
	 * System Agent dynamic frequency configuration
	 * When enabled memory will be trained at two different frequencies.
	 * 0 = Disabled
	 * 1 = FixedLow
	 * 2 = FixedHigh
	 * 3 = Enabled
	*/
	u8 SaGv;

	/* Enable/disable Rank Margin Tool */
	u8 Rmt;

	/* Lan */
	u8 EnableLan;

	/* SATA related */
	u8 EnableSata;
	u8 SataMode;
	u8 SataSalpSupport;
	u8 SataPortsEnable[8];
	u8 SataPortsDevSlp[8];

	/* Audio related */
	u8 EnableAzalia;
	u8 DspEnable;

	/*
	 * I/O Buffer Ownership:
	 * 0: HD-A Link
	 * 1 Shared, HD-A Link and I2S Port
	 * 3: I2S Ports
	 */
	u8 IoBufferOwnership;

	/* Trace Hub function */
	u8 EnableTraceHub;
	u32 TraceHubMemReg0Size;
	u32 TraceHubMemReg1Size;

	/* DCI Enable/Disable */
	u8 PchDciEn;

	/* Pcie Root Ports */
	u8 PcieRpEnable[CONFIG_MAX_ROOT_PORTS];
	u8 PcieRpClkReqSupport[CONFIG_MAX_ROOT_PORTS];
	u8 PcieRpClkReqNumber[CONFIG_MAX_ROOT_PORTS];

	/* USB related */
	struct usb2_port_config usb2_ports[16];
	struct usb3_port_config usb3_ports[10];
	u8 XdciEnable;
	u8 SsicPortEnable;

	/* SMBus */
	u8 SmbusEnable;

	/*
	 * SerialIO device mode selection:
	 *
	 * Device index:
	 * PchSerialIoIndexI2C0
	 * PchSerialIoIndexI2C1
	 * PchSerialIoIndexI2C2
	 * PchSerialIoIndexI2C3
	 * PchSerialIoIndexI2C4
	 * PchSerialIoIndexI2C5
	 * PchSerialIoIndexI2C6
	 * PchSerialIoIndexSpi0
	 * PchSerialIoIndexSpi1
	 * PchSerialIoIndexUart0
	 * PchSerialIoIndexUart1
	 * PchSerialIoIndexUart2
	 *
	 * Mode select:
	 * PchSerialIoDisabled
	 * PchSerialIoAcpi
	 * PchSerialIoPci
	 * PchSerialIoAcpiHidden
	 * PchSerialIoLegacyUart
	 */
	u8 SerialIoDevMode[PchSerialIoIndexMax];

	/* I2C */
	/* Bus voltage level, default is 3.3V */
	enum skylake_i2c_voltage i2c_voltage[SKYLAKE_I2C_DEV_MAX];
	struct lpss_i2c_bus_config i2c[SKYLAKE_I2C_DEV_MAX];

	/* GSPI */
	struct gspi_cfg gspi[CONFIG_SOC_INTEL_COMMON_BLOCK_GSPI_MAX];

	/* Camera */
	u8 Cio2Enable;
	u8 SaImguEnable;

	/* eMMC and SD */
	u8 ScsEmmcEnabled;
	u8 ScsEmmcHs400Enabled;
	u8 ScsSdCardEnabled;

	/* Integrated Sensor */
	u8 IshEnable;

	u8 PttSwitch;
	u8 HeciTimeouts;
	u8 HsioMessaging;
	u8 Heci3Enabled;

	/* Gfx related */
	u8 IgdDvmt50PreAlloc;
	u8 PrimaryDisplay;
	u8 InternalGfx;
	u8 ApertureSize;
	u8 SkipExtGfxScan;
	u8 ScanExtGfxForLegacyOpRom;

	/*
	 * The following fields come from fsp_vpd.h
	 * These are configuration values that are passed to FSP during
	 * SiliconInit.
	 */
	u32 LogoPtr;
	u32 LogoSize;
	u32 GraphicsConfigPtr;
	u8 Device4Enable;
	u8 RtcLock;
	/* GPIO IRQ Route  The valid values is 14 or 15*/
	u8 GpioIrqSelect;
	/* SCI IRQ Select  The valid values is 9, 10, 11 and 20 21, 22, 23*/
	u8 SciIrqSelect;
	/* TCO IRQ Select  The valid values is 9, 10, 11, 20 21, 22, 23*/
	u8 TcoIrqSelect;
	u8 TcoIrqEnable;
	/* Enable SMI_LOCK bit to prevent writes to the Global SMI Enable bit.*/
	u8 LockDownConfigGlobalSmi;
	/*
	 * Enable BIOS Interface Lock Down bit to prevent writes to the Backup
	 * Control Register. Top Swap bit and the General Control and Status
	 * Registers Boot BIOS Straps.
	 */
	u8 LockDownConfigBiosInterface;
	/*
	 * Enable RTC lower and upper 128 byte Lock bits to lock Bytes 38h-3Fh
	 * in the upper and and lower 128-byte bank of RTC RAM.
	 */
	u8 LockDownConfigRtcLock;
	/*
	 * When enabled, the BIOS Region can only be modified from SMM after
	 * EndOfDxe protocol is installed
	 */
	u8 LockDownConfigBiosLock;
	/*
	 * Enable InSMM.STS (EISS) in SPI If this bit is set, then WPD must be a
	 * '1' and InSMM.STS must be '1' also in order to write to BIOS regions
	 * of SPI Flash. If this bit is clear, then the InSMM.STS is a don't
	 * care. The BIOS must set the EISS bit while BIOS Guard support is
	 * enabled.
	 */
	u8 LockDownConfigSpiEiss;
	/* Subsystem Vendor ID of the PCH devices*/
	u16 PchConfigSubSystemVendorId;
	/* Subsystem ID of the PCH devices*/
	u16 PchConfigSubSystemId;

	/*
	 * Determine if WLAN wake from Sx, corresponds to the
	 * HOST_WLAN_PP_EN bit in the PWRM_CFG3 register.
	 */
	u8 PchPmWoWlanEnable;

	/*
	 * Determine if WLAN wake from DeepSx, corresponds to
	 * the DSX_WLAN_PP_EN bit in the PWRM_CFG3 register.
	 */
	u8 PchPmWoWlanDeepSxEnable;

	/*
	 * Corresponds to the "WOL Enable Override" bit in the General PM
	 * Configuration B (GEN_PMCON_B) register
	 */
	u8 WakeConfigWolEnableOverride;
	/* Determine if enable PCIe to wake from deep Sx*/
	u8 WakeConfigPcieWakeFromDeepSx;
	/* Deep Sx Policy. Values 0: PchDeepSxPolDisable,
	 * 1: PchDpS5BatteryEn, 2: PchDpS5AlwaysEn, 3: PchDpS4S5BatteryEn,
	 * 4: PchDpS4S5AlwaysEn, 5: PchDpS3S4S5BatteryEn, 6: PchDpS3S4S5AlwaysEn
	 */
	u8 PmConfigDeepSxPol;
	/*
	 * SLP_S3 Minimum Assertion Width Policy. Values 0: PchSlpS360us,
	 * 1: PchSlpS31ms, 2: PchSlpS350ms, 3: PchSlpS32s.
	 */
	u8 PmConfigSlpS3MinAssert;
	/*
	 * SLP_S4 Minimum Assertion Width Policy. Values 0: PchSlpS4PchTime,
	 * 1: PchSlpS41s, 2: PchSlpS42s, 3: PchSlpS43s, 4: PchSlpS44s.
	 */
	u8 PmConfigSlpS4MinAssert;
	/*
	 * SLP_SUS Minimum Assertion Width Policy. Values 0: PchSlpSus0ms,
	 * 1: PchSlpSus500ms, 2: PchSlpSus1s, 3: PchSlpSus4s.
	 */
	u8 PmConfigSlpSusMinAssert;
	/*
	 * SLP_A Minimum Assertion Width Policy. Values 0: PchSlpA0ms,
	 * 1: PchSlpA4s, 2: PchSlpA98ms, 3: PchSlpA2s.
	 */
	u8 PmConfigSlpAMinAssert;
	/*
	 * This member describes whether or not the PCI ClockRun feature of PCH
	 * should be enabled. Values 0: Disabled, 1: Enabled
	 */
	u8 PmConfigPciClockRun;
	/*
	 * SLP_X Stretching After SUS Well Power Up. Values 0: Disabled,
	 * 1: Enabled
	 */
	u8 PmConfigSlpStrchSusUp;
	/*
	 * PCH power button override period.
	 * Values: 0x0 - 4s, 0x1 - 6s, 0x2 - 8s, 0x3 - 10s, 0x4 - 12s, 0x5 - 14s
	 */
	u8 PmConfigPwrBtnOverridePeriod;

	/*
	 * PCH Pm Slp S0 Voltage Margining Enable
	 * Indicates platform supports VCCPrim_Core Voltage Margining
	 * in SLP_S0# asserted state.
	 */
	u8 PchPmSlpS0VmEnable;

	/*
	 * Reset Power Cycle Duration could be customized in the unit of second.
	 * PCH HW default is 4 seconds, and range is 1~4 seconds.
	 * Values: 0x0 - 0s, 0x1 - 1s, 0x2 - 2s, 0x3 - 3s, 0x4 - 4s
	 */
	u8 PmConfigPwrCycDur;
	/* Determines if enable Serial IRQ. Values 0: Disabled, 1: Enabled.*/
	u8 SerialIrqConfigSirqEnable;
	/* Serial IRQ Mode Select. Values: 0: PchQuietMode,
	 * 1: PchContinuousMode.
	 */
	u8 SerialIrqConfigSirqMode;
	/*
	 * Start Frame Pulse Width.
	 * Values: 0: PchSfpw4Clk, 1: PchSfpw6Clk, 2; PchSfpw8Clk.
	 */
	u8 SerialIrqConfigStartFramePulse;
	u8 FspSkipMpInit;
	/*
	 * VrConfig Settings for 5 domains
	 * 0 = System Agent, 1 = IA Core, 2 = Ring,
	 * 3 = GT unsliced,  4 = GT sliced
	 */
	struct vr_config domain_vr_config[NUM_VR_DOMAINS];
	/*
	 * HeciEnabled decides the state of Heci1 at end of boot
	 * Setting to 0 (default) disables Heci1 and hides the device from OS
	 */
	u8 HeciEnabled;
	/* PL2 Override value in Watts */
	u32 tdp_pl2_override;
	u8 PmTimerDisabled;
	/* Intel Speed Shift Technology */
	u8 speed_shift_enable;
	/*
	 * Enable VR specific mailbox command
	 * 000b - Don't Send any VR command
	 * 001b - VR command specifically for the MPS IMPV8 VR will be sent
	 * 010b - VR specific command sent for PS4 exit issue
	 * 011b - VR specific command sent for both MPS IMPV8 & PS4 exit issue
	*/
	u8 SendVrMbxCmd;

	/* Enable/Disable VMX feature */
	u8 VmxEnable;

	/*
	 * PRMRR size setting with three options
	 * 0x02000000 - 32MiB
	 * 0x04000000 - 64MiB
	 * 0x08000000 - 128MiB
	 */
	u32 PrmrrSize;

	/* Enable/Disable host reads to PMC XRAM registers */
	u8 PchPmPmcReadDisable;

	/* Statically clock gate 8254 PIT. */
	u8 clock_gate_8254;

	/*
	 * Use SD card detect GPIO with default config:
	 * - Edge triggered
	 * - No internal pull
	 * - Active both (high + low)
	 * - Can wake device from D3
	 * - 100ms debounce timeout
	 *
	 * GpioInt (Edge, ActiveBoth, SharedAndWake, PullNone, 10000,
	 *          "\\_SB.PCI0.GPIO", 0, ResourceConsumer)
	 *          { sdcard_cd_gpio_default }
	 */
	unsigned int sdcard_cd_gpio_default;

	/* Use custom SD card detect GPIO configuration */
	struct acpi_gpio sdcard_cd_gpio;

	/* Wake Enable Bitmap for USB2 ports */
	u16 usb2_wake_enable_bitmap;

	/* Wake Enable Bitmap for USB3 ports */
	u8 usb3_wake_enable_bitmap;

	/*
	 * Acoustic Noise Mitigation
	 * 0b - Disable
	 * 1b - Enable noise mitigation
	 */
	u8 AcousticNoiseMitigation;

	/*
	 * Disable Fast Package C-state ramping
	 * Need to set AcousticNoiseMitigation = '1' first
	 * 0b - Enabled
	 * 1b - Disabled
	 */
	u8 FastPkgCRampDisableIa;
	u8 FastPkgCRampDisableGt;
	u8 FastPkgCRampDisableSa;

	/*
	 * Adjust the VR slew rates
	 * Need to set AcousticNoiseMitigation = '1' first
	 * 000b - Fast/2
	 * 001b - Fast/4
	 * 010b - Fast/8
	 * 011b - Fast/16
	 */
	u8 SlowSlewRateForIa;
	u8 SlowSlewRateForGt;
	u8 SlowSlewRateForSa;

	/* Enable SGX feature */
	u8 sgx_enable;
};

typedef struct soc_intel_skylake_config config_t;

extern struct chip_operations soc_ops;

#endif
