/*
 * This file is part of the coreboot project.
 *
 * Copyright 2015 Google Inc.
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

#include <stddef.h>
#include <console/uart.h>
#include <soc/iomap.h>
#include <soc/serialio.h>

uintptr_t uart_platform_base(int idx)
{
	/* Same base address for all debug port usage. In reality UART2
	 * is currently only supported. */
	return UART_BASE_0_ADDR(idx);
}
