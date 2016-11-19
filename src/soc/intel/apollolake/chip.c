/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 * (Written by Andrey Petrov <andrey.petrov@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/acpi.h>
#include <bootstate.h>
#include <cbmem.h>
#include <console/console.h>
#include <cpu/cpu.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <soc/iomap.h>
#include <soc/cpu.h>
#include <soc/intel/common/vbt.h>
#include <soc/itss.h>
#include <soc/nvs.h>
#include <soc/pci_devs.h>
#include <spi-generic.h>
#include <soc/pm.h>
#include <soc/p2sb.h>
#include <soc/northbridge.h>

#include "chip.h"

static void *vbt;
static struct region_device vbt_rdev;

static const char *soc_acpi_name(struct device *dev)
{
	if (dev->path.type == DEVICE_PATH_DOMAIN)
		return "PCI0";

	if (dev->path.type != DEVICE_PATH_PCI)
		return NULL;

	switch (dev->path.pci.devfn) {
	/* DSDT: acpi/northbridge.asl */
	case NB_DEVFN:
		return "MCHC";
	/* DSDT: acpi/lpc.asl */
	case LPC_DEVFN:
		return "LPCB";
	/* DSDT: acpi/xhci.asl */
	case XHCI_DEVFN:
		return "XHCI";
	/* DSDT: acpi/pch_hda.asl */
	case HDA_DEVFN:
		return "HDAS";
	/* DSDT: acpi/lpss.asl */
	case LPSS_DEVFN_UART0:
		return "URT1";
	case LPSS_DEVFN_UART1:
		return "URT2";
	case LPSS_DEVFN_UART2:
		return "URT3";
	case LPSS_DEVFN_UART3:
		return "URT4";
	case LPSS_DEVFN_SPI0:
		return "SPI1";
	case LPSS_DEVFN_SPI1:
		return "SPI2";
	case LPSS_DEVFN_SPI2:
		return "SPI3";
	case LPSS_DEVFN_PWM:
		return "PWM";
	case LPSS_DEVFN_I2C0:
		return "I2C0";
	case LPSS_DEVFN_I2C1:
		return "I2C1";
	case LPSS_DEVFN_I2C2:
		return "I2C2";
	case LPSS_DEVFN_I2C3:
		return "I2C3";
	case LPSS_DEVFN_I2C4:
		return "I2C4";
	case LPSS_DEVFN_I2C5:
		return "I2C5";
	case LPSS_DEVFN_I2C6:
		return "I2C6";
	case LPSS_DEVFN_I2C7:
		return "I2C7";
	/* Storage */
	case SDCARD_DEVFN:
		return "SDCD";
	case EMMC_DEVFN:
		return "EMMC";
	case SDIO_DEVFN:
		return "SDIO";
	/* PCIe */
	case PCIEB0_DEVFN:
		return "RP01";
	}

	return NULL;
}

static void pci_domain_set_resources(device_t dev)
{
       assign_resources(dev->link_list);
}

static struct device_operations pci_domain_ops = {
	.read_resources = pci_domain_read_resources,
	.set_resources = pci_domain_set_resources,
	.enable_resources = NULL,
	.init = NULL,
	.scan_bus = pci_domain_scan_bus,
	.ops_pci_bus = pci_bus_default_ops,
	.acpi_name = &soc_acpi_name,
};

static struct device_operations cpu_bus_ops = {
	.read_resources = DEVICE_NOOP,
	.set_resources = DEVICE_NOOP,
	.enable_resources = DEVICE_NOOP,
	.init = apollolake_init_cpus,
	.scan_bus = NULL,
	.acpi_fill_ssdt_generator = generate_cpu_entries,
};

static void enable_dev(device_t dev)
{
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN) {
		dev->ops = &pci_domain_ops;
	} else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER) {
		dev->ops = &cpu_bus_ops;
	}
}

/*
 * If the PCIe root port at function 0 is disabled,
 * the PCIe root ports might be coalesced after FSP silicon init.
 * The below function will swap the devfn of the first enabled device
 * in devicetree and function 0 resides a pci device
 * so that it won't confuse coreboot.
 */
static void pcie_update_device_tree(unsigned int devfn0, int num_funcs)
{
	device_t func0;
	unsigned int devfn;
	int i;
	unsigned int inc = PCI_DEVFN(0, 1);

	func0 = dev_find_slot(0, devfn0);
	if (func0 == NULL)
		return;

	/* No more functions if function 0 is disabled. */
	if (pci_read_config32(func0, PCI_VENDOR_ID) == 0xffffffff)
		return;

	devfn = devfn0 + inc;

	/*
	 * Increase funtion by 1.
	 * Then find first enabled device to replace func0
	 * as that port was move to func0.
	 */
	for (i = 1; i < num_funcs; i++, devfn += inc) {
		device_t dev = dev_find_slot(0, devfn);
		if (dev == NULL)
			continue;

		if (!dev->enabled)
			continue;
		/* Found the first enabled device in given dev number */
		func0->path.pci.devfn = dev->path.pci.devfn;
		dev->path.pci.devfn = devfn0;
		break;
	}
}

static void pcie_override_devicetree_after_silicon_init(void)
{
	pcie_update_device_tree(PCIEA0_DEVFN, 4);
	pcie_update_device_tree(PCIEB0_DEVFN, 2);
}

/* Configure package power limits */
static void set_power_limits(void)
{
	static struct soc_intel_apollolake_config *cfg;
	struct device *dev = NB_DEV_ROOT;
	msr_t rapl_msr_reg, limit;
	uint32_t power_unit;
	uint32_t tdp, min_power, max_power;
	uint32_t *rapl_mmio_reg;

	if (!dev || !dev->chip_info) {
		printk(BIOS_ERR, "BUG! Could not find SOC devicetree config\n");
		return;
	}

	cfg = dev->chip_info;

	/* Get units */
	rapl_msr_reg = rdmsr(MSR_PKG_POWER_SKU_UNIT);
	power_unit = 1 << (rapl_msr_reg.lo & 0xf);

	/* Get power defaults for this SKU */
	rapl_msr_reg = rdmsr(MSR_PKG_POWER_SKU);
	tdp = rapl_msr_reg.lo & PKG_POWER_LIMIT_MASK;
	min_power = (rapl_msr_reg.lo >> 16) & PKG_POWER_LIMIT_MASK;
	max_power = rapl_msr_reg.hi & PKG_POWER_LIMIT_MASK;

	if (min_power > 0 && tdp < min_power)
		tdp = min_power;

	if (max_power > 0 && tdp > max_power)
		tdp = max_power;

	/* Set PL1 override value */
	tdp = (cfg->tdp_pl1_override_mw == 0) ?
		tdp : (cfg->tdp_pl1_override_mw * power_unit) / 1000;

	/* Set long term power limit to TDP */
	limit.lo = tdp & PKG_POWER_LIMIT_MASK;
	/* PL2 is invalid for small core */
	limit.hi = 0x0;

	/* Set PL1 Pkg Power clamp bit */
	limit.lo |= PKG_POWER_LIMIT_CLAMP;

	limit.lo |= PKG_POWER_LIMIT_EN;
	limit.lo |= (MB_POWER_LIMIT1_TIME_DEFAULT &
		PKG_POWER_LIMIT_TIME_MASK) << PKG_POWER_LIMIT_TIME_SHIFT;

	/* Program package power limits in RAPL MSR */
	wrmsr(MSR_PKG_POWER_LIMIT, limit);
	printk(BIOS_INFO, "RAPL PL1 %d.%dW\n", tdp / power_unit,
				100 * (tdp % power_unit) / power_unit);

	/* Get the MMIO address */
	rapl_mmio_reg = (void *)(uintptr_t) (MCH_BASE_ADDR + MCHBAR_RAPL_PPL);
	/*
	 * Disable RAPL MMIO PL1 Power limits because RAPL uses MSR value.
	 * PL2 (limit.hi) is invalid for small cores
	 */
	write32(rapl_mmio_reg, limit.lo & ~(PKG_POWER_LIMIT_EN));
}

static void soc_init(void *data)
{
	struct global_nvs_t *gnvs;

	/* Save VBT info and mapping */
	vbt = vbt_get(&vbt_rdev);

	/* Snapshot the current GPIO IRQ polarities. FSP is setting a
	 * default policy that doesn't honor boards' requirements. */
	itss_snapshot_irq_polarities(GPIO_IRQ_START, GPIO_IRQ_END);

	fsp_silicon_init();

	/* Restore GPIO IRQ polarities back to previous settings. */
	itss_restore_irq_polarities(GPIO_IRQ_START, GPIO_IRQ_END);

	/* override 'enabled' setting in device tree if needed */
	pcie_override_devicetree_after_silicon_init();

	/*
	 * Keep the P2SB device visible so it and the other devices are
	 * visible in coreboot for driver support and PCI resource allocation.
	 * There is a UPD setting for this, but it's more consistent to use
	 * hide and unhide symmetrically.
	 */
	p2sb_unhide();

	/* Allocate ACPI NVS in CBMEM */
	gnvs = cbmem_add(CBMEM_ID_ACPI_GNVS, sizeof(*gnvs));

	/* Set RAPL MSR for Package power limits*/
	set_power_limits();
}

static void soc_final(void *data)
{
	if (vbt)
		rdev_munmap(&vbt_rdev, vbt);

	/* Disable global reset, just in case */
	global_reset_enable(0);
	/* Make sure payload/OS can't trigger global reset */
	global_reset_lock();
}

static void disable_dev(struct device *dev, FSP_S_CONFIG *silconfig) {

	switch (dev->path.pci.devfn) {
	case ISH_DEVFN:
		silconfig->IshEnable = 0;
		break;
	case SATA_DEVFN:
		silconfig->EnableSata = 0;
		break;
	case PCIEB0_DEVFN:
		silconfig->PcieRootPortEn[0] = 0;
		silconfig->PcieRpHotPlug[0] = 0;
		break;
	case PCIEB1_DEVFN:
		silconfig->PcieRootPortEn[1] = 0;
		silconfig->PcieRpHotPlug[1] = 0;
		break;
	case PCIEA0_DEVFN:
		silconfig->PcieRootPortEn[2] = 0;
		silconfig->PcieRpHotPlug[2] = 0;
		break;
	case PCIEA1_DEVFN:
		silconfig->PcieRootPortEn[3] = 0;
		silconfig->PcieRpHotPlug[3] = 0;
		break;
	case PCIEA2_DEVFN:
		silconfig->PcieRootPortEn[4] = 0;
		silconfig->PcieRpHotPlug[4] = 0;
		break;
	case PCIEA3_DEVFN:
		silconfig->PcieRootPortEn[5] = 0;
		silconfig->PcieRpHotPlug[5] = 0;
		break;
	case XHCI_DEVFN:
		silconfig->Usb30Mode = 0;
		break;
	case XDCI_DEVFN:
		silconfig->UsbOtg = 0;
		break;
	case LPSS_DEVFN_I2C0:
		silconfig->I2c0Enable = 0;
		break;
	case LPSS_DEVFN_I2C1:
		silconfig->I2c1Enable = 0;
		break;
	case LPSS_DEVFN_I2C2:
		silconfig->I2c2Enable = 0;
		break;
	case LPSS_DEVFN_I2C3:
		silconfig->I2c3Enable = 0;
		break;
	case LPSS_DEVFN_I2C4:
		silconfig->I2c4Enable = 0;
		break;
	case LPSS_DEVFN_I2C5:
		silconfig->I2c5Enable = 0;
		break;
	case LPSS_DEVFN_I2C6:
		silconfig->I2c6Enable = 0;
		break;
	case LPSS_DEVFN_I2C7:
		silconfig->I2c7Enable = 0;
		break;
	case LPSS_DEVFN_UART0:
		silconfig->Hsuart0Enable = 0;
		break;
	case LPSS_DEVFN_UART1:
		silconfig->Hsuart1Enable = 0;
		break;
	case LPSS_DEVFN_UART2:
		silconfig->Hsuart2Enable = 0;
		break;
	case LPSS_DEVFN_UART3:
		silconfig->Hsuart3Enable = 0;
		break;
	case LPSS_DEVFN_SPI0:
		silconfig->Spi0Enable = 0;
		break;
	case LPSS_DEVFN_SPI1:
		silconfig->Spi1Enable = 0;
		break;
	case LPSS_DEVFN_SPI2:
		silconfig->Spi2Enable = 0;
		break;
	case SDCARD_DEVFN:
		silconfig->SdcardEnabled = 0;
		break;
	case EMMC_DEVFN:
		silconfig->eMMCEnabled = 0;
		break;
	case SDIO_DEVFN:
		silconfig->SdioEnabled = 0;
		break;
	case SMBUS_DEVFN:
		silconfig->SmbusEnable = 0;
		break;
	default:
		printk(BIOS_WARNING, "PCI:%02x.%01x: Could not disable the device\n",
			PCI_SLOT(dev->path.pci.devfn),
			PCI_FUNC(dev->path.pci.devfn));
		break;
	}
}

static void parse_devicetree(FSP_S_CONFIG *silconfig)
{
	struct device *dev = NB_DEV_ROOT;

	if (!dev) {
		printk(BIOS_ERR, "Could not find root device\n");
		return;
	}
	/* Only disable bus 0 devices. */
	for (dev = dev->bus->children; dev; dev = dev->sibling) {
		if (!dev->enabled)
			disable_dev(dev, silconfig);
	}
}

void platform_fsp_silicon_init_params_cb(FSPS_UPD *silupd)
{
        FSP_S_CONFIG *silconfig = &silupd->FspsConfig;
	static struct soc_intel_apollolake_config *cfg;

	/* Load VBT before devicetree-specific config. */
	silconfig->GraphicsConfigPtr = (uintptr_t)vbt;

	struct device *dev = NB_DEV_ROOT;

	if (!dev || !dev->chip_info) {
		printk(BIOS_ERR, "BUG! Could not find SOC devicetree config\n");
		return;
	}

	cfg = dev->chip_info;

	/* Parse device tree and disable unused device*/
	parse_devicetree(silconfig);

	silconfig->PcieRpClkReqNumber[0] = cfg->pcie_rp0_clkreq_pin;
	silconfig->PcieRpClkReqNumber[1] = cfg->pcie_rp1_clkreq_pin;
	silconfig->PcieRpClkReqNumber[2] = cfg->pcie_rp2_clkreq_pin;
	silconfig->PcieRpClkReqNumber[3] = cfg->pcie_rp3_clkreq_pin;
	silconfig->PcieRpClkReqNumber[4] = cfg->pcie_rp4_clkreq_pin;
	silconfig->PcieRpClkReqNumber[5] = cfg->pcie_rp5_clkreq_pin;

	if (cfg->emmc_tx_cmd_cntl != 0)
		silconfig->EmmcTxCmdCntl = cfg->emmc_tx_cmd_cntl;
	if (cfg->emmc_tx_data_cntl1 != 0)
		silconfig->EmmcTxDataCntl1 = cfg->emmc_tx_data_cntl1;
	if (cfg->emmc_tx_data_cntl2 != 0)
		silconfig->EmmcTxDataCntl2 = cfg->emmc_tx_data_cntl2;
	if (cfg->emmc_rx_cmd_data_cntl1 != 0)
		silconfig->EmmcRxCmdDataCntl1 = cfg->emmc_rx_cmd_data_cntl1;
	if (cfg->emmc_rx_strobe_cntl != 0)
		silconfig->EmmcRxStrobeCntl = cfg->emmc_rx_strobe_cntl;
	if (cfg->emmc_rx_cmd_data_cntl2 != 0)
		silconfig->EmmcRxCmdDataCntl2 = cfg->emmc_rx_cmd_data_cntl2;

	silconfig->LPSS_S0ixEnable = cfg->lpss_s0ix_enable;
	silconfig->SkipMpInit = 1;

	/* Disable monitor mwait since it is broken due to a hardware bug without a fix */
	silconfig->MonitorMwaitEnable = 0;

	/* Disable setting of EISS bit in FSP. */
	silconfig->SpiEiss = 0;

	/* Disable FSP from locking access to the RTC NVRAM */
	silconfig->RtcLock = 0;

	/* Enable Audio clk gate and power gate */
	silconfig->HDAudioClkGate = cfg->hdaudio_clk_gate_enable;
	silconfig->HDAudioPwrGate = cfg->hdaudio_pwr_gate_enable;
	/* Bios config lockdown Audio clk and power gate */
	silconfig->BiosCfgLockDown = cfg->hdaudio_bios_config_lockdown;

}

struct chip_operations soc_intel_apollolake_ops = {
	CHIP_NAME("Intel Apollolake SOC")
	.enable_dev = &enable_dev,
	.init = &soc_init,
	.final = &soc_final
};

void platform_fsp_notify_status(enum fsp_notify_phase phase)
{
	/* Hide the P2SB device to align with previous behavior. */
	if (phase == END_OF_FIRMWARE)
		p2sb_hide();
}

/*
 * spi_init() needs to run unconditionally on every boot (including resume) to
 * allow write protect to be disabled for eventlog and nvram updates. This needs
 * to be done as early as possible in ramstage. Thus, add a callback for entry
 * into BS_PRE_DEVICE.
 */
static void spi_init_cb(void *unused)
{
	spi_init();
}

BOOT_STATE_INIT_ENTRY(BS_PRE_DEVICE, BS_ON_ENTRY, spi_init_cb, NULL);
