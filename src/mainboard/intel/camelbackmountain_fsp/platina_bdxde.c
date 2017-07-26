/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017
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

#include "mainboard.h"

#define DEFAULT_GPIOBASE 0x0500


void mainboard_init(void *ignored)
{
        device_t c_dev;
        uint32_t reg32;
        uint16_t reg16;
	uint8_t reg8;

        printk(BIOS_DEBUG, "Mainboard Init\n");

        /* LPC Controller                               */
        /* Enables the LPC_GEN1_DEC iobase for the CPLD */
        c_dev = dev_find_slot(0, PCI_DEVFN(0x1f, 0));
	if(c_dev) {
		reg32 = pci_read_config32(c_dev, 0xf0);
	        printk(BIOS_DEBUG, "RCBA: %x\n", reg32);
		pci_write_config32(c_dev, LPC_GEN1_DEC, 0x00fc0601);
	        reg32 = pci_read_config32(c_dev, LPC_GEN1_DEC);
		printk(BIOS_DEBUG, "LPC_GEN1_DEC: %x\n", reg32);
	}
	else {
		printk(BIOS_DEBUG, "ERROR - could not find PCI 0:1f.0\n");
	}
        
	/* Intel to Broadcom PCIe Links	*/
        /* Selectable_de_emphasis      	*/
        c_dev = dev_find_slot(0, PCI_DEVFN(0x03, 0));
	if(c_dev) {
		reg16 = pci_read_config16(c_dev, 0xc0);
		printk(BIOS_DEBUG, "x86's Lnkcon2: %x\n", reg16);
		pci_write_config16(c_dev, 0xc0, (0x0042));
		reg16 = pci_read_config16(c_dev, 0xc0);
		printk(BIOS_DEBUG, "x86's Lnkcon2: %x\n", reg16);

	}
	else {
		printk(BIOS_DEBUG, "ERROR - could not find PCI 0:03.0\n");
	}
	

        /* U2ECR - USB 2.0                              */
        /* Electrical Control Registers                 */
        /* "Setting 4" for opening the eye diagram      */
        printk(BIOS_DEBUG, "x86's U2ECR: %x\n", pch_iobp_read(0xe5004100));
        pch_iobp_update(0xe5004100, 0xffff80ff, 0x00002400);
        printk(BIOS_DEBUG, "x86's U2ECR: %x\n", pch_iobp_read(0xe5004100));

	/* Disable CPLD boot dog */
	reg8 = inb(0x604);
	outb((reg8 & 0xfd), 0x604);
	printk(BIOS_DEBUG, "CPLD's ctrl-1: %x\n", inb(0x604));
	printk(BIOS_DEBUG, "CPLD's stat-1: %x\n", inb(0x602));
	printk(BIOS_DEBUG, "CPLD's mask-0: %x\n", inb(0x605));

	/* Setup GPIOs Registers */
	outl(0xbfeff7c3, DEFAULT_GPIOBASE + 0x00); /* GPIO_USE_SEL	*/
	outl(0x0910e802, DEFAULT_GPIOBASE + 0x04); /* GP_IO_SEL 	*/
	outl(0xb915403c, DEFAULT_GPIOBASE + 0x0c); /* GP_LVL 		*/

	outl(0x3cff7ff7, DEFAULT_GPIOBASE + 0x30); /* GPIO_USE_SEL2 	*/
	outl(0x03808004, DEFAULT_GPIOBASE + 0x34); /* GP_IO_SEL2 	*/
	outl(0x82800008, DEFAULT_GPIOBASE + 0x38); /* GP_LVL2 		*/

	outl(0x000009fa, DEFAULT_GPIOBASE + 0x40); /* GPIO_USE_SEL3 	*/
	outl(0x00000600, DEFAULT_GPIOBASE + 0x44); /* GP_IO_SEL3 	*/
	outl(0x00000005, DEFAULT_GPIOBASE + 0x48); /* GP_LVL3 		*/

	outl(0x00000000, DEFAULT_GPIOBASE + 0x60); /* GP_RST_SEL1	*/
}
