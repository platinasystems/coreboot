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

#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <arch/io.h>
#include <intelblocks/xhci.h>

__attribute__((weak)) void soc_xhci_init(struct device *dev) { /* no-op */ }

static struct device_operations usb_xhci_ops = {
	.read_resources		= &pci_dev_read_resources,
	.set_resources		= &pci_dev_set_resources,
	.enable_resources	= &pci_dev_enable_resources,
	.init			= soc_xhci_init,
};

static const unsigned short pci_device_ids[] = {
	0x5aa8, /* ApolloLake */
	0x31a8, /* GLK */
	0x9d2f, /* SunRisePoint LP */
	0xa12f, /* KBL-H*/
	0
};

static const struct pci_driver pch_usb_xhci __pci_driver = {
	.ops	 = &usb_xhci_ops,
	.vendor	 = PCI_VENDOR_ID_INTEL,
	.devices	 = pci_device_ids,
};
