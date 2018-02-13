/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
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

#include "Porting.h"
#include "AGESA.h"
#include "amdlib.h"

#include <northbridge/amd/agesa/agesawrapper.h>
#include <vendorcode/amd/agesa/f15tn/Proc/CPU/heapManager.h>
#include <PlatformMemoryConfiguration.h>

#define FILECODE PROC_GNB_PCIE_FAMILY_0X15_F15PCIECOMPLEXCONFIG_FILECODE

/*
 * Lane ID Mapping (from Fam15h BKDG: Table 45: Lane Id Mapping)
 *
 * Lane Id
 * 0 P_UMI_[T,R]X[P,N]0 - southbridge link, connect via dev 8
 * 1 P_UMI_[T,R]X[P,N]1 - southbridge link, connect via dev 8
 * 2 P_UMI_[T,R]X[P,N]2 - southbridge link, connect via dev 8
 * 3 P_UMI_[T,R]X[P,N]3 - southbridge link, connect via dev 8
 * 4 P_GPP_[T,R]X[P,N]0 - may connect to PCI dev 4 - 7
 * 5 P_GPP_[T,R]X[P,N]1 - may connect to PCI dev 4 - 7
 * 6 P_GPP_[T,R]X[P,N]2 - may connect to PCI dev 4 - 7
 * 7 P_GPP_[T,R]X[P,N]3 - may connect to PCI dev 4 - 7
 * 8 P_GFX_[T,R]X[P,N]0 - may be used to form GFX slot or DDI
 * 9 P_GFX_[T,R]X[P,N]1 - may be used to form GFX slot or DDI
 * 10 P_GFX_[T,R]X[P,N]2 - may be used to form GFX slot or DDI
 * 11 P_GFX_[T,R]X[P,N]3 - may be used to form GFX slot or DDI
 * 12 P_GFX_[T,R]X[P,N]4 - may be used to form GFX slot or DDI
 * 13 P_GFX_[T,R]X[P,N]5 - may be used to form GFX slot or DDI
 * 14 P_GFX_[T,R]X[P,N]6 - may be used to form GFX slot or DDI
 * 15 P_GFX_[T,R]X[P,N]7 - may be used to form GFX slot or DDI
 * 16 P_GFX_[T,R]X[P,N]8 - may be used to form GFX slot or DDI
 * 17 P_GFX_[T,R]X[P,N]9 - may be used to form GFX slot or DDI
 * 18 P_GFX_[T,R]X[P,N]10 - may be used to form GFX slot or DDI
 * 19 P_GFX_[T,R]X[P,N]11 - may be used to form GFX slot or DDI
 * 20 P_GFX_[T,R]X[P,N]12 - may be used to form GFX slot or DDI
 * 21 P_GFX_[T,R]X[P,N]13 - may be used to form GFX slot or DDI
 * 22 P_GFX_[T,R]X[P,N]14 - may be used to form GFX slot or DDI
 * 23 P_GFX_[T,R]X[P,N]15 - may be used to form GFX slot or DDI
 * 24 DP0_TX[P,N]0 - rest is just for DDI (graphics outputs)
 * 25 DP0_TX[P,N]1
 * 26 DP0_TX[P,N]2
 * 27 DP0_TX[P,N]3
 * 28 DP1_TX[P,N]0
 * 29 DP1_TX[P,N]1
 * 30 DP1_TX[P,N]2
 * 31 DP1_TX[P,N]3
 * 32 DP2_TX[P,N]0
 * 33 DP2_TX[P,N]1
 * 34 DP2_TX[P,N]2
 * 35 DP2_TX[P,N]3
 * 36 DP2_TX[P,N]4
 * 37 DP2_TX[P,N]5
 * 38 DP2_TX[P,N]6
 */

static const PCIe_PORT_DESCRIPTOR PortList [] = {
	/* PCIe port, Lanes 8:23, PCI Device Number 2, blue x16 slot */
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 8, 23),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 2, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 1)
	},
	/* PCIe port, Lanes 4:7, PCI Device Number 4, black x16 slot (in fact x4) */
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 4, 7),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 4, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 1)
	},
	/* PCIe port, Lanes 0:3, UMI link to SB, PCI Device Number 8 */
	{
		DESCRIPTOR_TERMINATE_LIST,
		PCIE_ENGINE_DATA_INITIALIZER (PciePortEngine, 0, 3),
		PCIE_PORT_DATA_INITIALIZER (PortEnabled, ChannelTypeExt6db, 8, HotplugDisabled, PcieGenMaxSupported, PcieGenMaxSupported, AspmDisabled, 0)
	},
};

/*
 * It is not known, if the setup is complete.
 *
 * Tested and works: VGA/DVI
 * Untested: HDMI
 */
static const PCIe_DDI_DESCRIPTOR DdiList [] = {
	// DP0 to HDMI0/DP
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 24, 27),
		PCIE_DDI_DATA_INITIALIZER (ConnectorTypeHDMI, Aux1, Hdp1)
	},
	// DP1 to FCH
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 28, 31),
		PCIE_DDI_DATA_INITIALIZER (ConnectorTypeNutmegDpToVga, Aux2, Hdp2)
	},
	// DP2 to HDMI1/DP
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER (PcieDdiEngine, 32, 35),
		PCIE_DDI_DATA_INITIALIZER (ConnectorTypeHDMI, Aux3, Hdp3)
	},
};

static const PCIe_COMPLEX_DESCRIPTOR Trinity = {
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
	VOID                 *TrinityPcieComplexListPtr;
	VOID                 *TrinityPciePortPtr;
	VOID                 *TrinityPcieDdiPtr;

	ALLOCATE_HEAP_PARAMS AllocHeapParams;

	// GNB PCIe topology Porting

	//
	// Allocate buffer for PCIe_COMPLEX_DESCRIPTOR , PCIe_PORT_DESCRIPTOR and PCIe_DDI_DESCRIPTOR
	//
	AllocHeapParams.RequestedBufferSize = sizeof(Trinity) + sizeof(PortList) + sizeof(DdiList);
	AllocHeapParams.BufferHandle = AMD_MEM_MISC_HANDLES_START;
	AllocHeapParams.Persist = HEAP_LOCAL_CACHE;
	Status = HeapAllocateBuffer (&AllocHeapParams, &InitEarly->StdHeader);
	ASSERT(Status == AGESA_SUCCESS);

	TrinityPcieComplexListPtr  =  (PCIe_COMPLEX_DESCRIPTOR *) AllocHeapParams.BufferPtr;

	AllocHeapParams.BufferPtr += sizeof(Trinity);
	TrinityPciePortPtr         =  (PCIe_PORT_DESCRIPTOR *)AllocHeapParams.BufferPtr;

	AllocHeapParams.BufferPtr += sizeof(PortList);
	TrinityPcieDdiPtr          =  (PCIe_DDI_DESCRIPTOR *) AllocHeapParams.BufferPtr;

	LibAmdMemFill (TrinityPcieComplexListPtr,
		       0,
		       sizeof(Trinity),
		       &InitEarly->StdHeader);

	LibAmdMemFill (TrinityPciePortPtr,
		       0,
		       sizeof(PortList),
		       &InitEarly->StdHeader);

	LibAmdMemFill (TrinityPcieDdiPtr,
		       0,
		       sizeof(DdiList),
		       &InitEarly->StdHeader);

	LibAmdMemCopy  (TrinityPcieComplexListPtr, &Trinity, sizeof(Trinity), &InitEarly->StdHeader);
	LibAmdMemCopy  (TrinityPciePortPtr, &PortList[0], sizeof(PortList), &InitEarly->StdHeader);
	LibAmdMemCopy  (TrinityPcieDdiPtr, &DdiList[0], sizeof(DdiList), &InitEarly->StdHeader);

	((PCIe_COMPLEX_DESCRIPTOR*)TrinityPcieComplexListPtr)->PciePortList =  (PCIe_PORT_DESCRIPTOR*)TrinityPciePortPtr;
	((PCIe_COMPLEX_DESCRIPTOR*)TrinityPcieComplexListPtr)->DdiLinkList  =  (PCIe_DDI_DESCRIPTOR*)TrinityPcieDdiPtr;

	InitEarly->GnbConfig.PcieComplexList = TrinityPcieComplexListPtr;
	return AGESA_SUCCESS;
}

static AGESA_STATUS OemInitMid(AMD_MID_PARAMS * InitMid)
{
	/* 0 iGpuVgaAdapter, 1 iGpuVgaNonAdapter; */
	InitMid->GnbMidConfiguration.iGpuVgaMode = 0;
	return AGESA_SUCCESS;
}

/*----------------------------------------------------------------------------------------
 *                        CUSTOMER OVERIDES MEMORY TABLE
 *----------------------------------------------------------------------------------------
 */

#if IS_ENABLED(CONFIG_BOARD_ASUS_F2A85_M) || IS_ENABLED(CONFIG_BOARD_ASUS_F2A85_M_PRO)
/*
 *  Platform Specific Overriding Table allows IBV/OEM to pass in platform information to AGESA
 *  (e.g. MemClk routing, the number of DIMM slots per channel,...). If PlatformSpecificTable
 *  is populated, AGESA will base its settings on the data from the table. Otherwise, it will
 *  use its default conservative settings.
 */
CONST PSO_ENTRY ROMDATA DefaultPlatformMemoryConfiguration[] = {

  NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, ANY_CHANNEL, 2),
  NUMBER_OF_CHANNELS_SUPPORTED (ANY_SOCKET, 2),
/*
  TODO: is this OK for DDR3 socket FM2?
  MEMCLK_DIS_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
  CKE_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x05, 0x0A),
  ODT_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00),
  CS_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
  */
  PSO_END
};
#elif IS_ENABLED(CONFIG_BOARD_ASUS_F2A85_M_LE)
/*
 *  Platform Specific Overriding Table allows IBV/OEM to pass in platform information to AGESA
 *  (e.g. MemClk routing, the number of DIMM slots per channel,...). If PlatformSpecificTable
 *  is populated, AGESA will base its settings on the data from the table. Otherwise, it will
 *  use its default conservative settings.
 */
CONST PSO_ENTRY ROMDATA DefaultPlatformMemoryConfiguration[] = {

  NUMBER_OF_DIMMS_SUPPORTED (ANY_SOCKET, ANY_CHANNEL, 1),
  NUMBER_OF_CHANNELS_SUPPORTED (ANY_SOCKET, 2),
/*
  TODO: is this OK for DDR3 socket FM2?
  MEMCLK_DIS_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
  CKE_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x05, 0x0A),
  ODT_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00),
  CS_TRI_MAP (ANY_SOCKET, ANY_CHANNEL, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
  */
  PSO_END
};
#endif /* CONFIG_BOARD_ASUS_F2A85_M */

const struct OEM_HOOK OemCustomize = {
	.InitEarly = OemInitEarly,
	.InitMid = OemInitMid,
};
