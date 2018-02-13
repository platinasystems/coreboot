/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
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

#include <stdint.h>
#include <delay.h>
#include <arch/io.h>
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <cpu/intel/microcode/microcode.c>
#include <reset.h>
#include <lib.h>
#include <soc/bootblock.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <soc/msr.h>
#include <soc/pci_devs.h>
#include <soc/spi.h>

/* Soft Reset Data Register Bit 12 = MAX Boot Frequency */
#define SPI_STRAP_MAX_FREQ	(1<<12)
/* Soft Reset Data Register Bit 6-11 = Flex Ratio */
#define FLEX_RATIO_BIT	6

static void set_pch_cpu_strap(u8 flex_ratio)
{
	uint8_t *spibar = (void *)SPI_BASE_ADDRESS;
	u32 ssl, ssms, soft_reset_data;


	/* Set Strap Lock Disable */
	ssl = read32(spibar + SPIBAR_RESET_LOCK);
	ssl |= SPIBAR_RESET_LOCK_DISABLE;
	write32(spibar + SPIBAR_RESET_LOCK, ssl);

	/* Soft Reset Data Register Bit 12 = MAX Boot Frequency
	 * Bit 6-11 = Flex Ratio
	 * Soft Reset Data register located at SPIBAR0 offset 0xF8[0:15].
	 */
	soft_reset_data = SPI_STRAP_MAX_FREQ;
	soft_reset_data |= (flex_ratio << FLEX_RATIO_BIT);
	write32(spibar + SPIBAR_RESET_DATA, soft_reset_data);

	/* Set Strap Mux Select  set to '1' */
	ssms = read32(spibar + SPIBAR_RESET_CTRL);
	ssms |= SPIBAR_RESET_CTRL_SSMC;
	write32(spibar + SPIBAR_RESET_CTRL, ssms);

	/* Set Strap Lock Enable */
	ssl = read32(spibar + SPIBAR_RESET_LOCK);
	ssl |= SPIBAR_RESET_LOCK_ENABLE;
	write32(spibar + SPIBAR_RESET_LOCK, ssl);
}

static void set_flex_ratio_to_tdp_nominal(void)
{
	msr_t flex_ratio, msr;
	u8 nominal_ratio;

	/* Check for Flex Ratio support */
	flex_ratio = rdmsr(MSR_FLEX_RATIO);
	if (!(flex_ratio.lo & FLEX_RATIO_EN))
		return;

	/* Check for >0 configurable TDPs */
	msr = rdmsr(MSR_PLATFORM_INFO);
	if (((msr.hi >> 1) & 3) == 0)
		return;

	/* Use nominal TDP ratio for flex ratio */
	msr = rdmsr(MSR_CONFIG_TDP_NOMINAL);
	nominal_ratio = msr.lo & 0xff;

	/* See if flex ratio is already set to nominal TDP ratio */
	if (((flex_ratio.lo >> 8) & 0xff) == nominal_ratio)
		return;

	/* Set flex ratio to nominal TDP ratio */
	flex_ratio.lo &= ~0xff00;
	flex_ratio.lo |= nominal_ratio << 8;
	flex_ratio.lo |= FLEX_RATIO_LOCK;
	wrmsr(MSR_FLEX_RATIO, flex_ratio);

	/* Set PCH Soft Reset Data Register with new Flex Ratio */
	set_pch_cpu_strap(nominal_ratio);

	/* Delay before reset to avoid potential TPM lockout */
	mdelay(30);

	/* Issue soft reset, will be "CPU only" due to soft reset data */
	soft_reset();
}

static void cache_bios_region(void)
{
	int mtrr;
	size_t rom_size;
	uint32_t alignment;

	mtrr = get_free_var_mtrr();

	if (mtrr == -1)
		return;

	/* Only the IFD BIOS region is memory mapped (at top of 4G) */
	rom_size = CONFIG_ROM_SIZE;

	if (!rom_size)
		return;

	/* Round to power of two */
	alignment = 1 << (log2_ceil(rom_size));
	rom_size = ALIGN_UP(rom_size, alignment);
	set_var_mtrr(mtrr, 4ULL*GiB - rom_size, rom_size, MTRR_TYPE_WRPROT);
}

void bootblock_cpu_init(void)
{
	cache_bios_region();
	/* Set flex ratio and reset if needed */
	set_flex_ratio_to_tdp_nominal();
	intel_update_microcode_from_cbfs();
}

void set_max_freq(void)
{
	msr_t msr, perf_ctl, platform_info;

	/* Check for configurable TDP option */
	platform_info = rdmsr(MSR_PLATFORM_INFO);

	if ((platform_info.hi >> 1) & 3) {
		/* Set to nominal TDP ratio */
		msr = rdmsr(MSR_CONFIG_TDP_NOMINAL);
		perf_ctl.lo = (msr.lo & 0xff) << 8;
	} else {
		/* Platform Info bits 15:8 give max ratio */
		msr = rdmsr(MSR_PLATFORM_INFO);
		perf_ctl.lo = msr.lo & 0xff00;
	}

	perf_ctl.hi = 0;
	wrmsr(MSR_IA32_PERF_CTL, perf_ctl);

	printk(BIOS_DEBUG, "CPU: frequency set to %d MHz\n",
		((perf_ctl.lo >> 8) & 0xff) * CPU_BCLK);
}
