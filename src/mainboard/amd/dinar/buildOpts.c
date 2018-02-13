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

/**
 * @file
 *
 * AMD User options selection for a Sabine/Lynx platform solution system
 *
 * This file is placed in the user's platform directory and contains the
 * build option selections desired for that platform.
 *
 */
#include <stdlib.h>
#include "AGESA.h"
//#define OPTION_HW_DQS_REC_EN_TRAINING TRUE
/* AGESA will check the OEM configuration during preprocessing stage,
 * coreboot enable -Wundef option, so we should make sure we have all contanstand defined
 */
/* MEMORY_BUS_SPEED */
#define DDR400_FREQUENCY		200	///< DDR 400
#define DDR533_FREQUENCY		266	///< DDR 533
#define DDR667_FREQUENCY		333	///< DDR 667
#define DDR800_FREQUENCY		400	///< DDR 800
#define DDR1066_FREQUENCY		533	///< DDR 1066
#define DDR1333_FREQUENCY		667	///< DDR 1333
#define DDR1600_FREQUENCY		800	///< DDR 1600
#define DDR1866_FREQUENCY		933	///< DDR 1866
#define UNSUPPORTED_DDR_FREQUENCY	934	///< Highest limit of DDR frequency

/* QUANDRANK_TYPE */
#define QUADRANK_REGISTERED		0	///< Quadrank registered DIMM
#define QUADRANK_UNBUFFERED		1	///< Quadrank unbuffered DIMM

/* USER_MEMORY_TIMING_MODE */
#define TIMING_MODE_AUTO		0	///< Use best rate possible
#define TIMING_MODE_LIMITED		1	///< Set user top limit
#define TIMING_MODE_SPECIFIC		2	///< Set user specified speed

/* POWER_DOWN_MODE */
#define POWER_DOWN_BY_CHANNEL		0	///< Channel power down mode
#define POWER_DOWN_BY_CHIP_SELECT	1	///< Chip select power down mode

/*  Select the CPU family.  */


/*  Select the CPU socket type.  */
#define INSTALL_G34_SOCKET_SUPPORT  TRUE
#define INSTALL_C32_SOCKET_SUPPORT  FALSE
#define INSTALL_S1G3_SOCKET_SUPPORT FALSE
#define INSTALL_S1G4_SOCKET_SUPPORT FALSE
#define INSTALL_ASB2_SOCKET_SUPPORT FALSE
#define INSTALL_FS1_SOCKET_SUPPORT  FALSE
#define INSTALL_FM1_SOCKET_SUPPORT  FALSE
#define INSTALL_FP1_SOCKET_SUPPORT  FALSE
#define INSTALL_FT1_SOCKET_SUPPORT  FALSE
#define INSTALL_AM3_SOCKET_SUPPORT  FALSE

/*
 * Agesa optional capabilities selection.
 * Uncomment and mark FALSE those features you wish to include in the build.
 * Comment out or mark TRUE those features you want to REMOVE from the build.
 */

/* User makes option selections here
 * Comment out the items wanted to be included in the build.
 * Uncomment those items you with to REMOVE from the build.
 */
//#define BLDOPT_REMOVE_UDIMMS_SUPPORT           TRUE
//#define BLDOPT_REMOVE_RDIMMS_SUPPORT           TRUE
//#define BLDOPT_REMOVE_ECC_SUPPORT              TRUE
//#define BLDOPT_REMOVE_BANK_INTERLEAVE          TRUE
//#define BLDOPT_REMOVE_DCT_INTERLEAVE           TRUE
//#define BLDOPT_REMOVE_NODE_INTERLEAVE          TRUE
#define BLDOPT_REMOVE_PARALLEL_TRAINING        TRUE
//#define BLDOPT_REMOVE_ONLINE_SPARE_SUPPORT     TRUE
//#define BLDOPT_REMOVE_DDR3_SUPPORT             TRUE
//#define BLDOPT_REMOVE_MULTISOCKET_SUPPORT      TRUE
//#define BLDOPT_REMOVE_ACPI_PSTATES             TRUE
//#define BLDOPT_REMOVE_SRAT                     TRUE
//#define BLDOPT_REMOVE_SLIT                     TRUE
#define BLDOPT_REMOVE_WHEA                     TRUE
//#define BLDOPT_REMOVE_DMI                      TRUE
#define BLDOPT_REMOVE_EARLY_SAMPLES            FALSE
//#define BLDOPT_REMOVE_FAMILY_15_SUPPORT          TRUE
/* Build configuration values here.
*/
#define BLDCFG_VRM_CURRENT_LIMIT                 120000
#define BLDCFG_VRM_LOW_POWER_THRESHOLD           0
#define BLDCFG_PLAT_NUM_IO_APICS                 2
#define BLDCFG_CORE_LEVELING_MODE                CORE_LEVEL_LOWEST
#define BLDCFG_MEM_INIT_PSTATE                   0
#define BLDCFG_AMD_PSTATE_CAP_VALUE              0

#define BLDCFG_AMD_PLATFORM_TYPE                  AMD_PLATFORM_SERVER

#define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR1600_FREQUENCY
#define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           TRUE
#define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_REGISTERED
#define BLDCFG_MEMORY_RDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE              FALSE
#define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    TRUE
#define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    TRUE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        TRUE
#define BLDCFG_MEMORY_POWER_DOWN                  TRUE
#define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHIP_SELECT  //FALSE
#define BLDCFG_ONLINE_SPARE                       TRUE
#define BLDCFG_MEMORY_PARITY_ENABLE               TRUE
#define BLDCFG_BANK_SWIZZLE                       TRUE
#define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#define BLDCFG_MEMORY_CLOCK_SELECT                DDR800_FREQUENCY
#define BLDCFG_DQS_TRAINING_CONTROL               TRUE
#define BLDCFG_IGNORE_SPD_CHECKSUM                FALSE
#define BLDCFG_USE_BURST_MODE                     FALSE
#define BLDCFG_MEMORY_ALL_CLOCKS_ON               TRUE
#define BLDCFG_ENABLE_ECC_FEATURE                 TRUE
#define BLDCFG_ECC_REDIRECTION                    TRUE
#define BLDCFG_SCRUB_IC_RATE                      0
#define BLDCFG_ECC_SYNC_FLOOD                     TRUE
#define BLDCFG_ECC_SYMBOL_SIZE                    0
#define BLDCFG_1GB_ALIGN                          FALSE
#define BLDCFG_PLATFORM_C1E_MODE                  C1eModeMsgBased
#define BLDCFG_PLATFORM_C1E_OPDATA                0x2000
//#define BLDCFG_USE_ATM_MODE                       TRUE

#define BLDCFG_PLATFORM_CSTATE_MODE               CStateModeC6
#define BLDCFG_PLATFORM_CSTATE_IO_BASE_ADDRESS    0xCB0
#define BLDCFG_PLATFORM_POWER_POLICY_MODE	  Performance  //BatteryLife
//#define BLDCFG_PLATFORM_CSTATE_MODE                  CStateModeMsgBasedC1e
//#define BLDCFG_PLATFORM_CSTATE_OPDATA                0x2000

//#define IDSOPT_IDS_ENABLED                        TRUE
#define BLDCFG_REMOVE_ACPI_PSTATES_PPC               TRUE
#define BLDOPT_REMOVE_LOW_PWR_PSTATE_FOR_PROCHOT	TRUE
#define BLDCFG_PSTATE_HPC_MODE                    FALSE

#define BLDCFG_HTDEVICE_CAPABILITIES_OVERRIDE_LIST &MaranelloOverrideDevCap
/*  Process the options...
 * This file include MUST occur AFTER the user option selection settings
 */


/*****************************************************************************
 *   Define the RELEASE VERSION string
 *
 * The Release Version string should identify the next planned release.
 * When a branch is made in preparation for a release, the release manager
 * should change/confirm that the branch version of this file contains the
 * string matching the desired version for the release. The trunk version of
 * the file should always contain a trailing 'X'. This will make sure that a
 * development build from trunk will not be confused for a released version.
 * The release manager will need to remove the trailing 'X' and update the
 * version string as appropriate for the release. The trunk copy of this file
 * should also be updated/incremented for the next expected version, + trailing 'X'
 ****************************************************************************/
// This is the delivery package title, "MarG34PI"
// This string MUST be exactly 8 characters long
#define AGESA_PACKAGE_STRING  {'O', 'r', 'o', 'c', 'h', 'i', 'P', 'I'}

// This is the release version number of the AGESA component
// This string MUST be exactly 12 characters long
#define AGESA_VERSION_STRING  {'V', '0', '.', '0', '.', '9', '.', '0', ' ', ' ', ' ', ' '}

// The Maranello solution is defined to be families 0x10 and 0x15 models 0x0 - 0xF in the G34 socket.
#define INSTALL_G34_SOCKET_SUPPORT           TRUE
#define INSTALL_FAMILY_10_SUPPORT            TRUE
#define INSTALL_FAMILY_15_MODEL_0x_SUPPORT   TRUE

#ifdef BLDOPT_REMOVE_FAMILY_10_SUPPORT
#if BLDOPT_REMOVE_FAMILY_10_SUPPORT == TRUE
#undef INSTALL_FAMILY_10_SUPPORT
#define INSTALL_FAMILY_10_SUPPORT     FALSE
#endif
#endif

#ifdef BLDOPT_REMOVE_FAMILY_15_SUPPORT
#if BLDOPT_REMOVE_FAMILY_15_SUPPORT == TRUE
#undef INSTALL_FAMILY_15_MODEL_0x_SUPPORT
#define INSTALL_FAMILY_15_MODEL_0x_SUPPORT     FALSE
#endif
#endif

// The following definitions specify the default values for various parameters in which there are
// no clearly defined defaults to be used in the common file.  The values below are based on product
// and BKDG content, please consult the AGESA Memory team for consultation.
#define DFLT_SCRUB_DRAM_RATE            (0xFF)
#define DFLT_SCRUB_L2_RATE              (0x10)
#define DFLT_SCRUB_L3_RATE              (0x10)
#define DFLT_SCRUB_IC_RATE              (0)
#define DFLT_SCRUB_DC_RATE              (0x12)
#define DFLT_MEMORY_QUADRANK_TYPE       QUADRANK_REGISTERED
#define DFLT_VRM_SLEW_RATE              (2500)

/*  Process the options...
 * This file include MUST occur
 AFTER the user option selection settings
 */
CONST MANUAL_BUID_SWAP_LIST ROMDATA MaranelloManualBuidSwapList[2] =
{
	{
		/* On the reference platform, there is only one nc chain, so socket & link are 'don't care' */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		{ //BUID Swap List
			{ //BUID Swaps
				/* Each Non-coherent chain may have a list of device swaps,
				 * Each item specify a device will be swap from its current id to a new one
				 */
				/* FromID 0x00 is the chain with the southbridge */
				/* 'Move' device zero to device zero, All others are non applicable */
				{0x00, 0x00}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
				{0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF}, {0xFF, 0xFF},
			},

			{ //The ordered final BUIDs
				/* Specify the final BUID to be zero, All others are non applicable */
				0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
				0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			}
		}
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};

#define BLDCFG_BUID_SWAP_LIST &MaranelloManualBuidSwapList

// And another platform specific one ...
//CONST CPU_TO_CPU_PCB_LIMITS ROMDATA MaranelloCpuToCpuLimitList[2] =
//{
//  HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,
//  HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_3200M,
//  HT_LIST_TERMINAL
//};

CONST CPU_TO_CPU_PCB_LIMITS ROMDATA MaranelloCpuToCpuLimitList[] =
{
	{
		/* On the reference platform, these settings apply to all coherent links */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set incoming and outgoing links to 16 bit widths, and 3.2GHz frequencies */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_2600M,
	},

	{
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_INTERNAL_LINK, HT_LIST_MATCH_ANY, HT_LIST_MATCH_INTERNAL_LINK,
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_2600M,
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};

#define BLDCFG_HTFABRIC_LIMITS_LIST &MaranelloCpuToCpuLimitList

// A performance-per-watt optimization.
CONST SKIP_REGANG ROMDATA PerfPerWatt[] = {
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, POWERED_OFF },
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_INTERNAL_LINK, HT_LIST_MATCH_ANY, HT_LIST_MATCH_INTERNAL_LINK, POWERED_OFF },
	{ HT_LIST_TERMINAL }
};

// uncomment the line below to make Perf-per-watt enabled by default.
#define BLDCFG_LINK_SKIP_REGANG_LIST &PerfPerWatt


CONST IO_PCB_LIMITS ROMDATA MaranelloIoLimitList[2] =
{
	{
		/* On the reference platform, there is only one nc chain, so socket & link are 'don't care' */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set upstream and downstream links to 16 bit widths, and limit frequencies to 3.2GHz */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_2600M, //Actually IO hub only support 2600M MAX
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};

#define BLDCFG_HTCHAIN_LIMITS_LIST &MaranelloIoLimitList

CONST SYSTEM_PHYSICAL_SOCKET_MAP ROMDATA DinarPhysicalSocketMap[] =
{
	// Source Socket, Link (4-7 are sublink 1), Target Socket
	{0, 0, 1},
	{0, 1, 1},
	{0, 3, 1},
	{0, 4, 1},
	{0, 5, 1},
	{0, 7, 1},
};

#define BLDCFG_SYSTEM_PHYSICAL_SOCKET_MAP &DinarPhysicalSocketMap

/*
 *  PCI Bus numbers for Drachma/Peso board
 */
CONST OVERRIDE_BUS_NUMBERS ROMDATA MaranelloOverrideBusNumbers[5] =
{
	// Socket, Link, SecBus, SubBus
	{ 0, 2, 0x00, 0xBF },		// RD890 of Dinar
	{ 1, 0, 0xC0, 0xFF },		// HTX
	{ (HT_LIST_TERMINAL) }
};

#define BLDCFG_BUS_NUMBERS_LIST &MaranelloOverrideBusNumbers

CONST CPU_HT_DEEMPHASIS_LEVEL ROMDATA DinarDeemphasisList[] =
{
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_200M, HT_FREQUENCY_1800M, DeemphasisLevelNone, DcvLevelNone},
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2000M, HT_FREQUENCY_2600M, DeemphasisLevelMinus3, DcvLevelMinus3},
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2800M, HT_FREQUENCY_MAX, DeemphasisLevelMinus6, DcvLevelMinus6},
	{ (0xFF) }
};

#define BLDCFG_PLATFORM_DEEMPHASIS_LIST DinarDeemphasisList
/*
   CONST SKIP_REGANG ROMDATA DinarSkipRegangMap[] =
   {
// {socketA, linkA, socketB, linkB}
{0, 0, 1, 1},
};

#define BLDCFG_LINK_SKIP_REGANG_LIST &DinarSkipRegangMap
*/

/*
 *  Device Capabilities Override for disabling ID Clumping
 */
CONST DEVICE_CAP_OVERRIDE ROMDATA MaranelloOverrideDevCap[2] =
{
	{ HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,
	0, 0, HT_LIST_MATCH_ANY, {0, 0, 0, 0, 0, 1, 0}, 0, 0, 0, 0, 0 },
	{ (HT_LIST_TERMINAL) }
};

#define BLDCFG_HTDEVICE_CAPABILITIES_OVERRIDE_LIST &MaranelloOverrideDevCap


#include "cpuRegisters.h"
#include "cpuFamRegisters.h"
#include "cpuFamilyTranslation.h"
#include "AdvancedApi.h"
#include "heapManager.h"
#include "CreateStruct.h"
#include "cpuFeatures.h"
#include "Table.h"
#include "cpuEarlyInit.h"
#include "cpuLateInit.h"
#include "GnbInterfaceStub.h"
#include <PlatformInstall.h>
