/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 - 2012 Advanced Micro Devices, Inc.
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

#include <stdlib.h>

#include "AGESA.h"
#include "AdvancedApi.h"
#include "Filecode.h"
#define FILECODE PLATFORM_SPECIFIC_OPTIONS_FILECODE

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

/* QUANDRANK_TYPE*/
#define QUADRANK_REGISTERED		0	///< Quadrank registered DIMM
#define QUADRANK_UNBUFFERED		1	///< Quadrank unbuffered DIMM

/* USER_MEMORY_TIMING_MODE */
#define TIMING_MODE_AUTO		0	///< Use best rate possible
#define TIMING_MODE_LIMITED		1	///< Set user top limit
#define TIMING_MODE_SPECIFIC		2	///< Set user specified speed

/* POWER_DOWN_MODE */
#define POWER_DOWN_BY_CHANNEL		0	///< Channel power down mode
#define POWER_DOWN_BY_CHIP_SELECT	1	///< Chip select power down mode

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
//#define BLDOPT_REMOVE_PARALLEL_TRAINING        TRUE
//#define BLDOPT_REMOVE_ONLINE_SPARE_SUPPORT     TRUE
#define BLDOPT_REMOVE_MEM_RESTORE_SUPPORT      TRUE
//#define BLDOPT_REMOVE_MULTISOCKET_SUPPORT      TRUE
////#define BLDOPT_REMOVE_ACPI_PSTATES             TRUE
////#define BLDOPT_REMOVE_SRAT                     TRUE
////#define BLDOPT_REMOVE_SLIT                     TRUE
//#define BLDOPT_REMOVE_WHEA                     TRUE
//#define BLDOPT_REMOVE_DMI                      TRUE

/*f15 Rev A1 ucode patch CpuF15OrMicrocodePatch0600011F */
#define BLDOPT_REMOVE_EARLY_SAMPLES		FALSE

//#define BLDOPT_REMOVE_HT_ASSIST                TRUE
//#define BLDOPT_REMOVE_MSG_BASED_C1E            TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PPC               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PCT               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSD               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_PSS               TRUE
//#define BLDCFG_REMOVE_ACPI_PSTATES_XPSS              TRUE

/* Build configuration values here.
 */
#define BLDCFG_VRM_CURRENT_LIMIT                 120000
#define BLDCFG_VRM_LOW_POWER_THRESHOLD           0
#define BLDCFG_VRM_INRUSH_CURRENT_LIMIT          0
#define BLDCFG_PLAT_NUM_IO_APICS                 3
#define BLDCFG_CORE_LEVELING_MODE                CORE_LEVEL_LOWEST
#define BLDCFG_MEM_INIT_PSTATE                   0
#define BLDCFG_AMD_PSTATE_CAP_VALUE              0

#define BLDCFG_AMD_PLATFORM_TYPE                  AMD_PLATFORM_SERVER

#define BLDCFG_MEMORY_BUS_FREQUENCY_LIMIT         DDR1333_FREQUENCY//1600
#define BLDCFG_MEMORY_MODE_UNGANGED               TRUE
#define BLDCFG_MEMORY_QUAD_RANK_CAPABLE           TRUE
#define BLDCFG_MEMORY_QUADRANK_TYPE               QUADRANK_REGISTERED
#define BLDCFG_MEMORY_RDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_UDIMM_CAPABLE               TRUE
#define BLDCFG_MEMORY_SODIMM_CAPABLE              FALSE
#define BLDCFG_LIMIT_MEMORY_TO_BELOW_1TB          TRUE
#define BLDCFG_MEMORY_ENABLE_BANK_INTERLEAVING    FALSE//TRUE
#define BLDCFG_MEMORY_ENABLE_NODE_INTERLEAVING    FALSE//TRUE
#define BLDCFG_MEMORY_CHANNEL_INTERLEAVING        FALSE//TRUE
#define BLDCFG_MEMORY_POWER_DOWN                  FALSE
#define BLDCFG_POWER_DOWN_MODE                    POWER_DOWN_BY_CHANNEL
#define BLDCFG_ONLINE_SPARE                       FALSE
#define BLDCFG_BANK_SWIZZLE                       TRUE
#define BLDCFG_TIMING_MODE_SELECT                 TIMING_MODE_AUTO
#define BLDCFG_MEMORY_CLOCK_SELECT                DDR1333_FREQUENCY //DDR800_FREQUENCY
#define BLDCFG_DQS_TRAINING_CONTROL               TRUE
#define BLDCFG_IGNORE_SPD_CHECKSUM                FALSE
#define BLDCFG_USE_BURST_MODE                     FALSE
#define BLDCFG_MEMORY_ALL_CLOCKS_ON               FALSE
#define BLDCFG_ENABLE_ECC_FEATURE                 TRUE
#define BLDCFG_ECC_REDIRECTION                    FALSE
#define BLDCFG_SCRUB_IC_RATE                      0
#define BLDCFG_ECC_SYNC_FLOOD                     TRUE
#define BLDCFG_ECC_SYMBOL_SIZE                    4

#define BLDCFG_PCI_MMIO_BASE                    CONFIG_MMCONF_BASE_ADDRESS
#define BLDCFG_PCI_MMIO_SIZE                    CONFIG_MMCONF_BUS_NUMBER

/**
 * Enable Message Based C1e CPU feature in multi-socket systems.
 * BLDCFG_PLATFORM_C1E_OPDATA element be defined with a valid IO port value,
 * else the feature cannot be enabled.
 */
#define BLDCFG_PLATFORM_C1E_MODE                  C1eModeMsgBased
#define BLDCFG_PLATFORM_C1E_OPDATA                0x80//TODO
//#define BLDCFG_PLATFORM_C1E_MODE_OPDATA1        0
//#define BLDCFG_PLATFORM_C1E_MODE_OPDATA2        0

#define BLDCFG_HEAP_DRAM_ADDRESS                  0xB0000
#define BLDCFG_CFG_TEMP_PCIE_MMIO_BASE_ADDRESS    0xD0000000
#define BLDCFG_1GB_ALIGN                          FALSE
//#define BLDCFG_PROCESSOR_SCOPE_NAME0              'C'
//#define BLDCFG_PROCESSOR_SCOPE_NAME1              '0'
//

// Select the platform control flow mode for performance tuning.
#define BLDCFG_PLATFORM_CONTROL_FLOW_MODE Nfcm

/**
 * Enable the probe filtering performance tuning feature.
 * The probe filter provides filtering of broadcast probes to
 * improve link bandwidth and performance for multi- node systems.
 *
 * This feature may interact with other performance features.
 *  TRUE  -Enable the feature (default) if supported by all processors,
 *         based on revision and presence of L3 cache.
 *         The feature is not enabled if there are no coherent HT links.
 *  FALSE -Do not enable the feature regardless of the configuration.
 */
//TODO enable it,
//but AGESA set PFMode = 0; //PF Disable, HW never set PFInitDone
//hang in F10HtAssistInit() do{...} while(PFInitDone != 1)
#define BLDCFG_USE_HT_ASSIST	FALSE

/**
 * The socket and link match values are platform specific
 */
CONST MANUAL_BUID_SWAP_LIST ROMDATA s8226_manual_swaplist[2] =
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

#define HYPERTRANSPORT_V31_SUPPORT 1

#if HYPERTRANSPORT_V31_SUPPORT
/**
 * The socket and link match values are platform specific
 *
 */
CONST CPU_TO_CPU_PCB_LIMITS ROMDATA s8226_cpu2cpu_limit_list[2] =
{
	{
		/* On the reference platform, these settings apply to all coherent links */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set incoming and outgoing links to 16 bit widths, and 3.2GHz frequencies */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_3200M,
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};

CONST IO_PCB_LIMITS ROMDATA s8226_io_limit_list[2] =
{
	{
		/* On the reference platform, there is only one nc chain, so socket & link are 'don't care' */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set upstream and downstream links to 16 bit widths, and limit frequencies to 3.2GHz */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_3200M, //Actually IO hub only support 2600M MAX
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};
#else /* HYPERTRANSPORT_V31_SUPPORT == 0 */
CONST CPU_TO_CPU_PCB_LIMITS ROMDATA s8226_cpu2cpu_limit_list[2] =
{
	{
		/* On the reference platform, these settings apply to all coherent links */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set incoming and outgoing links to 16 bit widths, and 1GHz frequencies */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_HT1_ONLY,
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL,
	}
};

CONST IO_PCB_LIMITS ROMDATA s8226_io_limit_list[2] =
{
	{
		/* On the reference platform, there is only one nc chain, so socket & link are 'don't care' */
		HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY,

		/* Set incoming and outgoing links to 16 bit widths, and 1GHz frequencies */
		HT_WIDTH_16_BITS, HT_WIDTH_16_BITS, HT_FREQUENCY_LIMIT_HT1_ONLY,
	},

	/* The 2nd element in the array merely terminates the list */
	{
		HT_LIST_TERMINAL
	}
};
#endif /* HYPERTRANSPORT_V31_SUPPORT == 0 */

/**
 * HyperTransport links will typically require an equalization at high frequencies.
 * This is called deemphasis.
 *
 * Deemphasis is specified as levels, for example, -3 db.
 * There are two levels for each link, its receiver deemphasis level and its DCV level,
 * which is based on the far side transmitter's deemphasis.
 * For each link, different levels may be required at each link frequency.
 *
 * Coherent connections between processors should have an entry for the port on each processor.
 * There should be one entry for the host root port of each non-coherent chain.
 *
 * AGESA initialization code does not set deemphasis on IO Devices.
 * A default is provided for internal links of MCM processors, and
 * those links will generally not need deemphasis structures.
 */
CONST CPU_HT_DEEMPHASIS_LEVEL ROMDATA s8226_deemphasis_list[] =
{
	/* Socket, Link, LowFreq, HighFreq, Receiver Deemphasis, Dcv Deemphasis */

	/* Non-coherent link deemphasis. */
	{0, 2, HT3_FREQUENCY_MIN, HT_FREQUENCY_1600M, DeemphasisLevelNone, DcvLevelNone},
	{0, 2, HT_FREQUENCY_1800M, HT_FREQUENCY_1800M, DeemphasisLevelMinus3, DcvLevelMinus5},
	{0, 2, HT_FREQUENCY_2000M, HT_FREQUENCY_2000M, DeemphasisLevelMinus6, DcvLevelMinus5},
	{0, 2, HT_FREQUENCY_2200M, HT_FREQUENCY_2200M, DeemphasisLevelMinus6, DcvLevelMinus7},
	{0, 2, HT_FREQUENCY_2400M, HT_FREQUENCY_2400M, DeemphasisLevelMinus8, DcvLevelMinus7},
	{0, 2, HT_FREQUENCY_2600M, HT_FREQUENCY_2600M, DeemphasisLevelMinus11pre8, DcvLevelMinus9},

	{1, 2, HT3_FREQUENCY_MIN, HT_FREQUENCY_1600M, DeemphasisLevelNone, DcvLevelNone},
	{1, 2, HT_FREQUENCY_1800M, HT_FREQUENCY_1800M, DeemphasisLevelMinus3, DcvLevelMinus5},
	{1, 2, HT_FREQUENCY_2000M, HT_FREQUENCY_2000M, DeemphasisLevelMinus6, DcvLevelMinus5},
	{1, 2, HT_FREQUENCY_2200M, HT_FREQUENCY_2200M, DeemphasisLevelMinus6, DcvLevelMinus7},
	{1, 2, HT_FREQUENCY_2400M, HT_FREQUENCY_2400M, DeemphasisLevelMinus8, DcvLevelMinus7},
	{1, 2, HT_FREQUENCY_2600M, HT_FREQUENCY_2600M, DeemphasisLevelMinus11pre8, DcvLevelMinus9},

	{2, 0, HT3_FREQUENCY_MIN, HT_FREQUENCY_1600M, DeemphasisLevelNone, DcvLevelNone},
	{2, 0, HT_FREQUENCY_1800M, HT_FREQUENCY_1800M, DeemphasisLevelMinus3, DcvLevelMinus5},
	{2, 0, HT_FREQUENCY_2000M, HT_FREQUENCY_2000M, DeemphasisLevelMinus6, DcvLevelMinus5},
	{2, 0, HT_FREQUENCY_2200M, HT_FREQUENCY_2200M, DeemphasisLevelMinus6, DcvLevelMinus7},
	{2, 0, HT_FREQUENCY_2400M, HT_FREQUENCY_2400M, DeemphasisLevelMinus8, DcvLevelMinus7},
	{2, 0, HT_FREQUENCY_2600M, HT_FREQUENCY_2600M, DeemphasisLevelMinus11pre8, DcvLevelMinus9},

	{3, 0, HT3_FREQUENCY_MIN, HT_FREQUENCY_1600M, DeemphasisLevelNone, DcvLevelNone},
	{3, 0, HT_FREQUENCY_1800M, HT_FREQUENCY_1800M, DeemphasisLevelMinus3, DcvLevelMinus5},
	{3, 0, HT_FREQUENCY_2000M, HT_FREQUENCY_2000M, DeemphasisLevelMinus6, DcvLevelMinus5},
	{3, 0, HT_FREQUENCY_2200M, HT_FREQUENCY_2200M, DeemphasisLevelMinus6, DcvLevelMinus7},
	{3, 0, HT_FREQUENCY_2400M, HT_FREQUENCY_2400M, DeemphasisLevelMinus8, DcvLevelMinus7},
	{3, 0, HT_FREQUENCY_2600M, HT_FREQUENCY_2600M, DeemphasisLevelMinus11pre8, DcvLevelMinus9},

	/* Coherent link deemphasis. */
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT3_FREQUENCY_MIN, HT_FREQUENCY_1600M, DeemphasisLevelNone, DcvLevelNone},
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_1800M, HT_FREQUENCY_1800M, DeemphasisLevelMinus3, DcvLevelMinus3},
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2000M, HT_FREQUENCY_2000M, DeemphasisLevelMinus6, DcvLevelMinus6},
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2200M, HT_FREQUENCY_2200M, DeemphasisLevelMinus6, DcvLevelMinus6},
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2400M, HT_FREQUENCY_2400M, DeemphasisLevelMinus8, DcvLevelMinus8},
	{HT_LIST_MATCH_ANY, HT_LIST_MATCH_ANY, HT_FREQUENCY_2600M, HT_FREQUENCY_MAX, DeemphasisLevelMinus11pre8, DcvLevelMinus11},

	/* End of the list */
	{
		HT_LIST_TERMINAL
	}
};

/**
 * For systems using socket infrastructure that permits strapping the SBI
 * address for each socket, this should be used to provide a socket ID value.
 * This is referred to as the hardware method for socket naming, and is the
 * preferred solution.
 */
/*
 * I do NOT know howto config socket id in simnow,
 * so use this software way to make HT works in simnow,
 * real hardware do not need this Socket Map.
 *
 * A physical socket map for a 4 G34 Sockets MCM processors topology,
 * reference the mainboard schemantic in detail.
 *
 */
CONST SYSTEM_PHYSICAL_SOCKET_MAP ROMDATA s8226_socket_map[] =
{
#define HT_SOCKET0	0
#define HT_SOCKET1	1
#define HT_SOCKET2	2
#define HT_SOCKET3	3

/**
 * 0-3 are sublink 0, 4-7 are sublink 1
 */
#define HT_LINK0A	0
#define HT_LINK1A	1
#define HT_LINK2A	2
#define HT_LINK3A	3
#define HT_LINK0B	4
#define HT_LINK1B	5
#define HT_LINK2B	6
#define HT_LINK3B	7

	/* Source Socket, Link, Target Socket */
/*	{HT_SOCKET0, HT_LINK0A, HT_SOCKET1},
	{HT_SOCKET0, HT_LINK0B, HT_SOCKET3},
	{HT_SOCKET0, HT_LINK1A, HT_SOCKET1},
	{HT_SOCKET0, HT_LINK1B, HT_SOCKET3},
	{HT_SOCKET0, HT_LINK3A, HT_SOCKET2},
	{HT_SOCKET0, HT_LINK3B, HT_SOCKET2},

	{HT_SOCKET1, HT_LINK0A, HT_SOCKET2},
	{HT_SOCKET1, HT_LINK0B, HT_SOCKET3},
	{HT_SOCKET1, HT_LINK1A, HT_SOCKET0},
	{HT_SOCKET1, HT_LINK1B, HT_SOCKET2},
	{HT_SOCKET1, HT_LINK3A, HT_SOCKET0},
	{HT_SOCKET1, HT_LINK3B, HT_SOCKET3},

	{HT_SOCKET2, HT_LINK0A, HT_SOCKET3},
	{HT_SOCKET2, HT_LINK0B, HT_SOCKET0},
	{HT_SOCKET2, HT_LINK1A, HT_SOCKET3},
	{HT_SOCKET2, HT_LINK1B, HT_SOCKET1},
	{HT_SOCKET2, HT_LINK3A, HT_SOCKET1},
	{HT_SOCKET2, HT_LINK3B, HT_SOCKET0},

	{HT_SOCKET3, HT_LINK0A, HT_SOCKET2},
	{HT_SOCKET3, HT_LINK0B, HT_SOCKET1},
	{HT_SOCKET3, HT_LINK1A, HT_SOCKET1},
	{HT_SOCKET3, HT_LINK1B, HT_SOCKET0},
	{HT_SOCKET3, HT_LINK3A, HT_SOCKET0},
	{HT_SOCKET3, HT_LINK3B, HT_SOCKET2}, */
};

CONST AP_MTRR_SETTINGS ROMDATA s8226_ap_mtrr_list[] =
{
	{AMD_AP_MTRR_FIX64k_00000, 0x1E1E1E1E1E1E1E1E},
	{AMD_AP_MTRR_FIX16k_80000, 0x1E1E1E1E1E1E1E1E},
	{AMD_AP_MTRR_FIX16k_A0000, 0x0000000000000000},
	{AMD_AP_MTRR_FIX4k_C0000,  0x0000000000000000},
	{AMD_AP_MTRR_FIX4k_C8000,  0x0000000000000000},
	{AMD_AP_MTRR_FIX4k_D0000,  0x0000000000000000},
	{AMD_AP_MTRR_FIX4k_D8000,  0x0000000000000000},
	{AMD_AP_MTRR_FIX4k_E0000,  0x1818181818181818},
	{AMD_AP_MTRR_FIX4k_E8000,  0x1818181818181818},
	{AMD_AP_MTRR_FIX4k_F0000,  0x1818181818181818},
	{AMD_AP_MTRR_FIX4k_F8000,  0x1818181818181818},
	{CPU_LIST_TERMINAL}
};

#define BLDCFG_BUID_SWAP_LIST			&s8226_manual_swaplist
#define BLDCFG_HTFABRIC_LIMITS_LIST		&s8226_cpu2cpu_limit_list
#define BLDCFG_HTCHAIN_LIMITS_LIST		&s8226_io_limit_list
#define BLDCFG_PLATFORM_DEEMPHASIS_LIST		&s8226_deemphasis_list
#define BLDCFG_AP_MTRR_SETTINGS_LIST		&s8226_ap_mtrr_list
//#define BLDCFG_SYSTEM_PHYSICAL_SOCKET_MAP	&s8226_socket_map


/*  Process the options...
 * This file include MUST occur AFTER the user option selection settings
 */

#include "SanMarinoInstall.h"
