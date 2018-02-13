/*
 * SMM utilities used in both SMM and normal mode
 *
 * Copyright (C) 2014 Alexandru Gagniuc <mr.nuke.me@gmail.com>
 * Subject to the GNU GPL v2, or (at your option) any later version.
 */

#include <console/console.h>
#include <soc/southbridge.h>
#include <soc/smi.h>

static void configure_smi(uint8_t smi_num, uint8_t mode)
{
	uint8_t reg32_offset, bit_offset;
	uint32_t reg32;

	if (smi_num >= NUMBER_SMITYPES) {
		printk(BIOS_WARNING, "BUG: Invalid SMI: %u\n", smi_num);
		return;
	}

	/* 16 sources per register, 2 bits per source; registers are 4 bytes */
	reg32_offset = (smi_num / 16) * 4;
	bit_offset = (smi_num % 16) * 2;

	reg32 = smi_read32(SMI_REG_CONTROL0 + reg32_offset);
	reg32 &= ~(0x3 << (bit_offset));
	reg32 |= (mode & 0x3) << bit_offset;
	smi_write32(SMI_REG_CONTROL0 + reg32_offset, reg32);
}

/**
 * Configure generation of interrupts for given GEVENT pin
 *
 * @param gevent The GEVENT pin number. Valid values are 0 thru 23
 * @param mode The type of event this pin should generate. Note that only
 *	       SMI_MODE_SMI generates an SMI. SMI_MODE_DISABLE disables events.
 * @param level SMI_LVL_LOW or SMI_LVL_HIGH
 */
void configure_gevent_smi(uint8_t gevent, uint8_t mode, uint8_t level)
{
	uint32_t reg32;
	/* GEVENT pins range from [0:23] */
	if (gevent > 23) {
		printk(BIOS_WARNING, "BUG: Invalid GEVENT: %u\n", gevent);
		return;
	}

	/* SMI0 source is GEVENT0 and so on */
	configure_smi(gevent, mode);

	/* And set set the trigger level */
	reg32 = smi_read32(SMI_REG_SMITRIG0);
	reg32 &= ~(1 << gevent);
	reg32 |= (level & 0x1) << gevent;
	smi_write32(SMI_REG_SMITRIG0, reg32);
}

/** Disable events from given GEVENT pin */
void disable_gevent_smi(uint8_t gevent)
{
	/* GEVENT pins range from [0:23] */
	if (gevent > 23) {
		printk(BIOS_WARNING, "BUG: Invalid GEVENT: %u\n", gevent);
		return;
	}

	/* SMI0 source is GEVENT0 and so on */
	configure_smi(gevent, SMI_MODE_DISABLE);
}

/** Enable SMIs on writes to ACPI SMI command port */
void enable_acpi_cmd_smi(void)
{
	configure_smi(SMITYPE_SMI_CMD_PORT, SMI_MODE_SMI);
}

uint16_t pm_acpi_smi_cmd_port(void)
{
	return pm_read16(PM_ACPI_SMI_CMD);
}
