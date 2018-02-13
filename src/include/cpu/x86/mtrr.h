#ifndef CPU_X86_MTRR_H
#define CPU_X86_MTRR_H

/*  These are the region types  */
#define MTRR_TYPE_UNCACHEABLE		0
#define MTRR_TYPE_WRCOMB		1
#define MTRR_TYPE_WRTHROUGH		4
#define MTRR_TYPE_WRPROT		5
#define MTRR_TYPE_WRBACK		6
#define MTRR_NUM_TYPES			7

#define MTRR_CAP_MSR			0x0fe

#define MTRR_CAP_SMRR			(1 << 11)
#define MTRR_CAP_WC			(1 << 10)
#define MTRR_CAP_FIX			(1 << 8)
#define MTRR_CAP_VCNT			0xff

#define MTRR_DEF_TYPE_MSR		0x2ff
#define MTRR_DEF_TYPE_MASK		0xff
#define MTRR_DEF_TYPE_EN		(1 << 11)
#define MTRR_DEF_TYPE_FIX_EN		(1 << 10)


#define SMRR_PHYS_BASE			0x1f2
#define SMRR_PHYS_MASK			0x1f3

#define MTRR_PHYS_BASE(reg)		(0x200 + 2 * (reg))
#define MTRR_PHYS_MASK(reg)		(MTRR_PHYS_BASE(reg) + 1)
#define  MTRR_PHYS_MASK_VALID		(1 << 11)

#define NUM_FIXED_RANGES		88
#define RANGES_PER_FIXED_MTRR		8
#define MTRR_FIX_64K_00000		0x250
#define MTRR_FIX_16K_80000		0x258
#define MTRR_FIX_16K_A0000		0x259
#define MTRR_FIX_4K_C0000		0x268
#define MTRR_FIX_4K_C8000		0x269
#define MTRR_FIX_4K_D0000		0x26a
#define MTRR_FIX_4K_D8000		0x26b
#define MTRR_FIX_4K_E0000		0x26c
#define MTRR_FIX_4K_E8000		0x26d
#define MTRR_FIX_4K_F0000		0x26e
#define MTRR_FIX_4K_F8000		0x26f

#if !defined(__ASSEMBLER__) && !defined(__PRE_RAM__)

#include <stdint.h>
#include <stddef.h>

/*
 * The MTRR code has some side effects that the callers should be aware for.
 * 1. The call sequence matters. x86_setup_mtrrs() calls
 *    x86_setup_fixed_mtrrs_no_enable() then enable_fixed_mtrrs() (equivalent
 *    of x86_setup_fixed_mtrrs()) then x86_setup_var_mtrrs(). If the callers
 *    want to call the components of x86_setup_mtrrs() because of other
 *    requirements the ordering should still preserved.
 * 2. enable_fixed_mtrr() will enable both variable and fixed MTRRs because
 *    of the nature of the global MTRR enable flag. Therefore, all direct
 *    or indirect callers of enable_fixed_mtrr() should ensure that the
 *    variable MTRR MSRs do not contain bad ranges.
 *
 * Note that this function sets up MTRRs for addresses above 4GiB.
 */
void x86_setup_mtrrs(void);
/*
 * x86_setup_mtrrs_with_detect() does the same thing as x86_setup_mtrrs(), but
 * it always dynamically detects the number of variable MTRRs available.
 */
void x86_setup_mtrrs_with_detect(void);
/*
 * x86_setup_var_mtrrs() parameters:
 * address_bits - number of physical address bits supported by cpu
 * above4gb - if set setup MTRRs for addresses above 4GiB else ignore
 *            memory ranges above 4GiB
 */
void x86_setup_var_mtrrs(unsigned int address_bits, unsigned int above4gb);
void enable_fixed_mtrr(void);
void x86_setup_fixed_mtrrs(void);
/* Set up fixed MTRRs but do not enable them. */
void x86_setup_fixed_mtrrs_no_enable(void);
void x86_mtrr_check(void);

/* Insert a temporary MTRR range for the duration of coreboot's runtime.
 * This function needs to be called after the first MTRR solution is derived. */
void mtrr_use_temp_range(uintptr_t begin, size_t size, int type);
#endif

#if !defined(__ASSEMBLER__) && defined(__PRE_RAM__) && !defined(__ROMCC__)
void set_var_mtrr(unsigned int reg, unsigned int base, unsigned int size,
	unsigned int type);
int get_free_var_mtrr(void);
#endif

#if !defined(__ASSEMBLER__) && !defined(__ROMCC__)

/* fms: find most significant bit set, stolen from Linux Kernel Source. */
static inline unsigned int fms(unsigned int x)
{
	int r;

	__asm__("bsrl %1,%0\n\t"
		"jnz 1f\n\t"
		"movl $0,%0\n"
		"1:" : "=r" (r) : "g" (x));
	return r;
}

/* fls: find least significant bit set */
static inline unsigned int fls(unsigned int x)
{
	int r;

	__asm__("bsfl %1,%0\n\t"
		"jnz 1f\n\t"
		"movl $32,%0\n"
		"1:" : "=r" (r) : "g" (x));
	return r;
}
#endif

/* Align up to next power of 2, suitable for ROMCC and assembler too.
 * Range of result 256kB to 128MB is good enough here.
 */
#define _POW2_MASK(x)	((x>>1)|(x>>2)|(x>>3)|(x>>4)|(x>>5)| \
					(x>>6)|(x>>7)|(x>>8)|((1<<18)-1))
#define _ALIGN_UP_POW2(x)	((x + _POW2_MASK(x)) & ~_POW2_MASK(x))

/* At the end of romstage, low RAM 0..CACHE_TM_RAMTOP may be set
 * as write-back cacheable to speed up ramstage decompression.
 * Note MTRR boundaries, must be power of two.
 */
#define CACHE_TMP_RAMTOP (16<<20)

#if ((CONFIG_XIP_ROM_SIZE & (CONFIG_XIP_ROM_SIZE - 1)) != 0)
# error "CONFIG_XIP_ROM_SIZE is not a power of 2"
#endif

/* Select CACHE_ROM_SIZE to use with MTRR setup. For most cases this
 * resolves to a suitable CONFIG_ROM_SIZE but some odd cases need to
 * use CONFIG_CACHE_ROM_SIZE_OVERRIDE in the mainboard Kconfig.
 */
#if (CONFIG_CACHE_ROM_SIZE_OVERRIDE != 0)
# define CACHE_ROM_SIZE	CONFIG_CACHE_ROM_SIZE_OVERRIDE
#else
# if ((CONFIG_ROM_SIZE & (CONFIG_ROM_SIZE-1)) == 0)
#  define CACHE_ROM_SIZE CONFIG_ROM_SIZE
# else
#  define CACHE_ROM_SIZE _ALIGN_UP_POW2(CONFIG_ROM_SIZE)
#  if (CACHE_ROM_SIZE < CONFIG_ROM_SIZE) || (CACHE_ROM_SIZE >= \
	(2 * CONFIG_ROM_SIZE))
#   error "CACHE_ROM_SIZE is not optimal."
#  endif
# endif
#endif

#if ((CACHE_ROM_SIZE & (CACHE_ROM_SIZE-1)) != 0)
# error "CACHE_ROM_SIZE is not a power of 2."
#endif

#define CACHE_ROM_BASE	(((1<<20) - (CACHE_ROM_SIZE>>12))<<12)

#if (IS_ENABLED(CONFIG_SOC_SETS_MSRS) && !defined(__ASSEMBLER__) \
	&& !defined(__ROMCC__))
#include <cpu/x86/msr.h>
#include <arch/cpu.h>

/*
 * Set the MTRRs using the data on the stack from setup_stack_and_mtrrs.
 * Return a new top_of_stack value which removes the setup_stack_and_mtrrs data.
 */
asmlinkage void *soc_set_mtrrs(void *top_of_stack);
asmlinkage void soc_enable_mtrrs(void);
#endif /* CONFIG_SOC_SETS_MSRS ... */

#endif /* CPU_X86_MTRR_H */
