/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015-2016 Intel Corp.
 * (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _FSP2_0_API_H_
#define _FSP2_0_API_H_

#include <stddef.h>
#include <stdint.h>
#include <fsp/soc_binding.h>

#define FSP_SUCCESS	EFI_SUCCESS

enum fsp_boot_mode {
	FSP_BOOT_WITH_FULL_CONFIGURATION = 0x00,
	FSP_BOOT_WITH_MINIMAL_CONFIGURATION = 0x01,
	FSP_BOOT_ASSUMING_NO_CONFIGURATION_CHANGES = 0x02,
	FSP_BOOT_ON_S4_RESUME = 0x05,
	FSP_BOOT_ON_S3_RESUME = 0x11,
	FSP_BOOT_ON_FLASH_UPDATE = 0x12,
	FSP_BOOT_IN_RECOVERY_MODE = 0x20
};

enum fsp_notify_phase {
	AFTER_PCI_ENUM = 0x20,
	READY_TO_BOOT = 0x40,
	END_OF_FIRMWARE = 0xF0
};


/* Main FSP stages */
void fsp_memory_init(bool s3wake);
void fsp_silicon_init(bool s3wake);

/* Callbacks for updating stage-specific parameters */
void platform_fsp_memory_init_params_cb(FSPM_UPD *mupd, uint32_t version);
void platform_fsp_silicon_init_params_cb(FSPS_UPD *supd);

/* Callback after processing FSP notify */
void platform_fsp_notify_status(enum fsp_notify_phase phase);

/*
 * # DOCUMENTATION:
 *
 * This file defines the interface between coreboot and the FSP 2.0 wrapper
 * fsp_memory_init(), fsp_silicon_init(), and fsp_notify() are the main entry
 * points and map 1:1 to the FSP entry points of the same name.
 *
 * ### fsp_memory_init():
 *     - s3wake: boolean indicating if the system is waking from resume
 *
 * This function is responsible for loading and executing the memory
 * initialization code from the FSP-M binary. It expects this binary to reside
 * in cbfs as FSP_M_FILE.
 *
 * The function takes one parameter, which is described above, but does not
 * take in memory parameters as an argument. The memory parameters can be filled
 * in with platform_fsp_memory_init_params_cb(). This is a callback symbol
 * that fsp_memory_init() will call. The platform must provide this symbol.
 *
 *
 * ### fsp_silicon_init():
 *
 * This function is responsible for loading and executing the silicon
 * initialization code from the FSP-S binary. It expects this binary to reside
 * in cbfs as FSP_S_FILE.
 *
 * Like fsp_memory_init(), it provides a callback to fill in FSP-specific
 * parameters, via platform_fsp_silicon_init_params_cb(). The platform must
 * also provide this symbol.
 *
 *
 * ### fsp_notify():
 *     - phase: Which FSP notification phase
 *
 * This function is responsible for loading and executing the notify code from
 * the FSP-S binary. It expects that fsp_silicon_init() has already been called
 * succesfully, and that the FSP-S binary is still loaded into memory.
 */

#endif /* _FSP2_0_API_H_ */
