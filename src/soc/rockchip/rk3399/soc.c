/*
 * This file is part of the coreboot project.
 *
 * Copyright 2015 MediaTek Inc.
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

#include <bootmode.h>
#include <console/console.h>
#include <cpu/cpu.h>
#include <device/device.h>
#include <soc/addressmap.h>
#include <soc/clock.h>
#include <soc/display.h>
#include <soc/sdram.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <symbols.h>

static void soc_read_resources(device_t dev)
{
	ram_resource(dev, 0, (uintptr_t)_dram / KiB, sdram_size_mb() * KiB);
}

static void soc_init(device_t dev)
{
	/* reserve bl31 image, which define in
	 * arm-trusted-firmware/plat/rockchip/rk3399/include/platform_def.h
	 */
	mmio_resource(dev, 1, (0x10000 / KiB), (0x80000 / KiB));

	if (IS_ENABLED(CONFIG_MAINBOARD_DO_NATIVE_VGA_INIT) && display_init_required())
		rk_display_init(dev);
	else
		printk(BIOS_INFO, "Display initialization disabled.\n");

	/* We don't need big CPUs, but bring them up as a courtesy to Linux. */
	rkclk_configure_cpu(APLL_600_MHZ, CPU_CLUSTER_BIG);
}

static struct device_operations soc_ops = {
	.read_resources = soc_read_resources,
	.init = soc_init,
};

static void enable_soc_dev(device_t dev)
{
	dev->ops = &soc_ops;
}

struct chip_operations soc_rockchip_rk3399_ops = {
	CHIP_NAME("SOC Rockchip RK3399")
	    .enable_dev = enable_soc_dev,
};
