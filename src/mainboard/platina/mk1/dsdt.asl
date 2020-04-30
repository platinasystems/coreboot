/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2011 Google Inc.
 * Copyright (C) 2015-2016 Intel Corp.
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

#include <arch/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x02,		// DSDT revision: ACPI v2.0 and up
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20110725	// OEM revision
)
{
	#include "acpi/platform.asl"

	Name(_S0, Package() { 0x00, 0x00, 0x00, 0x00 })
	Name(_S5, Package() { 0x07, 0x00, 0x00, 0x00 })

	Scope (\_SB)
	{
		Device (PCI0)
		{
			#include <acpi/southcluster.asl>
			#include <acpi/pcie1.asl>
		}

		Name (PRUN, Package() {
			Package() { 0x0008FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0008FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0008FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0008FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0009FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0009FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0009FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0009FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000AFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000AFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000AFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000AFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000BFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000BFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000BFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000BFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000CFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000CFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000CFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000CFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000DFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000DFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000DFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000DFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000EFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000EFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000EFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000EFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x000FFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x000FFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x000FFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x000FFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0010FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0010FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0010FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0010FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0011FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0011FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0011FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0011FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0012FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0012FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0012FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0012FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0013FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0013FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0013FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0013FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0014FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0014FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0014FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0014FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0016FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0016FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0016FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0016FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0017FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0017FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0017FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0017FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0018FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0018FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0018FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0018FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x0019FFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x0019FFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x0019FFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x0019FFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x001CFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x001CFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x001CFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x001CFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x001DFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x001DFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x001DFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x001DFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x001EFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x001EFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x001EFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x001EFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },

			Package() { 0x001FFFFF, 0, \_SB.PCI0.LPC0.LNKA, 0 },
			Package() { 0x001FFFFF, 1, \_SB.PCI0.LPC0.LNKB, 0 },
			Package() { 0x001FFFFF, 2, \_SB.PCI0.LPC0.LNKC, 0 },
			Package() { 0x001FFFFF, 3, \_SB.PCI0.LPC0.LNKD, 0 },
		})

		Name (ARUN, Package() {
			Package() { 0x0008FFFF, 0, 0, 16 },
			Package() { 0x0008FFFF, 1, 0, 17 },
			Package() { 0x0008FFFF, 2, 0, 18 },
			Package() { 0x0008FFFF, 3, 0, 19 },

			Package() { 0x0009FFFF, 0, 0, 16 },
			Package() { 0x0009FFFF, 1, 0, 17 },
			Package() { 0x0009FFFF, 2, 0, 18 },
			Package() { 0x0009FFFF, 3, 0, 19 },

			Package() { 0x000AFFFF, 0, 0, 16 },
			Package() { 0x000AFFFF, 1, 0, 17 },
			Package() { 0x000AFFFF, 2, 0, 18 },
			Package() { 0x000AFFFF, 3, 0, 19 },

			Package() { 0x000BFFFF, 0, 0, 16 },
			Package() { 0x000BFFFF, 1, 0, 17 },
			Package() { 0x000BFFFF, 2, 0, 18 },
			Package() { 0x000BFFFF, 3, 0, 19 },

			Package() { 0x000CFFFF, 0, 0, 16 },
			Package() { 0x000CFFFF, 1, 0, 17 },
			Package() { 0x000CFFFF, 2, 0, 18 },
			Package() { 0x000CFFFF, 3, 0, 19 },

			Package() { 0x000DFFFF, 0, 0, 16 },
			Package() { 0x000DFFFF, 1, 0, 17 },
			Package() { 0x000DFFFF, 2, 0, 18 },
			Package() { 0x000DFFFF, 3, 0, 19 },

			Package() { 0x000EFFFF, 0, 0, 16 },
			Package() { 0x000EFFFF, 1, 0, 17 },
			Package() { 0x000EFFFF, 2, 0, 18 },
			Package() { 0x000EFFFF, 3, 0, 19 },

			Package() { 0x000FFFFF, 0, 0, 16 },
			Package() { 0x000FFFFF, 1, 0, 17 },
			Package() { 0x000FFFFF, 2, 0, 18 },
			Package() { 0x000FFFFF, 3, 0, 19 },

			Package() { 0x0010FFFF, 0, 0, 16 },
			Package() { 0x0010FFFF, 1, 0, 17 },
			Package() { 0x0010FFFF, 2, 0, 18 },
			Package() { 0x0010FFFF, 3, 0, 19 },

			Package() { 0x0011FFFF, 0, 0, 16 },
			Package() { 0x0011FFFF, 1, 0, 17 },
			Package() { 0x0011FFFF, 2, 0, 18 },
			Package() { 0x0011FFFF, 3, 0, 19 },

			Package() { 0x0012FFFF, 0, 0, 16 },
			Package() { 0x0012FFFF, 1, 0, 17 },
			Package() { 0x0012FFFF, 2, 0, 18 },
			Package() { 0x0012FFFF, 3, 0, 19 },

			Package() { 0x0013FFFF, 0, 0, 16 },
			Package() { 0x0013FFFF, 1, 0, 17 },
			Package() { 0x0013FFFF, 2, 0, 18 },
			Package() { 0x0013FFFF, 3, 0, 19 },

			Package() { 0x0014FFFF, 0, 0, 16 },
			Package() { 0x0014FFFF, 1, 0, 17 },
			Package() { 0x0014FFFF, 2, 0, 18 },
			Package() { 0x0014FFFF, 3, 0, 19 },

			Package() { 0x0016FFFF, 0, 0, 16 },
			Package() { 0x0016FFFF, 1, 0, 17 },
			Package() { 0x0016FFFF, 2, 0, 18 },
			Package() { 0x0016FFFF, 3, 0, 19 },

			Package() { 0x0017FFFF, 0, 0, 16 },
			Package() { 0x0017FFFF, 1, 0, 17 },
			Package() { 0x0017FFFF, 2, 0, 18 },
			Package() { 0x0017FFFF, 3, 0, 19 },

			Package() { 0x0018FFFF, 0, 0, 16 },
			Package() { 0x0018FFFF, 1, 0, 17 },
			Package() { 0x0018FFFF, 2, 0, 18 },
			Package() { 0x0018FFFF, 3, 0, 19 },

			Package() { 0x0019FFFF, 0, 0, 16 },
			Package() { 0x0019FFFF, 1, 0, 17 },
			Package() { 0x0019FFFF, 2, 0, 18 },
			Package() { 0x0019FFFF, 3, 0, 19 },

			Package() { 0x001CFFFF, 0, 0, 16 },
			Package() { 0x001CFFFF, 1, 0, 17 },
			Package() { 0x001CFFFF, 2, 0, 18 },
			Package() { 0x001CFFFF, 3, 0, 19 },

			Package() { 0x001DFFFF, 0, 0, 16 },
			Package() { 0x001DFFFF, 1, 0, 17 },
			Package() { 0x001DFFFF, 2, 0, 18 },
			Package() { 0x001DFFFF, 3, 0, 19 },

			Package() { 0x001EFFFF, 0, 0, 16 },
			Package() { 0x001EFFFF, 1, 0, 17 },
			Package() { 0x001EFFFF, 2, 0, 18 },
			Package() { 0x001EFFFF, 3, 0, 19 },

			Package() { 0x001FFFFF, 0, 0, 16 },
			Package() { 0x001FFFFF, 1, 0, 17 },
			Package() { 0x001FFFFF, 2, 0, 18 },
			Package() { 0x001FFFFF, 3, 0, 19 },
		})

		Device (UNC0)
		{
			Name (_HID, EisaId ("PNP0A03"))
			Name (_UID, 0x3F)
			Method (_BBN, 0, NotSerialized)
			{
				Return (0xff)
			}

			Name (_ADR, 0x00)
			Method (_STA, 0, NotSerialized)
			{
				Return (0xf)
			}

			Name (_CRS, ResourceTemplate ()
			{
				WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x00FF,             // Range Minimum
					0x00FF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0001,             // Length
					,, )
			})

			Method (_PRT, 0, NotSerialized)
			{
				If (LEqual (PICM, Zero))
				{
					Return (PRUN)
				}

				Return (ARUN)
			}
		}
	}

	#include "acpi/mainboard.asl"

	Scope (\_SB.PCI0.SBUS)
	{
		Device (NVM0)
		{	
			Name (_HID, "INT3499") /* _HID: Hardware ID */
			Name (_UID, Zero)  /* _UID: Unique ID */
			Name (_DDN, "ONIE")  /* _DDN: DOS Device Name */

			Method (_STA, 0, NotSerialized)  /* _STA: Status */
			{
				Return (0x0F)
			}

			Name (_CRS, ResourceTemplate ()
			{
				I2cSerialBus (0x0051,
					     ControllerInitiated,
					     400000, // Bus Speed
					     AddressingMode7Bit,
					     "\\_SB.PCI0.SBUS", // Link to host controller
					     0x00, // Resource source index, MBZ
					     ResourceConsumer,
					     ,) // Descriptor Name
			})

			Name (_DSD, Package ()
			{
				ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () { "size", 16384 },
					Package () { "pagesize", 64 },
					Package () { "no-read-rollover", 1 },
					Package () { "address-width", 16 },
				},
				ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
				Package () {
					Package () { "onie-data", NVRG },
				}
			})

			Name (NVRG, Package() {
				ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () { "reg", Package() { 0x0, 0x0800 } },
				}
			})
		}
		
		Device (NVM1)
		{	
			Name (_HID, "INT3499") /* _HID: Hardware ID */
			Name (_UID, Zero)  /* _UID: Unique ID */
			Name (_DDN, "ONIE")  /* _DDN: DOS Device Name */

			Method (_STA, 0, NotSerialized)  /* _STA: Status */
			{
				Return (0x0F)
			}

			Name (_CRS, ResourceTemplate ()
			{
				I2cSerialBus (0x0053,
					     ControllerInitiated,
					     400000, // Bus Speed
					     AddressingMode7Bit,
					     "\\_SB.PCI0.SBUS", // Link to host controller
					     0x00, // Resource source index, MBZ
					     ResourceConsumer,
					     ,) // Descriptor Name
			})

			Name (_DSD, Package ()
			{
				ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () { "size", 16384 },
					Package () { "pagesize", 64 },
					Package () { "no-read-rollover", 1 },
					Package () { "address-width", 16 },
				},
				ToUUID ("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
				Package () {
					Package () { "onie-data", "NVRG" },
				}
			})

			Name (NVRG, Package() {
				ToUUID ("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () { "reg", Package() { 0x0, 0x0800 } },
				}
			})
		}

		Device (ONI0)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
                	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     Package () {
                             	     Package () { "compatible", "linux,onie" },
				     Package () { "nvmem-cells", Package() { NVM0 } },
				     Package () { "nvmem-cell-names", Package() { "onie-data" } },
                	     }
        		})
		}

		Device (ONI1)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
                	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     Package () {
                             	     Package () { "compatible", "linux,onie" },
				     Package () { "nvmem-cells", Package() { NVM1 } },
				     Package () { "nvmem-cell-names", Package() { "onie-data" } },
                	     }
        		})
		}

		Device (TMP0)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
                	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     Package () {
                             	     Package () { "compatible", "ti,tmp75" },
                	     }
        		})
        		Method (_CRS, 0, Serialized)
        		{
				Name (SBUF, ResourceTemplate ()
                		{
					I2cSerialBusV2 (0x4f, ControllerInitiated,
                                	400000, AddressingMode7Bit,
                                	"\\_SB.PCI0.SBUS", 0x00,
                                	ResourceConsumer, , Exclusive,)
               			})
                		Return (SBUF)
        		}
		}
	}	
}
