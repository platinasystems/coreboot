/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 Advanced Micro Devices, Inc.
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

#include "PlatformGnbPcieComplex.h"

#include <string.h>
#include <northbridge/amd/agesa/agesawrapper.h>
#include <vendorcode/amd/agesa/f12/Proc/CPU/heapManager.h>
#include <PlatformMemoryConfiguration.h>

#define FILECODE PROC_GNB_PCIE_FAMILY_0X12_F12PCIECOMPLEXCONFIG_FILECODE

static const PCIe_PORT_DESCRIPTOR PortList [] = {
	// Initialize Port descriptor (PCIe port, Lanes 8:15, PCI Device Number 2, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 8, 15),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 2, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, BIT2)
	},
	// Initialize Port descriptor (PCIe port, Lanes 16:19, PCI Device Number 3, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 16, 19),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 3, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, BIT3)
	},
	// Initialize Port descriptor (PCIe port, Lanes 4, PCI Device Number 4, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 4, 4),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 4, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
	},
	// Initialize Port descriptor (PCIe port, Lanes 5, PCI Device Number 5, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 5, 5),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 5, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
	},
	// Initialize Port descriptor (PCIe port, Lanes 6, PCI Device Number 6, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 6, 6),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 6, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
	},
	// Initialize Port descriptor (PCIe port, Lanes 7, PCI Device Number 7, ...)
	{
		DESCRIPTOR_TERMINATE_LIST,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 7, 7),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 7, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
	}
	// Initialize Port descriptor (PCIe port, Lanes 8, PCI Device Number 8, ...)
//	{
//		DESCRIPTOR_TERMINATE_LIST,
//		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 8, 8),
//		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 8, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
//	}
};

static const PCIe_DDI_DESCRIPTOR DdiList [] = {
	// Initialize Ddi descriptor (DDI interface Lanes 24:27, DdA, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 24, 27),
		PCIE_DDI_DATA_INITIALIZER (ConnectorTypeNutmegDpToVga, Aux2, Hdp2)
	},
	// Initialize Ddi descriptor (DDI interface Lanes 28:31, DdB, ...)
	{
		DESCRIPTOR_TERMINATE_LIST,
		PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 28, 31),
		PCIE_DDI_DATA_INITIALIZER (ConnectorTypeEDP, Aux1, Hdp1)
	}
};

static const PCIe_COMPLEX_DESCRIPTOR Llano = {
	DESCRIPTOR_TERMINATE_LIST,
	0,
	&PortList[0],
	&DdiList[0]
};

/*---------------------------------------------------------------------------------------*/
/**
 *  OemCustomizeInitEarly
 *
 *  Description:
 *    This stub function will call the host environment through the binary block
 *    interface (call-out port) to provide a user hook opportunity
 *
 *  Parameters:
 *    @param[in]      *InitEarly
 *
 *    @retval         VOID
 *
 **/
/*---------------------------------------------------------------------------------------*/

static AGESA_STATUS OemInitEarly(AMD_EARLY_PARAMS * InitEarly)
{
	AGESA_STATUS         Status;
	VOID                 *LlanoPcieComplexListPtr;
	VOID                 *LlanoPciePortPtr;
	VOID                 *LlanoPcieDdiPtr;

	ALLOCATE_HEAP_PARAMS AllocHeapParams;

	// GNB PCIe topology Porting

	//
	// Allocate buffer for PCIe_COMPLEX_DESCRIPTOR , PCIe_PORT_DESCRIPTOR and PCIe_DDI_DESCRIPTOR
	//
	AllocHeapParams.RequestedBufferSize = sizeof(Llano) + sizeof(PortList) + sizeof(DdiList);

	AllocHeapParams.BufferHandle = AMD_MEM_MISC_HANDLES_START;
	AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
	Status = HeapAllocateBuffer (&AllocHeapParams, &InitEarly->StdHeader);
	ASSERT(Status == AGESA_SUCCESS);

	LlanoPcieComplexListPtr = (PCIe_COMPLEX_DESCRIPTOR *) AllocHeapParams.BufferPtr;

	AllocHeapParams.BufferPtr += sizeof(Llano);
	LlanoPciePortPtr        = (PCIe_PORT_DESCRIPTOR *)AllocHeapParams.BufferPtr;

	AllocHeapParams.BufferPtr += sizeof(PortList);
	LlanoPcieDdiPtr         = (PCIe_DDI_DESCRIPTOR *) AllocHeapParams.BufferPtr;

	LibAmdMemFill (LlanoPcieComplexListPtr,
	                 0,
	                 sizeof(Llano),
	                 &InitEarly->StdHeader);

	LibAmdMemFill (LlanoPciePortPtr,
	                 0,
	                 sizeof(PortList),
	                 &InitEarly->StdHeader);

	LibAmdMemFill (LlanoPcieDdiPtr,
	                 0,
	                 sizeof(DdiList),
	                 &InitEarly->StdHeader);

	LibAmdMemCopy (LlanoPcieComplexListPtr, &Llano, sizeof(Llano), &InitEarly->StdHeader);
	LibAmdMemCopy (LlanoPciePortPtr, &PortList[0], sizeof(PortList), &InitEarly->StdHeader);
	LibAmdMemCopy (LlanoPcieDdiPtr, &DdiList[0], sizeof(DdiList), &InitEarly->StdHeader);


	((PCIe_COMPLEX_DESCRIPTOR*)LlanoPcieComplexListPtr)->PciePortList = (PCIe_PORT_DESCRIPTOR*)LlanoPciePortPtr;
	((PCIe_COMPLEX_DESCRIPTOR*)LlanoPcieComplexListPtr)->DdiLinkList = (PCIe_DDI_DESCRIPTOR*)LlanoPcieDdiPtr;

	InitEarly->GnbConfig.PcieComplexList = LlanoPcieComplexListPtr;
	InitEarly->GnbConfig.PsppPolicy      = 0;
	return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                        CUSTOMER OVERIDES MEMORY TABLE
 *----------------------------------------------------------------------------------------
 */

/*
 *  Platform Specific Overriding Table allows IBV/OEM to pass in platform information to AGESA
 *  (e.g. MemClk routing, the number of DIMM slots per channel,...). If PlatformSpecificTable
 *  is populated, AGESA will base its settings on the data from the table. Otherwise, it will
 *  use its default conservative settings.
 */
CONST PSO_ENTRY ROMDATA DefaultPlatformMemoryConfiguration[] = {
	NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, ANY_CHANNEL, 1),
	NUMBER_OF_CHANNELS_SUPPORTED (ANY_SOCKET, 2),
	PSO_END
};

const struct OEM_HOOK OemCustomize = {
	.InitEarly = OemInitEarly,
};
