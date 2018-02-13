/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015-2017 Intel Corporation.
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
#include <device/pci.h>
#include <drivers/intel/gma/i915_reg.h>
#include <intelblocks/graphics.h>
#include <soc/intel/common/opregion.h>
#include <soc/ramstage.h>

uintptr_t fsp_soc_get_igd_bar(void)
{
	return graphics_get_memory_base();
}

void graphics_soc_init(struct device *dev)
{
	u32 ddi_buf_ctl;

	/*
	 * Enable DDI-A (eDP) 4-lane operation if the link is not up yet.
	 * This will allow the kernel to use 4-lane eDP links properly
	 * if the VBIOS or GOP driver does not execute.
	 */
	ddi_buf_ctl = graphics_gtt_read(DDI_BUF_CTL_A);
	if (!acpi_is_wakeup_s3() && !(ddi_buf_ctl & DDI_BUF_CTL_ENABLE)) {
		ddi_buf_ctl |= DDI_A_4_LANES;
		graphics_gtt_write(DDI_BUF_CTL_A, ddi_buf_ctl);
	}

	/*
	 * GFX PEIM module inside FSP binary is taking care of graphics
	 * initialization based on INTEL_GMA_ADD_VBT_DATA_FILE Kconfig
	 * option and input VBT file. Hence no need to load/execute legacy VGA
	 * OpROM in order to initialize GFX.
	 *
	 * In case of non-FSP solution, SoC need to select VGA_ROM_RUN
	 * Kconfig to perform GFX initialization through VGA OpRom.
	 */
	if (IS_ENABLED(CONFIG_INTEL_GMA_ADD_VBT_DATA_FILE))
		return;

	/* IGD needs to Bus Master */
	u32 reg32 = pci_read_config32(dev, PCI_COMMAND);
	reg32 |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY | PCI_COMMAND_IO;
	pci_write_config32(dev, PCI_COMMAND, reg32);

	/* Initialize PCI device, load/execute BIOS Option ROM */
	pci_dev_init(dev);
}

/* Initialize IGD OpRegion, called from ACPI code */
static void update_igd_opregion(igd_opregion_t *opregion)
{
	u16 reg16;

	/* Initialize Mailbox 3 */
	opregion->mailbox3.bclp = IGD_BACKLIGHT_BRIGHTNESS;
	opregion->mailbox3.pfit = IGD_FIELD_VALID | IGD_PFIT_STRETCH;
	opregion->mailbox3.pcft = 0; /* should be (IMON << 1) & 0x3e */
	opregion->mailbox3.cblv = IGD_FIELD_VALID | IGD_INITIAL_BRIGHTNESS;
	opregion->mailbox3.bclm[0] = IGD_WORD_FIELD_VALID + 0x0000;
	opregion->mailbox3.bclm[1] = IGD_WORD_FIELD_VALID + 0x0a19;
	opregion->mailbox3.bclm[2] = IGD_WORD_FIELD_VALID + 0x1433;
	opregion->mailbox3.bclm[3] = IGD_WORD_FIELD_VALID + 0x1e4c;
	opregion->mailbox3.bclm[4] = IGD_WORD_FIELD_VALID + 0x2866;
	opregion->mailbox3.bclm[5] = IGD_WORD_FIELD_VALID + 0x327f;
	opregion->mailbox3.bclm[6] = IGD_WORD_FIELD_VALID + 0x3c99;
	opregion->mailbox3.bclm[7] = IGD_WORD_FIELD_VALID + 0x46b2;
	opregion->mailbox3.bclm[8] = IGD_WORD_FIELD_VALID + 0x50cc;
	opregion->mailbox3.bclm[9] = IGD_WORD_FIELD_VALID + 0x5ae5;
	opregion->mailbox3.bclm[10] = IGD_WORD_FIELD_VALID + 0x64ff;

	/* TODO This may need to happen in S3 resume */
	pci_write_config32(SA_DEV_IGD, ASLS, (u32)opregion);
	reg16 = pci_read_config16(SA_DEV_IGD, SWSCI);
	reg16 &= ~GSSCIE;
	reg16 |= SMISCISEL;
	pci_write_config16(SA_DEV_IGD, SWSCI, reg16);
}

uintptr_t graphics_soc_write_acpi_opregion(struct device *device,
		uintptr_t current, struct acpi_rsdp *rsdp)
{
	igd_opregion_t *opregion;

	/* If GOP is not used, exit here */
	if (!IS_ENABLED(CONFIG_INTEL_GMA_ADD_VBT_DATA_FILE))
		return current;

	/* If IGD is disabled, exit here */
	if (pci_read_config16(device, PCI_VENDOR_ID) == 0xFFFF)
		return current;

	printk(BIOS_DEBUG, "ACPI: * IGD OpRegion\n");
	opregion = (igd_opregion_t *)current;

	if (init_igd_opregion(opregion) != CB_SUCCESS)
		return current;

	update_igd_opregion(opregion);
	current += sizeof(igd_opregion_t);
	current = acpi_align_current(current);

	printk(BIOS_DEBUG, "current = %lx\n", current);
	return current;
}
