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

#include "AGESA.h"
#include <PlatformMemoryConfiguration.h>
#include "PlatformGnbPcieComplex.h"

#include <northbridge/amd/agesa/state_machine.h>

static const PCIe_PORT_DESCRIPTOR PortList[] = {
	// Initialize Port descriptor (PCIe port, Lanes 4, PCI Device Number 4, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER(PciePortEngine, 4, 7),
		PCIE_PORT_DATA_INITIALIZER(GNB_GPP_PORT4_PORT_PRESENT, GNB_GPP_PORT4_CHANNEL_TYPE, 4, GNB_GPP_PORT4_HOTPLUG_SUPPORT, GNB_GPP_PORT4_SPEED_MODE, GNB_GPP_PORT4_SPEED_MODE, GNB_GPP_PORT4_LINK_ASPM, 0)
	},
	// Initialize Port descriptor (PCIe port, Lanes 8, PCI Device Number 8, ...)
	{
		DESCRIPTOR_TERMINATE_LIST,
		PCIE_ENGINE_DATA_INITIALIZER(PciePortEngine, 0, 3),
		PCIE_PORT_DATA_INITIALIZER(GNB_GPP_PORT8_PORT_PRESENT, GNB_GPP_PORT8_CHANNEL_TYPE, 8, GNB_GPP_PORT8_HOTPLUG_SUPPORT, GNB_GPP_PORT8_SPEED_MODE, GNB_GPP_PORT8_SPEED_MODE, GNB_GPP_PORT8_LINK_ASPM, 0)
	}
};

static const PCIe_DDI_DESCRIPTOR DdiList[] = {
	// Initialize Ddi descriptor (DDI interface Lanes 8:11, DdA, ...)
	{
		0,
		PCIE_ENGINE_DATA_INITIALIZER(PcieDdiEngine, 8, 11),
		//PCIE_DDI_DATA_INITIALIZER(ConnectorTypeDP, Aux1, Hdp1)
		{ConnectorTypeDP, Aux1, Hdp1}
	},
	// Initialize Ddi descriptor (DDI interface Lanes 12:15, DdB, ...)
	{
		DESCRIPTOR_TERMINATE_LIST,
		PCIE_ENGINE_DATA_INITIALIZER(PcieDdiEngine, 12, 15),
		//PCIE_DDI_DATA_INITIALIZER(ConnectorTypeDP, Aux2, Hdp2)
		{ConnectorTypeDP, Aux2, Hdp2}
	}
};

static const PCIe_COMPLEX_DESCRIPTOR PcieComplex = {
	.Flags        = DESCRIPTOR_TERMINATE_LIST,
	.SocketId     = 0,
	.PciePortList = PortList,
	.DdiLinkList  = DdiList,
};

void board_BeforeInitEarly(struct sysinfo *cb, AMD_EARLY_PARAMS *InitEarly)
{
	InitEarly->GnbConfig.PcieComplexList = &PcieComplex;
	InitEarly->GnbConfig.PsppPolicy		= 0;
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
static CONST PSO_ENTRY ROMDATA PlatformMemoryTable[] = {
  NUMBER_OF_DIMMS_SUPPORTED(ANY_SOCKET, ANY_CHANNEL, 2),
  NUMBER_OF_CHANNELS_SUPPORTED(ANY_SOCKET, 1),
  PSO_END
};

void board_BeforeInitPost(struct sysinfo *cb, AMD_POST_PARAMS *InitPost)
{
	InitPost->MemConfig.PlatformMemoryConfiguration = (PSO_ENTRY *)PlatformMemoryTable;
}
