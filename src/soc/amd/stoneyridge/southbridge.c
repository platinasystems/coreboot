/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Advanced Micro Devices, Inc.
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

#include <console/console.h>

#include <arch/io.h>
#include <arch/acpi.h>
#include <bootstate.h>
#include <cpu/x86/smm.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <cbmem.h>
#include <amd_pci_util.h>
#include <soc/southbridge.h>
#include <soc/smbus.h>
#include <soc/smi.h>
#if IS_ENABLED(CONFIG_STONEYRIDGE_IMC_FWM)
#include <fchec.h>
#endif


int acpi_get_sleep_type(void)
{
	u16 tmp = inw(ACPI_PM1_CNT_BLK);
	tmp = ((tmp & (7 << 10)) >> 10);
	return (int)tmp;
}

void pm_write8(u8 reg, u8 value)
{
	write8((void *)(PM_MMIO_BASE + reg), value);
}

u8 pm_read8(u8 reg)
{
	return read8((void *)(PM_MMIO_BASE + reg));
}

void pm_write16(u8 reg, u16 value)
{
	write16((void *)(PM_MMIO_BASE + reg), value);
}

u16 pm_read16(u16 reg)
{
	return read16((void *)(PM_MMIO_BASE + reg));
}

void sb_enable(device_t dev)
{
	printk(BIOS_DEBUG, "%s\n", __func__);
}

static void sb_init_acpi_ports(void)
{
	/* We use some of these ports in SMM regardless of whether or not
	 * ACPI tables are generated. Enable these ports indiscriminately.
	 */

	pm_write16(PM_EVT_BLK, ACPI_PM_EVT_BLK);
	pm_write16(PM1_CNT_BLK, ACPI_PM1_CNT_BLK);
	pm_write16(PM_TMR_BLK, ACPI_PM_TMR_BLK);
	pm_write16(PM_GPE0_BLK, ACPI_GPE0_BLK);
	/* CpuControl is in \_PR.CP00, 6 bytes */
	pm_write16(PM_CPU_CTRL, ACPI_CPU_CONTROL);

	if (IS_ENABLED(CONFIG_HAVE_SMI_HANDLER)) {
		pm_write16(PM_ACPI_SMI_CMD, APM_CNT);
		enable_acpi_cmd_smi();
	} else {
		pm_write16(PM_ACPI_SMI_CMD, 0);
	}

	/* AcpiDecodeEnable, When set, SB uses the contents of the PM registers
	 * at index 60-6B to decode ACPI I/O address. AcpiSmiEn & SmiCmdEn
	 */
	pm_write8(PM_ACPI_CONF, BIT(0) | BIT(1) | BIT(4) | BIT(2));
}

void southbridge_init(void *chip_info)
{
	sb_init_acpi_ports();
}

void southbridge_final(void *chip_info)
{
#if IS_ENABLED(CONFIG_STONEYRIDGE_IMC_FWM)
	agesawrapper_fchecfancontrolservice();
#if !IS_ENABLED(CONFIG_ACPI_ENABLE_THERMAL_ZONE)
	enable_imc_thermal_zone();
#endif
#endif
}

/*
 * Update the PCI devices with a valid IRQ number
 * that is set in the mainboard PCI_IRQ structures.
 */
static void set_pci_irqs(void *unused)
{
	/* Write PCI_INTR regs 0xC00/0xC01 */
	write_pci_int_table();

	/* Write IRQs for all devicetree enabled devices */
	write_pci_cfg_irqs();
}

/*
 * Hook this function into the PCI state machine
 * on entry into BS_DEV_ENABLE.
 */
BOOT_STATE_INIT_ENTRY(BS_DEV_ENABLE, BS_ON_ENTRY, set_pci_irqs, NULL);
