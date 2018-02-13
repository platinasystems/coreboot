/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 Uwe Hermann <uwe@hermann-uwe.de>
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

#include <device/pci_def.h>
#include <device/pnp_def.h>
#include <console/console.h>
#include <southbridge/intel/i82371eb/i82371eb.h>
#include <northbridge/intel/i440bx/raminit.h>
#include <cpu/x86/bist.h>
#include <cpu/intel/romstage.h>
/* FIXME: This should be PC97307 (but it's buggy at the moment)! */
#include <superio/nsc/pc97317/pc97317.h>
#include <lib.h>

/* FIXME: This should be PC97307 (but it's buggy at the moment)! */
#define SERIAL_DEV PNP_DEV(0x15c, PC97317_SP1)

int spd_read_byte(unsigned int device, unsigned int address)
{
	return smbus_read_byte(device, address);
}

void mainboard_romstage_entry(unsigned long bist)
{
	/* FIXME: Should be PC97307! */
	pc97317_enable_serial(SERIAL_DEV, CONFIG_TTYS0_BASE);
	console_init();
	report_bist_failure(bist);

	enable_smbus();
	sdram_initialize();
}
