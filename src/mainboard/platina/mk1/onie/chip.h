/*
 * This file is part of the coreboot project.
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

#ifndef __PLATINA_MK1_ONIE_H__
#define __PLATINA_MK1_ONIE_H__

#include <arch/acpi_device.h>

struct mainboard_platina_mk1_onie_config {
	int property_count;
	struct acpi_dp property_list[4];	/* Must match devicetree.cb property_count */
	int regs_count;
	uint64_t regs_list[2];			/* Must match devicetree.cb property_count */
	int onie_count;
	struct acpi_dp onie_list[1];		/* Must match devicetree.cb property_count */
};

#endif /* __PLATINA_MK1_ONIE_H__ */
