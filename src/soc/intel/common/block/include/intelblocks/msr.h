/*
 * This file is part of the coreboot project.
 *
 * Copyright 2017 Intel Corporation.
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

#ifndef SOC_INTEL_COMMON_MSR_H
#define SOC_INTEL_COMMON_MSR_H

#define MSR_CORE_THREAD_COUNT	0x35
#define IA32_FEATURE_CONTROL	0x3a
#define  CPUID_VMX		(1 << 5)
#define  CPUID_SMX		(1 << 6)
#define  PLATFORM_INFO_SET_TDP	(1 << 29)
#define MSR_PLATFORM_INFO	0xce
#define MSR_PMG_CST_CONFIG_CONTROL	0xe2
/* Set MSR_PMG_CST_CONFIG_CONTROL[3:0] for Package C-State limit */
#define   PKG_C_STATE_LIMIT_C2_MASK	0x2
/* Set MSR_PMG_CST_CONFIG_CONTROL[7:4] for Core C-State limit*/
#define   CORE_C_STATE_LIMIT_C10_MASK	0x70
/* Set MSR_PMG_CST_CONFIG_CONTROL[10] to IO redirect to MWAIT */
#define   IO_MWAIT_REDIRECT_MASK	0x400
/* Set MSR_PMG_CST_CONFIG_CONTROL[15] to lock CST_CFG [0-15] bits */
#define   CST_CFG_LOCK_MASK	0x8000
#define MSR_PMG_IO_CAPTURE_BASE	0xe4
#define MSR_POWER_MISC		0x120
#define   ENABLE_IA_UNTRUSTED	(1 << 6)
#define   FLUSH_DL1_L2		(1 << 8)
#define MSR_EMULATE_PM_TMR	0x121
#define   EMULATE_PM_TMR_EN	(1 << 16)
#define MSR_FEATURE_CONFIG	0x13c
#define   FEATURE_CONFIG_RESERVED_MASK	0x3ULL
#define   FEATURE_CONFIG_LOCK	(1 << 0)
#define IA32_MCG_CAP		0x179
#define SMM_MCA_CAP_MSR		0x17d
#define  SMM_CPU_SVRSTR_BIT	57
#define  SMM_CPU_SVRSTR_MASK	(1 << (SMM_CPU_SVRSTR_BIT - 32))
#define MSR_IA32_PERF_CTL	0x199
#define IA32_MISC_ENABLE	0x1a0
#define MSR_TEMPERATURE_TARGET	0x1a2
#define MSR_PREFETCH_CTL	0x1a4
#define   PREFETCH_L1_DISABLE	(1 << 0)
#define   PREFETCH_L2_DISABLE	(1 << 2)
#define MSR_MISC_PWR_MGMT	0x1aa
#define  MISC_PWR_MGMT_EIST_HW_DIS	(1 << 0)
#define  MISC_PWR_MGMT_ISST_EN		(1 << 6)
#define  MISC_PWR_MGMT_ISST_EN_INT	(1 << 7)
#define  MISC_PWR_MGMT_ISST_EN_EPP	(1 << 12)
#define MSR_TURBO_RATIO_LIMIT		0x1ad
#define MSR_POWER_CTL			0x1fc
#define MSR_EVICT_CTL			0x2e0
#define IA32_MC0_CTL			0x400
#define IA32_MC0_STATUS			0x401
#define SMM_FEATURE_CONTROL_MSR		0x4e0
#define  SMM_CPU_SAVE_EN		(1 << 1)
#define MSR_PKG_POWER_SKU_UNIT		0x606
#define MSR_C_STATE_LATENCY_CONTROL_0	0x60a
#define MSR_C_STATE_LATENCY_CONTROL_1	0x60b
#define MSR_C_STATE_LATENCY_CONTROL_2	0x60c
#define MSR_PKG_POWER_LIMIT		0x610
/*
 * For Mobile, RAPL default PL1 time window value set to 28 seconds.
 * RAPL time window calculation defined as follows:
 * Time Window = (float)((1+X/4)*(2*^Y), X Corresponds to [23:22],
 * Y to [21:17] in MSR 0x610. 28 sec is equal to 0x6e.
 */
#define   MB_POWER_LIMIT1_TIME_DEFAULT	0x6e
#define MSR_PKG_POWER_SKU		0x614
#define MSR_DDR_RAPL_LIMIT		0x618
#define MSR_C_STATE_LATENCY_CONTROL_3	0x633
#define MSR_C_STATE_LATENCY_CONTROL_4	0x634
#define MSR_C_STATE_LATENCY_CONTROL_5	0x635
#define  IRTL_VALID			(1 << 15)
#define  IRTL_1_NS			(0 << 10)
#define  IRTL_32_NS			(1 << 10)
#define  IRTL_1024_NS			(2 << 10)
#define  IRTL_32768_NS			(3 << 10)
#define  IRTL_1048576_NS		(4 << 10)
#define  IRTL_33554432_NS		(5 << 10)
#define  IRTL_RESPONSE_MASK		(0x3ff)
#define MSR_COUNTER_24_MHZ		0x637
#define MSR_CONFIG_TDP_NOMINAL		0x648
#define MSR_CONFIG_TDP_LEVEL1		0x649
#define MSR_CONFIG_TDP_LEVEL2		0x64a
#define MSR_CONFIG_TDP_CONTROL		0x64b
#define MSR_TURBO_ACTIVATION_RATIO	0x64c
#define PKG_POWER_LIMIT_MASK		(0x7fff)
#define PKG_POWER_LIMIT_EN		(1 << 15)
#define PKG_POWER_LIMIT_CLAMP		(1 << 16)
#define PKG_POWER_LIMIT_TIME_SHIFT	17
#define PKG_POWER_LIMIT_TIME_MASK	(0x7f)
#define MSR_IA32_PQR_ASSOC		0x0c8f
/* MSR bits 33:32 encode slot number 0-3 */
#define   IA32_PQR_ASSOC_MASK		(1 << 0 | 1 << 1)
#define MSR_IA32_L3_MASK_1		0x0c91
#define MSR_IA32_L3_MASK_2		0x0c92
#define MSR_L2_QOS_MASK(reg)		(0xd10 + reg)

#endif	/* SOC_INTEL_COMMON_MSR_H */

