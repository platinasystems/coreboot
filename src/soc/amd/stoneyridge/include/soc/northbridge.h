/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Advanced Micro Devices, Inc.
 * Copyright (C) 2015 Intel Corp.
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

#ifndef __PI_STONEYRIDGE_NORTHBRIDGE_H__
#define __PI_STONEYRIDGE_NORTHBRIDGE_H__

#include <arch/io.h>
#include <device/device.h>

/* D18F0 - HT Configuration Registers */
#define D18F0_NODE_ID		0x60
#define D18F0_CPU_CNT		0x62 /* BKDG defines as a field in DWORD 0x60 */
# define CPU_CNT_MASK		0x1f /*  CpuCnt + 1 = no. CPUs */

/* D18F1 - Address Map Registers */

/* MMIO base and limit */
#define D18F1_MMIO_BASE0_LO	0x80
# define MMIO_WE		(1 << 1)
# define MMIO_RE		(1 << 0)
#define D18F1_MMIO_LIMIT0_LO	0x84
# define MMIO_NP		(1 << 7)
#define D18F1_MMIO_BASELIM0_HI	0x180
#define D18F1_MMIO_BASE8_LO	0x1a0
#define D18F1_MMIO_LIMIT8_LO	0x1a4
#define D18F1_MMIO_BASELIM8_HI	0x1c0
#define NB_MMIO_BASE_LO(reg)	((reg) * 2 * sizeof(uint32_t) + (((reg) < 8) \
					? D18F1_MMIO_BASE0_LO \
					: D18F1_MMIO_BASE8_LO \
						- 8 * sizeof(uint64_t)))
#define NB_MMIO_LIMIT_LO(reg)	(NB_MMIO_BASE_LO(reg) + sizeof(uint32_t))
#define NB_MMIO_BASELIM_HI(reg)	((reg) * sizeof(uint32_t) + (((reg) < 8) \
					? D18F1_MMIO_BASELIM0_HI \
					: D18F1_MMIO_BASELIM8_HI \
						- 8 * sizeof(uint32_t)))
/* I/O base and limit */
#define D18F1_IO_BASE0		0xc0
# define IO_WE			(1 << 1)
# define IO_RE			(1 << 0)
#define D18F1_IO_LIMIT0		0xc4
#define NB_IO_BASE(reg)		((reg) * 2 * sizeof(uint32_t) + D18F1_IO_BASE0)
#define NB_IO_LIMIT(reg)	(NB_IO_BASE(reg) + sizeof(uint32_t))

#define D18F1_DRAM_HOLE		0xf0
# define DRAM_HOIST_VALID	(1 << 1)
# define DRAM_HOLE_VALID	(1 << 0)
#define D18F1_VGAEN		0xf4
# define VGA_ADDR_ENABLE	(1 << 0)

enum {
	/* SMM handler area. */
	SMM_SUBREGION_HANDLER,
	/* SMM cache region. */
	SMM_SUBREGION_CACHE,
	/* Chipset specific area. */
	SMM_SUBREGION_CHIPSET,
	/* Total sub regions supported. */
	SMM_SUBREGION_NUM,
};

/*
 * Fills in the arguments for the entire SMM region covered by chipset
 * protections. e.g. TSEG.
 */
void smm_region_info(void **start, size_t *size);
/*
 * Fills in the start and size for the requested SMM subregion. Returns
 * 0 on susccess, < 0 on failure.
 */
int smm_subregion(int sub, void **start, size_t *size);
void domain_enable_resources(device_t dev);
void domain_read_resources(device_t dev);
void domain_set_resources(device_t dev);
void fam15_finalize(void *chip_info);
void setup_uma_memory(void);

#endif /* __PI_STONEYRIDGE_NORTHBRIDGE_H__ */
