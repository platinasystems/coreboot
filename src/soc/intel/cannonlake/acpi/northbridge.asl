/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Intel Corp.
 * (Written by Bora Guvendik <bora.guvendik@intel.com> for Intel Corp.)
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

	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_SEG, Zero)  // _SEG: PCI Segment
	Name (_ADR, Zero)  // _ADR: Address
	Name (_UID, Zero)  // _UID: Unique ID
