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

	scope (\_SB)
	{
		Device (ONI0)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
                	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     Package () {
                             	     Package () { "compatible", "linux,onie" },
				     Package () { "nvmem-cells", Package() { \_SB.PCI0.SBUS.NVM0 } },
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
				     Package () { "nvmem-cells", Package() { \_SB.PCI0.SBUS.NVM1 } },
				     Package () { "nvmem-cell-names", Package() { "onie-data" } },
                	     }
        		})
		}
	}
	
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

		Device (MUX0)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
                	     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     Package () {
                             	     Package () { "compatible", "nxp,pca9548" },
                	     }
        		})
        		Name (_CRS, ResourceTemplate()
			{
				I2cSerialBus (0x70, ControllerInitiated,
                                		     400000, AddressingMode7Bit,
                                		     "\\_SB.PCI0.SBUS", 0x00,
                                		     ResourceConsumer, ,)
			})

			Device (CH00)
			{
				Name (_ADR, 0)

				Device (QS00)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
                	     		     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     		     Package () {
						     Package () { "compatible", "nxp,pca9548" },
                	     		     }
					})

					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x71,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH00", 0x00,
					     ResourceConsumer, ,)
					     })
				}
			}

			Device (CH01)
			{
				Name (_ADR, 1)

				Device (QS10)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
                	     		     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     		     Package () {
						     Package () { "compatible", "nxp,pca9548" },
                	     		     }
					})

					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x71,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH01", 0x00,
					     ResourceConsumer,,)
					})
				}
			}

			Device (CH02)
			{
				Name (_ADR, 2)

				Device (QS20)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
                	     		     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     		     Package () {
						     Package () { "compatible", "nxp,pca9548" },
                	     		     }
					})

					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x71,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH02", 0x00,
					     ResourceConsumer,,)
					})
				}
			}

			Device (CH03)
			{
				Name (_ADR, 3)

				Device (QS30)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
                	     		     ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     		     Package () {
						     Package () { "compatible", "nxp,pca9548" },
                	     		     }
					})

					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x71,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH03", 0x00,
					     ResourceConsumer,,)
					})
				}
			}

			Device (CH04)
			{
				Name (_ADR, 4)

				Device (QS40)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT0_ABS",  "PORT1_ABS", 
						    			"PORT2_ABS",  "PORT3_ABS", 
									"PORT4_ABS",  "PORT5_ABS", 
									"PORT6_ABS",  "PORT7_ABS", 
						 			"PORT8_ABS",  "PORT9_ABS",
									"PORT10_ABS",  "PORT11_ABS",
									"PORT12_ABS",  "PORT13_ABS",
									"PORT14_ABS",  "PORT15_ABS"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port0-abs", "G00A"},
							Package () {"gpio-port1-abs", "G01A"},
							Package () {"gpio-port2-abs", "G02A"},
							Package () {"gpio-port3-abs", "G03A"},
							Package () {"gpio-port4-abs", "G04A"},
							Package () {"gpio-port5-abs", "G05A"},
							Package () {"gpio-port6-abs", "G06A"},
							Package () {"gpio-port7-abs", "G07A"},
							Package () {"gpio-port8-abs", "G08A"},
							Package () {"gpio-port9-abs", "G09A"},
							Package () {"gpio-port10-abs", "G10A"},
							Package () {"gpio-port11-abs", "G11A"},
							Package () {"gpio-port12-abs", "G12A"},
							Package () {"gpio-port13-abs", "G13A"},
							Package () {"gpio-port14-abs", "G14A"},
							Package () {"gpio-port15-abs", "G15A"},
						}
					})

					Name (G00A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G01A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G02A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G03A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G04A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G05A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G06A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G07A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G08A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G09A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G10A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G11A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G12A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G13A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G14A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G15A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x20,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH04", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS41)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT16_ABS",  "PORT17_ABS", 
						    			"PORT18_ABS",  "PORT19_ABS", 
									"PORT20_ABS",  "PORT21_ABS", 
									"PORT22_ABS",  "PORT23_ABS", 
						 			"PORT24_ABS",  "PORT25_ABS",
									"PORT26_ABS",  "PORT27_ABS",
									"PORT28_ABS",  "PORT29_ABS",
									"PORT30_ABS",  "PORT31_ABS"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port16-abs", "G16A"},
							Package () {"gpio-port17-abs", "G17A"},
							Package () {"gpio-port18-abs", "G18A"},
							Package () {"gpio-port19-abs", "G19A"},
							Package () {"gpio-port20-abs", "G20A"},
							Package () {"gpio-port21-abs", "G21A"},
							Package () {"gpio-port22-abs", "G22A"},
							Package () {"gpio-port23-abs", "G23A"},
							Package () {"gpio-port24-abs", "G24A"},
							Package () {"gpio-port25-abs", "G25A"},
							Package () {"gpio-port26-abs", "G26A"},
							Package () {"gpio-port27-abs", "G27A"},
							Package () {"gpio-port28-abs", "G28A"},
							Package () {"gpio-port29-abs", "G29A"},
							Package () {"gpio-port30-abs", "G30A"},
							Package () {"gpio-port31-abs", "G31A"},
						}
					})

					Name (G16A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G17A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G18A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G19A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G20A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G21A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G22A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G23A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G24A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G25A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G26A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G27A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G28A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G29A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G30A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G31A, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x21,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH04", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS42)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT0_INT_L",  "PORT1_INT_L", 
						    			"PORT2_INT_L",  "PORT3_INT_L", 
									"PORT4_INT_L",  "PORT5_INT_L", 
									"PORT6_INT_L",  "PORT7_INT_L", 
						 			"PORT8_INT_L",  "PORT9_INT_L",
									"PORT10_INT_L",  "PORT11_INT_L",
									"PORT12_INT_L",  "PORT13_INT_L",
									"PORT14_INT_L",  "PORT15_INT_L"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port0-int-l", "G00I"},
							Package () {"gpio-port1-int-l", "G01I"},
							Package () {"gpio-port2-int-l", "G02I"},
							Package () {"gpio-port3-int-l", "G03I"},
							Package () {"gpio-port4-int-l", "G04I"},
							Package () {"gpio-port5-int-l", "G05I"},
							Package () {"gpio-port6-int-l", "G06I"},
							Package () {"gpio-port7-int-l", "G07I"},
							Package () {"gpio-port8-int-l", "G08I"},
							Package () {"gpio-port9-int-l", "G09I"},
							Package () {"gpio-port10-int-l", "G10I"},
							Package () {"gpio-port11-int-l", "G11I"},
							Package () {"gpio-port12-int-l", "G12I"},
							Package () {"gpio-port13-int-l", "G13I"},
							Package () {"gpio-port14-int-l", "G14I"},
							Package () {"gpio-port15-int-l", "G15I"},
						}
					})

					Name (G00I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G01I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G02I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G03I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G04I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G05I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G06I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G07I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G08I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G09I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G10I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G11I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G12I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G13I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G14I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G15I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x22,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH04", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS43)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT16_INT_L",  "PORT17_INT_L", 
						    			"PORT18_INT_L",  "PORT19_INT_L", 
									"PORT20_INT_L",  "PORT21_INT_L", 
									"PORT22_INT_L",  "PORT23_INT_L", 
						 			"PORT24_INT_L",  "PORT25_INT_L",
									"PORT26_INT_L",  "PORT27_INT_L",
									"PORT28_INT_L",  "PORT29_INT_L",
									"PORT30_INT_L",  "PORT31_INT_L"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port16-int-l", "G16I"},
							Package () {"gpio-port17-int-l", "G17I"},
							Package () {"gpio-port18-int-l", "G18I"},
							Package () {"gpio-port19-int-l", "G19I"},
							Package () {"gpio-port20-int-l", "G20I"},
							Package () {"gpio-port21-int-l", "G21I"},
							Package () {"gpio-port22-int-l", "G22I"},
							Package () {"gpio-port23-int-l", "G23I"},
							Package () {"gpio-port24-int-l", "G24I"},
							Package () {"gpio-port25-int-l", "G25I"},
							Package () {"gpio-port26-int-l", "G26I"},
							Package () {"gpio-port27-int-l", "G27I"},
							Package () {"gpio-port28-int-l", "G28I"},
							Package () {"gpio-port29-int-l", "G29I"},
							Package () {"gpio-port30-int-l", "G30I"},
							Package () {"gpio-port31-int-l", "G31I"},
						}
					})

					Name (G16I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G17I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G18I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G19I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G20I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G21I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G22I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G23I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G24I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G25I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G26I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G27I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G28I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G29I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G30I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G31I, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x23,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH04", 0x00,
					     ResourceConsumer,,)
					})
				}
			}

			Device (CH05)
			{
				Name (_ADR, 5)

				Device (QS40)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT0_LPMODE",  "PORT1_LPMODE", 
						    			"PORT2_LPMODE",  "PORT3_LPMODE", 
									"PORT4_LPMODE",  "PORT5_LPMODE", 
									"PORT6_LPMODE",  "PORT7_LPMODE", 
						 			"PORT8_LPMODE",  "PORT9_LPMODE",
									"PORT10_LPMODE",  "PORT11_LPMODE",
									"PORT12_LPMODE",  "PORT13_LPMODE",
									"PORT14_LPMODE",  "PORT15_LPMODE"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port0-lpmode", "G00L"},
							Package () {"gpio-port1-lpmode", "G01L"},
							Package () {"gpio-port2-lpmode", "G02L"},
							Package () {"gpio-port3-lpmode", "G03L"},
							Package () {"gpio-port4-lpmode", "G04L"},
							Package () {"gpio-port5-lpmode", "G05L"},
							Package () {"gpio-port6-lpmode", "G06L"},
							Package () {"gpio-port7-lpmode", "G07L"},
							Package () {"gpio-port8-lpmode", "G08L"},
							Package () {"gpio-port9-lpmode", "G09L"},
							Package () {"gpio-port10-lpmode", "G10L"},
							Package () {"gpio-port11-lpmode", "G11L"},
							Package () {"gpio-port12-lpmode", "G12L"},
							Package () {"gpio-port13-lpmode", "G13L"},
							Package () {"gpio-port14-lpmode", "G14L"},
							Package () {"gpio-port15-lpmode", "G15L"},
						}
					})

					Name (G00L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G01L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G02L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G03L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G04L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G05L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G06L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G07L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G08L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G09L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G10L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G11L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G12L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G13L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G14L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G15L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x20,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH05", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS41)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT16_LPMODE",  "PORT17_LPMODE", 
						    			"PORT18_LPMODE",  "PORT19_LPMODE", 
									"PORT20_LPMODE",  "PORT21_LPMODE", 
									"PORT22_LPMODE",  "PORT23_LPMODE", 
						 			"PORT24_LPMODE",  "PORT25_LPMODE",
									"PORT26_LPMODE",  "PORT27_LPMODE",
									"PORT28_LPMODE",  "PORT29_LPMODE",
									"PORT30_LPMODE",  "PORT31_LPMODE"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port16-lpmode", "G16L"},
							Package () {"gpio-port17-lpmode", "G17L"},
							Package () {"gpio-port18-lpmode", "G18L"},
							Package () {"gpio-port19-lpmode", "G19L"},
							Package () {"gpio-port20-lpmode", "G20L"},
							Package () {"gpio-port21-lpmode", "G21L"},
							Package () {"gpio-port22-lpmode", "G22L"},
							Package () {"gpio-port23-lpmode", "G23L"},
							Package () {"gpio-port24-lpmode", "G24L"},
							Package () {"gpio-port25-lpmode", "G25L"},
							Package () {"gpio-port26-lpmode", "G26L"},
							Package () {"gpio-port27-lpmode", "G27L"},
							Package () {"gpio-port28-lpmode", "G28L"},
							Package () {"gpio-port29-lpmode", "G29L"},
							Package () {"gpio-port30-lpmode", "G30L"},
							Package () {"gpio-port31-lpmode", "G31L"},
						}
					})

					Name (G16L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G17L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G18L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G19L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G20L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G21L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G22L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G23L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G24L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G25L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G26L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G27L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G28L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G29L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G30L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G31L, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x21,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH05", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS42)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                	     			Package () {
							Package () { "compatible", "nxp,pca9555" },
							Package () { "gpio-line-names",
								Package () {
									"PORT0_RST_L",  "PORT1_RST_L", 
						    			"PORT2_RST_L",  "PORT3_RST_L", 
									"PORT4_RST_L",  "PORT5_RST_L", 
									"PORT6_RST_L",  "PORT7_RST_L", 
						 			"PORT8_RST_L",  "PORT9_RST_L",
									"PORT10_RST_L",  "PORT11_RST_L",
									"PORT12_RST_L",  "PORT13_RST_L",
									"PORT14_RST_L",  "PORT15_RST_L"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port0-rst-l", "G00R"},
							Package () {"gpio-port1-rst-l", "G01R"},
							Package () {"gpio-port2-rst-l", "G02R"},
							Package () {"gpio-port3-rst-l", "G03R"},
							Package () {"gpio-port4-rst-l", "G04R"},
							Package () {"gpio-port5-rst-l", "G05R"},
							Package () {"gpio-port6-rst-l", "G06R"},
							Package () {"gpio-port7-rst-l", "G07R"},
							Package () {"gpio-port8-rst-l", "G08R"},
							Package () {"gpio-port9-rst-l", "G09R"},
							Package () {"gpio-port10-rst-l", "G10R"},
							Package () {"gpio-port11-rst-l", "G11R"},
							Package () {"gpio-port12-rst-l", "G12R"},
							Package () {"gpio-port13-rst-l", "G13R"},
							Package () {"gpio-port14-rst-l", "G14R"},
							Package () {"gpio-port15-rst-l", "G15R"},
						}
					})

					Name (G00R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G01R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G02R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G03R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G04R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G05R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G06R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G07R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G08R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G09R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G10R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G11R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G12R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G13R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G14R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G15R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x22,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH05", 0x00,
					     ResourceConsumer,,)
					})
				}

				Device (QS43)
				{
					Name (_HID, "PRP0001")
        				Name (_DSD, Package() {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () { "compatible", "nxp,pca9555" },
 							Package () { "gpio-line-names",
								Package () {
									"PORT16_RST_L",  "PORT17_RST_L", 
						    			"PORT18_RST_L",  "PORT19_RST_L", 
									"PORT20_RST_L",  "PORT21_RST_L", 
									"PORT22_RST_L",  "PORT23_RST_L", 
						 			"PORT24_RST_L",  "PORT25_RST_L",
									"PORT26_RST_L",  "PORT27_RST_L",
									"PORT28_RST_L",  "PORT29_RST_L",
									"PORT30_RST_L",  "PORT31_RST_L"
								}
							}
						},
						ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
						Package () {
							Package () {"gpio-port16-rst-l", "G16R"},
							Package () {"gpio-port17-rst-l", "G17R"},
							Package () {"gpio-port18-rst-l", "G18R"},
							Package () {"gpio-port19-rst-l", "G19R"},
							Package () {"gpio-port20-rst-l", "G20R"},
							Package () {"gpio-port21-rst-l", "G21R"},
							Package () {"gpio-port22-rst-l", "G22R"},
							Package () {"gpio-port23-rst-l", "G23R"},
							Package () {"gpio-port24-rst-l", "G24R"},
							Package () {"gpio-port25-rst-l", "G25R"},
							Package () {"gpio-port26-rst-l", "G26R"},
							Package () {"gpio-port27-rst-l", "G27R"},
							Package () {"gpio-port28-rst-l", "G28R"},
							Package () {"gpio-port29-rst-l", "G29R"},
							Package () {"gpio-port30-rst-l", "G30R"},
							Package () {"gpio-port31-rst-l", "G31R"},
						}
					})

					Name (G16R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 0, 0 }},
						}
					})
					
					Name (G17R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 1, 0 }},
						}
					})
					
					Name (G18R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 2, 0 }},
						}
					})
					
					Name (G19R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 3, 0 }},
						}
					})
					
					Name (G20R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 4, 0 }},
						}
					})
					
					Name (G21R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 5, 0 }},
						}
					})
					
					Name (G22R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 6, 0 }},
						}
					})
					
					Name (G23R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 7, 0 }},
						}
					})
					
					Name (G24R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 8, 0 }},
						}
					})
					
					Name (G25R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 9, 0 }},
						}
					})
					
					Name (G26R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 10, 0 }},
						}
					})
					
					Name (G27R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 11, 0 }},
						}
					})
					
					Name (G28R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 12, 0 }},
						}
					})
					
					Name (G29R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 13, 0 }},
						}
					})
					
					Name (G30R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 14, 0 }},
						}
					})
					
					Name (G31R, Package () {
						ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
						Package () {
							Package () {"gpios", Package () { 15, 0 }},
						}
					})
					
					Name (_CRS, ResourceTemplate () {
					     I2cSerialBus (0x23,
					     ControllerInitiated, 400000,
					     AddressingMode7Bit, "\\_SB.PCI0.SBUS.MUX0.CH05", 0x00,
					     ResourceConsumer,,)
					})
				}
			}
		}

		Device (GPIO)
		{
			Name (_HID, "PRP0001")
        		Name (_DSD, Package() {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () { "compatible", "nxp,pca9539" },
 					Package () { "gpio-line-names",
						Package () {
							"TH_RST_L", "TH_PCIE_RST_L", 
							"LED_CLR", "HOST_TO_BMC_I2C", 
							"UART_MUX_SEL", "USB_MUX_SEL", 
							"TH_CLK_FSEL_0", "TH_CLK_FSEL_1", 
						 	"TH_INT_L", "QSFP_GPIO0_INT_L",
							"QSFP_GPIO1_INT_L", "QSFP_GPIO2_INT_L",
							"QSFP_GPIO3_INT_L", "TH_CLK_SEL",
							"I210_RST_L", "I210_PE_RST_L"
						}
					}
				},
				ToUUID("dbb8e3e6-5886-4ba6-8795-1319f52a966b"),
				Package () {
					Package () {"gpio-host-th-rst-l", "G00H"},
					Package () {"gpio-host-th-pcie-rst-l", "G01H"},
					Package () {"gpio-host-led-clr", "G02H"},
					Package () {"gpio-host-host-to-bmc-i2c", "G03H"},
					Package () {"gpio-host-uart-mux-sel", "G04H"},
					Package () {"gpio-host-usb-mux-sel", "G05H"},
					Package () {"gpio-host-th-clk-fsel-0", "G06H"},
					Package () {"gpio-host-th-clk-fsel-1", "G07H"},
					Package () {"gpio-host-th-int-l", "G08H"},
					Package () {"gpio-host-qsfp-gpio0-int-l", "G09H"},
					Package () {"gpio-host-qsfp-gpio1-int-l", "G10H"},
					Package () {"gpio-host-qsfp-gpio2-int-l", "G11H"},
					Package () {"gpio-host-qsfp-gpio3-int-l", "G12H"},
					Package () {"gpio-host-qsfp-th-clk-sel", "G13H"},
					Package () {"gpio-host-i210-rst-l", "G14H"},
					Package () {"gpio-host-i210-pe-rst-l", "G15H"},
				}
				
        		})
			Name (G00H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 0, 0 }},
				}
			})
			
			Name (G01H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 1, 0 }},
				}
			})
			
			Name (G02H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 2, 0 }},
				}
			})
			
			Name (G03H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 3, 0 }},
				}
			})
			
			Name (G04H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 4, 0 }},
				}
			})
			
			Name (G05H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 5, 0 }},
				}
			})
			
			Name (G06H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 6, 0 }},
				}
			})
			
			Name (G07H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 7, 0 }},
				}
			})
			
			Name (G08H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 8, 0 }},
				}
			})
			
			Name (G09H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 9, 0 }},
				}
			})
			
			Name (G10H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 10, 0 }},
				}
			})
			
			Name (G11H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 11, 0 }},
				}
			})
			
			Name (G12H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 12, 0 }},
				}
			})
			
			Name (G13H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 13, 0 }},
				}
			})
			
			Name (G14H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 14, 0 }},
				}
			})
			
			Name (G15H, Package () {
				ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
				Package () {
					Package () {"gpios", Package () { 15, 0 }},
				}
			})
			
        		Name (_CRS, ResourceTemplate ()
			{
				I2cSerialBus (0x74, ControllerInitiated,
					400000, AddressingMode7Bit,
                                	"\\_SB.PCI0.SBUS", 0x00,
                                	ResourceConsumer, ,)
               		})
		}
	}
}
