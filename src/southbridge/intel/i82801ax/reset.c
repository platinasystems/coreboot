/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2002 Eric Biederman <ebiederm@xmission.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <reset.h>
#include <arch/io.h>

void do_hard_reset(void)
{
	/* Try rebooting through port 0xcf9. */
	outb((1 << 2) | (1 << 1), 0xcf9);
}
