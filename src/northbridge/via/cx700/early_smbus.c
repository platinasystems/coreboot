/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
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

// other bioses use this, too:
#define SMBUS_IO_BASE		0x0500

#define SMBHSTSTAT		SMBUS_IO_BASE + 0x0
#define SMBSLVSTAT		SMBUS_IO_BASE + 0x1
#define SMBHSTCTL		SMBUS_IO_BASE + 0x2
#define SMBHSTCMD		SMBUS_IO_BASE + 0x3
#define SMBXMITADD		SMBUS_IO_BASE + 0x4
#define SMBHSTDAT0		SMBUS_IO_BASE + 0x5
#define SMBHSTDAT1		SMBUS_IO_BASE + 0x6

#define SMBBLKDAT		SMBUS_IO_BASE + 0x7
#define SMBSLVCTL		SMBUS_IO_BASE + 0x8
#define SMBTRNSADD		SMBUS_IO_BASE + 0x9
#define SMBSLVDATA 		SMBUS_IO_BASE + 0xa
#define SMLINK_PIN_CTL		SMBUS_IO_BASE + 0xe
#define SMBUS_PIN_CTL		SMBUS_IO_BASE + 0xf

/* Define register settings */
#define HOST_RESET		0xff
#define READ_CMD		0x01	// 1 in the 0 bit of SMBHSTADD states to READ

#define SMBUS_TIMEOUT		(100*1000*10)

#define I2C_TRANS_CMD		0x40
#define CLOCK_SLAVE_ADDRESS	0x69

#define SMBUS_DELAY()		outb(0x80, 0x80)

/* Internal functions */
#if CONFIG_DEBUG_SMBUS
static void smbus_print_error(unsigned char host_status_register, int loops)
{
	/* Check if there actually was an error */
	if (host_status_register == 0x00 || host_status_register == 0x40 ||
	    host_status_register == 0x42)
		return;
	printk(BIOS_ERR, "SMBus Error: %02x\n", host_status_register);

	if (loops >= SMBUS_TIMEOUT) {
		printk(BIOS_ERR, "SMBus Timout\n");
	}
	if (host_status_register & (1 << 4)) {
		printk(BIOS_ERR, "Interrup/SMI# was Failed Bus Transaction\n");
	}
	if (host_status_register & (1 << 3)) {
		printk(BIOS_ERR, "Bus Error\n");
	}
	if (host_status_register & (1 << 2)) {
		printk(BIOS_ERR, "Device Error\n");
	}
	if (host_status_register & (1 << 1)) {
		/* This isn't a real error... */
		printk(BIOS_DEBUG, "Interrupt/SMI# was Successful Completion\n");
	}
	if (host_status_register & (1 << 0)) {
		printk(BIOS_ERR, "Host Busy\n");
	}
}
#endif

static void smbus_wait_until_ready(void)
{
	int loops;

	loops = 0;

	/* Yes, this is a mess, but it's the easiest way to do it */
	while (((inb(SMBHSTSTAT) & 1) == 1) && (loops <= SMBUS_TIMEOUT)) {
		SMBUS_DELAY();
		++loops;
	}
#if CONFIG_DEBUG_SMBUS
	/* Some systems seem to have a flakey SMBus. No need to spew a lot of
	 * errors on those, once we know that SMBus access is principally
	 * working.
	 */
	smbus_print_error(inb(SMBHSTSTAT), loops);
#endif
}

static void smbus_reset(void)
{
	outb(HOST_RESET, SMBHSTSTAT);
}

/* Public functions */
static void set_ics_data(unsigned char dev, int data, char len)
{
	smbus_reset();
	/* clear host data port */
	outb(0x00, SMBHSTDAT0);
	SMBUS_DELAY();
	smbus_wait_until_ready();

	/* read to reset block transfer counter */
	inb(SMBHSTCTL);

	/* fill blocktransfer array */
	if (dev == 0xd2) {
		outb(0x0d, SMBBLKDAT);
		outb(0x00, SMBBLKDAT);
		outb(0x3f, SMBBLKDAT);
		outb(0xcd, SMBBLKDAT);
		outb(0x7f, SMBBLKDAT);
		outb(0xbf, SMBBLKDAT);
		outb(0x1a, SMBBLKDAT);
		outb(0x2a, SMBBLKDAT);
		outb(0x01, SMBBLKDAT);
		outb(0x0f, SMBBLKDAT);
		outb(0x0b, SMBBLKDAT);
		outb(0x80, SMBBLKDAT);
		outb(0x8d, SMBBLKDAT);
		outb(0x9b, SMBBLKDAT);
	} else {
		outb(0x08, SMBBLKDAT);
		outb(0xff, SMBBLKDAT);
		outb(0x3f, SMBBLKDAT);
		outb(0x00, SMBBLKDAT);
		outb(0x00, SMBBLKDAT);
		outb(0xff, SMBBLKDAT);
		outb(0xff, SMBBLKDAT);
		outb(0xff, SMBBLKDAT);
		outb(0xff, SMBBLKDAT);
	}

	outb(dev, SMBXMITADD);
	outb(0, SMBHSTCMD);
	outb(len, SMBHSTDAT0);
	outb(0x74, SMBHSTCTL);

	SMBUS_DELAY();

	smbus_wait_until_ready();

	smbus_reset();

}

static unsigned int get_spd_data(const struct mem_controller *ctrl, unsigned int dimm,
				 unsigned int offset)
{
	unsigned int val, addr;

	smbus_reset();

	/* clear host data port */
	outb(0x00, SMBHSTDAT0);
	SMBUS_DELAY();
	smbus_wait_until_ready();

	/* Fetch the SMBus address of the SPD ROM from
	 * the ctrl struct in romstage.c in case they are at
	 * non-standard positions.
	 * SMBus Address shifted by 1
	 */
	addr = (ctrl->channel0[dimm]) << 1;

	outb(addr | 0x1, SMBXMITADD);
	outb(offset, SMBHSTCMD);
	outb(0x48, SMBHSTCTL);

	SMBUS_DELAY();

	smbus_wait_until_ready();

	val = inb(SMBHSTDAT0);
	smbus_reset();
	return val;
}

static void enable_smbus(void)
{
	pci_devfn_t dev;

	/* The CX700 ISA Bridge (0x1106, 0x8324) is hardcoded to this location,
	 * no need to probe.
	 */
	dev = PCI_DEV(0, 17, 0);

	/* SMBus Clock Select: Divider fof 14.318MHz */
	pci_write_config8(dev, 0x94, 0x20);

	/* SMBus I/O Base, enable SMBus */
	pci_write_config16(dev, 0xd0, SMBUS_IO_BASE | 1);

	/* SMBus Clock from 128K Source, Enable SMBus Host Controller */
	pci_write_config8(dev, 0xd2, 0x05);

	/* Enable I/O decoding */
	pci_write_config16(dev, 0x04, 0x0003);

	/* Setup clock chips */
	set_ics_data(0xd2, 0, 14);
	set_ics_data(0xd4, 0, 9);
}

/* Debugging Function */
#if CONFIG_DEBUG_SMBUS
static void dump_spd_data(const struct mem_controller *ctrl)
{
	int dimm, offset, regs;
	unsigned int val;

	for (dimm = 0; dimm < DIMM_SOCKETS; dimm++) {
		printk(BIOS_DEBUG, "SPD Data for DIMM %02x\n", dimm);

		val = get_spd_data(ctrl, dimm, 0);
		if (val == 0xff) {
			regs = 256;
		} else if (val == 0x80) {
			regs = 128;
		} else {
			printk(BIOS_DEBUG, "No DIMM present\n");
			regs = 0;
		}
		for (offset = 0; offset < regs; offset++) {
			printk(BIOS_DEBUG, "  Offset %02x = 0x%02x\n",
				offset, get_spd_data(ctrl, dimm, offset));
		}
	}
}
#else
#define dump_spd_data(ctrl)
#endif
