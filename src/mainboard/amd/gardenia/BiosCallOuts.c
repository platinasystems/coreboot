/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015-2016 Advanced Micro Devices, Inc.
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

#include <device/pci_def.h>
#include <device/device.h>
#include "AGESA.h"
#include "amdlib.h"
#include <northbridge/amd/pi/BiosCallOuts.h>
#include <northbridge/amd/pi/00670F00/chip.h>
#include "Ids.h"
#include "heapManager.h"
#include "FchPlatform.h"
#include "cbfs.h"
#if IS_ENABLED(CONFIG_HUDSON_IMC_FWM)
#include "imc.h"
#endif
#include "hudson.h"
#include <stdlib.h>
#include "BiosCallOuts.h"
#include "northbridge/amd/pi/dimmSpd.h"
#include "northbridge/amd/pi/agesawrapper.h"

static AGESA_STATUS Fch_Oem_config(UINT32 Func, UINT32 FchData, VOID *ConfigPtr);

const BIOS_CALLOUT_STRUCT BiosCallouts[] =
{
	{AGESA_ALLOCATE_BUFFER,          agesa_AllocateBuffer },
	{AGESA_DEALLOCATE_BUFFER,        agesa_DeallocateBuffer },
	{AGESA_LOCATE_BUFFER,            agesa_LocateBuffer },
	{AGESA_READ_SPD,                 agesa_ReadSpd },
	{AGESA_DO_RESET,                 agesa_Reset },
	{AGESA_READ_SPD_RECOVERY,        agesa_NoopUnsupported },
	{AGESA_RUNFUNC_ONAP,             agesa_RunFuncOnAp },
	{AGESA_GET_IDS_INIT_DATA,        agesa_EmptyIdsInitData },
	{AGESA_HOOKBEFORE_DQS_TRAINING,  agesa_NoopSuccess },
	{AGESA_HOOKBEFORE_EXIT_SELF_REF, agesa_NoopSuccess },
	{AGESA_FCH_OEM_CALLOUT,          Fch_Oem_config },
	{AGESA_GNB_GFX_GET_VBIOS_IMAGE,  agesa_GfxGetVbiosImage }
};
const int BiosCalloutsLen = ARRAY_SIZE(BiosCallouts);

static const GPIO_CONTROL oem_gardenia_gpio[] = {
	/* BT radio disable */
	{14, Function1, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						| FCH_GPIO_OUTPUT_ENABLE},
	/* NFC PU */
	{64, Function0, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						| FCH_GPIO_OUTPUT_ENABLE},
	/* NFC wake */
	{65, Function0, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						| FCH_GPIO_OUTPUT_ENABLE},
	/* Webcam */
	{66, Function0, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						| FCH_GPIO_OUTPUT_ENABLE},
	/* PCIe presence detect */
	{69, Function0, FCH_GPIO_PULL_UP_ENABLE},
	/* GPS sleep */
	{70, Function0, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						| FCH_GPIO_OUTPUT_ENABLE},
	/* MUX for Power Express Eval */
	{116, Function1, FCH_GPIO_PULL_DOWN_ENABLE},
	/* SD power */
	{119, Function2, FCH_GPIO_PULL_UP_ENABLE | FCH_GPIO_OUTPUT_VALUE
						 | FCH_GPIO_OUTPUT_ENABLE},
	{-1}
};
/**
 * Fch Oem setting callback
 *
 *  Configure platform specific Hudson device,
 *   such as Azalia, SATA, IMC etc.
 */
AGESA_STATUS Fch_Oem_config(UINT32 Func, UINT32 FchData, VOID *ConfigPtr)
{
	AMD_CONFIG_PARAMS *StdHeader = ConfigPtr;

	if (StdHeader->Func == AMD_INIT_RESET) {
		FCH_RESET_DATA_BLOCK *FchParams_reset = (FCH_RESET_DATA_BLOCK *)FchData;
		printk(BIOS_DEBUG, "Fch OEM config in INIT RESET ");
		FchParams_reset->FchReset.SataEnable = hudson_sata_enable();
		FchParams_reset->FchReset.IdeEnable = hudson_ide_enable();
		FchParams_reset->EarlyOemGpioTable = oem_gardenia_gpio;
	} else if (StdHeader->Func == AMD_INIT_ENV) {
		FCH_DATA_BLOCK *FchParams_env = (FCH_DATA_BLOCK *)FchData;
		printk(BIOS_DEBUG, "Fch OEM config in INIT ENV ");
#if IS_ENABLED(CONFIG_HUDSON_IMC_FWM)
		oem_fan_control(FchParams_env);
#endif

		/* XHCI configuration */
#if CONFIG_HUDSON_XHCI_ENABLE
		FchParams_env->Usb.Xhci0Enable = TRUE;
#else
		FchParams_env->Usb.Xhci0Enable = FALSE;
#endif
		FchParams_env->Usb.Xhci1Enable = FALSE;
		FchParams_env->Usb.USB30PortInit = 8; /* 8: If USB3 port is unremoveable. */

		/* SATA configuration */
		FchParams_env->Sata.SataClass = CONFIG_HUDSON_SATA_MODE;
		switch ((SATA_CLASS)CONFIG_HUDSON_SATA_MODE) {
		case SataRaid:
		case SataAhci:
		case SataAhci7804:
		case SataLegacyIde:
			FchParams_env->Sata.SataIdeMode = FALSE;
			break;
		case SataIde2Ahci:
		case SataIde2Ahci7804:
		default: /* SataNativeIde */
			FchParams_env->Sata.SataIdeMode = TRUE;
			break;
		}
	}
	printk(BIOS_DEBUG, "Done\n");

	return AGESA_SUCCESS;
}
