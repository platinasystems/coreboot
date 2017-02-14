/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2011 Google Inc.
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
#include <soc/pci_devs.h>
#include <soc/lpc.h>
#include <soc/iobp.h>
#include <arch/io.h>
#include <device/device.h>
#include <device/pci.h>
#include <delay.h>

#include "platina_bdxde.h"


void mainboard_init(device_t dev)
{
        device_t c_dev;
        uint32_t reg32;
        uint16_t reg16;

        printk(BIOS_DEBUG, "Mainboard Init\n");

        /* LPC Controller                               */
        /* Enables the LPC_GEN1_DEC iobase for the CPLD */
        c_dev = dev_find_slot(0, LPC_DEV_FUNC);

        reg32 = pci_read_config32(c_dev, 0xf0);
        printk(BIOS_DEBUG, "RCBA: %x\n", reg32);
        pci_write_config32(c_dev, LPC_GEN1_DEC, 0x00fc0601);
        reg32 = pci_read_config32(c_dev, LPC_GEN1_DEC);
        printk(BIOS_DEBUG, "LPC_GEN1_DEC: %x\n", reg32);

        
	/* Intel to Broadcom PCIe Links	*/
        /* Selectable_de_emphasis      	*/
        c_dev = dev_find_slot(0, PCI_DEVFN(0x03, 0));

	reg16 = pci_read_config16(c_dev, 0xc0);	
       	printk(BIOS_DEBUG, "x86's Lnkcon2: %x\n", reg16);	
        pci_write_config16(c_dev, 0xc0, (reg16|0x0040));
        reg16 = pci_read_config16(c_dev, 0xc0);
        printk(BIOS_DEBUG, "x86's Lnkcon2: %x\n", reg16);
	

        /* U2ECR - USB 2.0                              */
        /* Electrical Control Registers                 */
        /* "Setting 4" for opening the eye diagram      */
        printk(BIOS_DEBUG, "x86's U2ECR: %x\n", pch_iobp_read(0xe5004100));
        pch_iobp_update(0xe5004100, 0xffff80ff, 0x00002400);
        printk(BIOS_DEBUG, "x86's U2ECR: %x\n", pch_iobp_read(0xe5004100));
}
