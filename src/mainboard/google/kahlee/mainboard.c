/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015-2017 Advanced Micro Devices, Inc.
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
#include <device/device.h>
#include <arch/acpi.h>
#include <amdblocks/agesawrapper.h>
#include <amdblocks/amd_pci_util.h>
#include <cbmem.h>
#include <baseboard/variants.h>
#include <boardid.h>
#include <soc/nvs.h>
#include <soc/smi.h>
#include <soc/southbridge.h>
#include <variant/ec.h>
#include <variant/thermal.h>
#include <vendorcode/google/chromeos/chromeos.h>

/***********************************************************
 * These arrays set up the FCH PCI_INTR registers 0xC00/0xC01.
 * This table is responsible for physically routing the PIC and
 * IOAPIC IRQs to the different PCI devices on the system.  It
 * is read and written via registers 0xC00/0xC01 as an
 * Index/Data pair.  These values are chipset and mainboard
 * dependent and should be updated accordingly.
 *
 * These values are used by the PCI configuration space,
 * MP Tables.  TODO: Make ACPI use these values too.
 */
const u8 mainboard_picr_data[] = {
	[0x00] = 0x03, 0x04, 0x05, 0x07, 0x0B, 0x0A, 0x1F, 0x1F,
	[0x08] = 0xFA, 0xF1, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x10] = 0x1F, 0x1F, 0x1F, 0x03, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x18] = 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x20] = 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00,
	[0x28] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x30] = 0x05, 0x04, 0x05, 0x04, 0x04, 0x05, 0x04, 0x05,
	[0x38] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x40] = 0x04, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x48] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x50] = 0x03, 0x04, 0x05, 0x07, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x58] = 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x60] = 0x1F, 0x1F, 0x07, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x68] = 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x70] = 0x03, 0x0F, 0x06, 0x0E, 0x0A, 0x0B, 0x1F, 0x1F,
	[0x78] = 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
};

const u8 mainboard_intr_data[] = {
	[0x00] = 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	[0x08] = 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F,
	[0x10] = 0x09, 0x1F, 0x1F, 0x10, 0x1F, 0x1F, 0x1F, 0x10,
	[0x18] = 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x20] = 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00,
	[0x28] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x30] = 0x12, 0x11, 0x12, 0x11, 0x12, 0x11, 0x12, 0x00,
	[0x38] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x40] = 0x11, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x48] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x50] = 0x1F, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00,
	[0x58] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x60] = 0x1F, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x68] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	[0x70] = 0x03, 0x0F, 0x06, 0x0E, 0x0A, 0x0B, 0x1F, 0x1F,
	[0x78] = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* PIRQ Setup */
static void pirq_setup(void)
{
	intr_data_ptr = mainboard_intr_data;
	picr_data_ptr = mainboard_picr_data;
}

static void mainboard_init(void *chip_info)
{
	const struct sci_source *gpes;
	size_t num;
	int boardid = board_id();

	printk(BIOS_INFO, "Board ID: %d\n", boardid);

	mainboard_ec_init();

	gpes = get_gpe_table(&num);
	gpe_configure_sci(gpes, num);
}

/*************************************************
 * Dedicated mainboard function
 *************************************************/
static void kahlee_enable(device_t dev)
{
	printk(BIOS_INFO, "Mainboard "
				CONFIG_MAINBOARD_PART_NUMBER " Enable.\n");

	/* Initialize the PIRQ data structures for consumption */
	pirq_setup();

	dev->ops->acpi_inject_dsdt_generator = chromeos_dsdt_generator;
}


static void mainboard_final(void *chip_info)
{
	struct global_nvs_t *gnvs;

	gnvs = cbmem_find(CBMEM_ID_ACPI_GNVS);

	if (gnvs) {
		gnvs->tmps = CTL_TDP_SENSOR_ID;
		gnvs->tcrt = CRITICAL_TEMPERATURE;
		gnvs->tpsv = PASSIVE_TEMPERATURE;
	}
}

int mainboard_get_xhci_oc_map(uint16_t *map)
{
	return variant_get_xhci_oc_map(map);
}

int mainboard_get_ehci_oc_map(uint16_t *map)
{
	return variant_get_ehci_oc_map(map);
}

struct chip_operations mainboard_ops = {
	.init = mainboard_init,
	.enable_dev = kahlee_enable,
	.final = mainboard_final,
};
