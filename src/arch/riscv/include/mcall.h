/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 The ChromiumOS Authors
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

#ifndef _MCALL_H
#define _MCALL_H

// NOTE: this is the size of hls_t below. A static_assert would be
// nice to have.
#define HLS_SIZE 64

/* We save 37 registers, currently. */
#define MENTRY_FRAME_SIZE (HLS_SIZE + 37 * 8)

#define MCALL_HART_ID			 0
#define MCALL_NUM_HARTS			 1
#define MCALL_QUERY_MEMORY		 2
#define MCALL_CONSOLE_PUTCHAR		 3
#define MCALL_CONSOLE_GETCHAR		 4
#define MCALL_SEND_IPI			 6
#define MCALL_CLEAR_IPI			 7
#define MCALL_SHUTDOWN			 8
#define MCALL_SET_TIMER			 9
#define MCALL_REMOTE_SFENCE_VM		10
#define MCALL_REMOTE_FENCE_I		11
#define MCALL_CONFIG_STRING_BASE	12
#define MCALL_CONFIG_STRING_SIZE	13

#ifndef __ASSEMBLER__

#include <arch/encoding.h>
#include <atomic.h>
#include <stdint.h>

typedef struct {
	unsigned long base;
	unsigned long size;
	unsigned long node_id;
} memory_block_info;

typedef struct {
	unsigned long dev;
	unsigned long cmd;
	unsigned long data;
	unsigned long sbi_private_data;
} sbi_device_message;


typedef struct {
	sbi_device_message *device_request_queue_head;
	unsigned long device_request_queue_size;
	sbi_device_message *device_response_queue_head;
	sbi_device_message *device_response_queue_tail;

	int hart_id;
	int ipi_pending;
	uint64_t *timecmp;
	uint64_t *time;
} hls_t;

#define MACHINE_STACK_TOP() ({ \
  /* coverity[uninit_use] : FALSE */ \
  register uintptr_t sp asm ("sp"); \
  (void*)((sp + RISCV_PGSIZE) & -RISCV_PGSIZE); })

// hart-local storage, at top of stack
#define HLS() ((hls_t*)(MACHINE_STACK_TOP() - HLS_SIZE))
#define OTHER_HLS(id) ((hls_t*)((void*)HLS() + RISCV_PGSIZE * ((id) - HLS()->hart_id)))

#define MACHINE_STACK_SIZE RISCV_PGSIZE

uintptr_t mcall_query_memory(uintptr_t id, memory_block_info *p);
uintptr_t mcall_console_putchar(uint8_t ch);
uintptr_t mcall_dev_req(sbi_device_message *m);
uintptr_t mcall_dev_resp(void);
uintptr_t mcall_set_timer(unsigned long long when);
uintptr_t mcall_clear_ipi(void);
uintptr_t mcall_send_ipi(uintptr_t recipient);
uintptr_t mcall_shutdown(void);
void hls_init(uint32_t hart_id); // need to call this before launching linux

#endif // __ASSEMBLER__

#endif
