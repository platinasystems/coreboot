/*
 * This file is part of the coreboot project.
 *
 * Copyright 2014 Google Inc.
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

#ifndef __BOOTBLOCK_COMMON_H
#define __BOOTBLOCK_COMMON_H

#include <arch/cpu.h>
#include <main_decl.h>
#include <stdint.h>

/*
 * These are defined as weak no-ops that can be overridden by mainboard/SoC.
 * The 'early' variants are called prior to console initialization. Also, the
 * SoC functions are called prior to the mainboard fucntions.
 */
void bootblock_mainboard_early_init(void);
void bootblock_mainboard_init(void);
void bootblock_soc_early_init(void);
void bootblock_soc_init(void);

/*
 * C code entry point for the boot block.
 */
asmlinkage void bootblock_c_entry(uint64_t base_timestamp);

/*
 * This is a the same as the bootblock main(), with the difference that it does
 * not collect a timestamp. Instead it accepts the first timestamp as an
 * argument. This can be used in cases where an earlier stamp is available
 * Note that this function is designed to be entered from C code.
 * This function assumes that the timer has already been initialized, so it
 * does not call init_timer().
 */
asmlinkage void bootblock_main_with_timestamp(uint64_t base_timestamp);

#endif	/* __BOOTBLOCK_COMMON_H */
