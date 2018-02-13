/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Advanced Micro Devices, Inc.
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

#include <assert.h>
#include <stdint.h>
#include <arch/io.h>
#include <arch/acpi.h>
#include <console/console.h>
#include <reset.h>
#include <arch/cpu.h>
#include <cbmem.h>
#include <soc/southbridge.h>
#include <soc/pci_devs.h>
#include <cpu/x86/msr.h>
#include <delay.h>

/* vendor includes */
#include <Porting.h>
#include <AGESA.h>
#include <Fch/Fch.h>

void configure_stoneyridge_uart(void)
{
	u8 byte, byte2;

	/* Power on the UART and AMBA devices */
	byte = read8((void *)ACPI_MMIO_BASE + AOAC_BASE + FCH_AOAC_REG56
					+ CONFIG_UART_FOR_CONSOLE * 2);
	byte |= AOAC_PWR_ON_DEV;
	write8((void *)ACPI_MMIO_BASE + AOAC_BASE + FCH_AOAC_REG56
					+ CONFIG_UART_FOR_CONSOLE * 2, byte);

	byte = read8((void *)ACPI_MMIO_BASE + AOAC_BASE + FCH_AOAC_REG62);
	byte |= AOAC_PWR_ON_DEV;
	write8((void *)ACPI_MMIO_BASE + AOAC_BASE + FCH_AOAC_REG62, byte);

	/* Set the GPIO mux to UART */
	write8((void *)FCH_IOMUXx89_UART0_RTS_L_EGPIO137, 0);
	write8((void *)FCH_IOMUXx8A_UART0_TXD_EGPIO138, 0);
	write8((void *)FCH_IOMUXx8E_UART1_RTS_L_EGPIO142, 0);
	write8((void *)FCH_IOMUXx8F_UART1_TXD_EGPIO143, 0);

	/* Wait for the UART and AMBA devices to indicate power and clock OK */
	do {
		udelay(100);
		byte = read8((void *)ACPI_MMIO_BASE + AOAC_BASE + FCH_AOAC_REG57
					+ CONFIG_UART_FOR_CONSOLE * 2);
		byte &= (A0AC_PWR_RST_STATE | AOAC_RST_CLK_OK_STATE);
		byte2 = read8((void *)ACPI_MMIO_BASE + AOAC_BASE
					+ FCH_AOAC_REG63);
		byte2 &= (A0AC_PWR_RST_STATE | AOAC_RST_CLK_OK_STATE);
	} while (!((byte == (A0AC_PWR_RST_STATE | AOAC_RST_CLK_OK_STATE)) &&
		   (byte2 == (A0AC_PWR_RST_STATE | AOAC_RST_CLK_OK_STATE))));

}

void sb_pci_port80(void)
{
	u8 byte;
	pci_devfn_t dev;

	dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);

	byte = pci_read_config8(dev, 0x4a);
	byte &= ~(1 << 5); /* disable lpc port 80 */
	pci_write_config8(dev, 0x4a, byte);
}

void sb_lpc_port80(void)
{
	u8 byte;
	pci_devfn_t dev;

	/* Enable LPC controller */
	outb(0xec, PM_INDEX);
	byte = inb(PM_DATA);
	byte |= 1;
	outb(0xec, PM_INDEX);
	outb(byte, PM_DATA);

	/* Enable port 80 LPC decode in pci function 3 configuration space. */
	dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);
	byte = pci_read_config8(dev, 0x4a);
	byte |= 1 << 5; /* enable port 80 */
	pci_write_config8(dev, 0x4a, byte);
}

void sb_lpc_decode(void)
{
	pci_devfn_t dev;
	u32 tmp = 0;

	/* Enable I/O decode to LPC bus */
	dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);
	tmp = DECODE_ENABLE_PARALLEL_PORT0 | DECODE_ENABLE_PARALLEL_PORT2
		| DECODE_ENABLE_PARALLEL_PORT4 | DECODE_ENABLE_SERIAL_PORT0
		| DECODE_ENABLE_SERIAL_PORT1 | DECODE_ENABLE_SERIAL_PORT2
		| DECODE_ENABLE_SERIAL_PORT3 | DECODE_ENABLE_SERIAL_PORT4
		| DECODE_ENABLE_SERIAL_PORT5 | DECODE_ENABLE_SERIAL_PORT6
		| DECODE_ENABLE_SERIAL_PORT7 | DECODE_ENABLE_AUDIO_PORT0
		| DECODE_ENABLE_AUDIO_PORT1 | DECODE_ENABLE_AUDIO_PORT2
		| DECODE_ENABLE_AUDIO_PORT3 | DECODE_ENABLE_MSS_PORT2
		| DECODE_ENABLE_MSS_PORT3 | DECODE_ENABLE_FDC_PORT0
		| DECODE_ENABLE_FDC_PORT1 | DECODE_ENABLE_GAME_PORT
		| DECODE_ENABLE_KBC_PORT | DECODE_ENABLE_ACPIUC_PORT
		| DECODE_ENABLE_ADLIB_PORT;

	pci_write_config32(dev, LPC_IO_PORT_DECODE_ENABLE, tmp);
}

static void enable_wideio(uint8_t port, uint16_t size)
{
	uint32_t wideio_enable[] = {
		LPC_WIDEIO0_ENABLE,
		LPC_WIDEIO1_ENABLE,
		LPC_WIDEIO2_ENABLE
	};
	uint32_t alt_wideio_enable[] = {
		LPC_ALT_WIDEIO0_ENABLE,
		LPC_ALT_WIDEIO1_ENABLE,
		LPC_ALT_WIDEIO2_ENABLE
	};
	pci_devfn_t dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);
	uint32_t tmp;

	/* Only allow port 0-2 */
	assert(port <= ARRAY_SIZE(wideio_enable));

	if (size == 16) {
		tmp = pci_read_config32(dev, LPC_ALT_WIDEIO_RANGE_ENABLE);
		tmp |= alt_wideio_enable[port];
		pci_write_config32(dev, LPC_ALT_WIDEIO_RANGE_ENABLE, tmp);
	} else { 	/* 512 */
		tmp = pci_read_config32(dev, LPC_ALT_WIDEIO_RANGE_ENABLE);
		tmp &= ~alt_wideio_enable[port];
		pci_write_config32(dev, LPC_ALT_WIDEIO_RANGE_ENABLE, tmp);
	}

	/* Enable the range */
	tmp = pci_read_config32(dev, LPC_IO_OR_MEM_DECODE_ENABLE);
	tmp |= wideio_enable[port];
	pci_write_config32(dev, LPC_IO_OR_MEM_DECODE_ENABLE, tmp);
}

/*
 * lpc_wideio_window() may be called any point in romstage, but take
 * care that AGESA doesn't overwrite the range this function used.
 * The function checks if there is an empty range and if all ranges are
 * used the function throws an assert. The function doesn't check for a
 * duplicate range, for ranges that can  be merged into a single
 * range, or ranges that overlap.
 *
 * The developer is expected to ensure that there are no conflicts.
 */
static void lpc_wideio_window(uint16_t base, uint16_t size)
{
	pci_devfn_t dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);
	u32 tmp;

	/* Support 512 or 16 bytes per range */
	assert(size == 512 || size == 16);

	/* Find and open Base Register and program it */
	tmp = pci_read_config32(dev, LPC_WIDEIO_GENERIC_PORT);

	if ((tmp & 0xffff) == 0) {	/* WIDEIO0 */
		tmp |= base;
		pci_write_config32(dev, LPC_WIDEIO_GENERIC_PORT, tmp);
		enable_wideio(0, size);
	} else if ((tmp & 0xffff0000) == 0) {	/* WIDEIO1 */
		tmp |= (base << 16);
		pci_write_config32(dev, LPC_WIDEIO_GENERIC_PORT, tmp);
		enable_wideio(1, size);
	} else { /* Check WIDEIO2 register */
		tmp = pci_read_config32(dev, LPC_WIDEIO2_GENERIC_PORT);
		if ((tmp & 0xffff) == 0) {	/* WIDEIO2 */
			tmp |= base;
			pci_write_config32(dev, LPC_WIDEIO2_GENERIC_PORT, tmp);
			enable_wideio(2, size);
		} else {	/* All WIDEIO locations used*/
			assert(0);
		}
	}
}

void lpc_wideio_512_window(uint16_t base)
{
	assert(IS_ALIGNED(base, 512));
	lpc_wideio_window(base, 512);
}

void lpc_wideio_16_window(uint16_t base)
{
	assert(IS_ALIGNED(base, 16));
	lpc_wideio_window(base, 16);
}

int s3_save_nvram_early(u32 dword, int size, int  nvram_pos)
{
	int i;
	printk(BIOS_DEBUG, "Writing %x of size %d to nvram pos: %d\n",
					dword, size, nvram_pos);

	for (i = 0 ; i < size ; i++) {
		outb(nvram_pos, BIOSRAM_INDEX);
		outb((dword >> (8 * i)) & 0xff, BIOSRAM_DATA);
		nvram_pos++;
	}

	return nvram_pos;
}

int s3_load_nvram_early(int size, u32 *old_dword, int nvram_pos)
{
	u32 data = *old_dword;
	int i;
	for (i = 0 ; i < size ; i++) {
		outb(nvram_pos, BIOSRAM_INDEX);
		data &= ~(0xff << (i * 8));
		data |= inb(BIOSRAM_DATA) << (i * 8);
		nvram_pos++;
	}
	*old_dword = data;
	printk(BIOS_DEBUG, "Loading %x of size %d to nvram pos:%d\n",
					*old_dword, size, nvram_pos-size);
	return nvram_pos;
}

void sb_clk_output_48Mhz(void)
{
	u32 ctrl;

	/*
	 * Enable the X14M_25M_48M_OSC pin and leaving it at it's default so
	 * 48Mhz will be on ball AP13 (FT3b package)
	 */
	ctrl = read32((void *)(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40));

	/* clear the OSCOUT1_ClkOutputEnb to enable the 48 Mhz clock */
	ctrl &= ~(1<<2);
	write32((void *)(ACPI_MMIO_BASE + MISC_BASE + FCH_MISC_REG40), ctrl);
}

static uintptr_t sb_spibase(void)
{
	/* Make sure the base address is predictable */
	device_t dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);
	u32 base, enables;

	base = pci_read_config32(dev, SPIROM_BASE_ADDRESS_REGISTER);
	enables = base & 0xf;
	base &= ~0x3f;

	if (!base) {
		base = SPI_BASE_ADDRESS;
		pci_write_config32(dev, SPIROM_BASE_ADDRESS_REGISTER, base
						| enables | SPI_ROM_ENABLE);
		/* PCI_COMMAND_MEMORY is read-only and enabled. */
	}
	return (uintptr_t)base;
}

void sb_set_spi100(u16 norm, u16 fast, u16 alt, u16 tpm)
{
	uintptr_t base = sb_spibase();
	write16((void *)base + SPI100_SPEED_CONFIG,
				(norm << SPI_NORM_SPEED_NEW_SH) |
				(fast << SPI_FAST_SPEED_NEW_SH) |
				(alt << SPI_ALT_SPEED_NEW_SH) |
				(tpm << SPI_TPM_SPEED_NEW_SH));
	write16((void *)base + SPI100_ENABLE, SPI_USE_SPI100);
}

void sb_disable_4dw_burst(void)
{
	uintptr_t base = sb_spibase();
	write16((void *)base + SPI100_HOST_PREF_CONFIG,
			read16((void *)base + SPI100_HOST_PREF_CONFIG)
					& ~SPI_RD4DW_EN_HOST);
}

void sb_set_readspeed(u16 norm, u16 fast)
{
	uintptr_t base = sb_spibase();
	write16((void *)base + SPI_CNTRL1, (read16((void *)base + SPI_CNTRL1)
					& ~SPI_CNTRL1_SPEED_MASK)
					| (norm << SPI_NORM_SPEED_SH)
					| (fast << SPI_FAST_SPEED_SH));
}

void sb_read_mode(u32 mode)
{
	uintptr_t base = sb_spibase();
	write32((void *)base + SPI_CNTRL0,
			(read32((void *)base + SPI_CNTRL0)
					& ~SPI_READ_MODE_MASK) | mode);
}

void sb_tpm_decode_spi(void)
{
	device_t dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);	/* LPC device */

	u32 spibase = pci_read_config32(dev, SPIROM_BASE_ADDRESS_REGISTER);
	pci_write_config32(dev, SPIROM_BASE_ADDRESS_REGISTER, spibase
							| ROUTE_TPM_2_SPI);
}

/*
 * Enable 4MB (LPC) ROM access at 0xFFC00000 - 0xFFFFFFFF.
 *
 * Hardware should enable LPC ROM by pin straps. This function does not
 * handle the theoretically possible PCI ROM, FWH, or SPI ROM configurations.
 *
 * The southbridge power-on default is to map 512K ROM space.
 *
 */
void sb_enable_rom(void)
{
	u8 reg8;
	pci_devfn_t dev;

	dev = PCI_DEV(0, PCU_DEV, LPC_FUNC);

	/* Decode variable LPC ROM address ranges 1 and 2. */
	reg8 = pci_io_read_config8(dev, 0x48);
	reg8 |= (1 << 3) | (1 << 4);
	pci_io_write_config8(dev, 0x48, reg8);

	/* LPC ROM address range 1: */
	/* Enable LPC ROM range mirroring start at 0x000e(0000). */
	pci_io_write_config16(dev, 0x68, 0x000e);
	/* Enable LPC ROM range mirroring end at 0x000f(ffff). */
	pci_io_write_config16(dev, 0x6a, 0x000f);

	/* LPC ROM address range 2: */
	/*
	 * Enable LPC ROM range start at:
	 * 0xfff8(0000): 512KB
	 * 0xfff0(0000): 1MB
	 * 0xffe0(0000): 2MB
	 * 0xffc0(0000): 4MB
	 */
	pci_io_write_config16(dev, 0x6c, 0x10000
					- (CONFIG_COREBOOT_ROMSIZE_KB >> 6));
	/* Enable LPC ROM range end at 0xffff(ffff). */
	pci_io_write_config16(dev, 0x6e, 0xffff);
}

void bootblock_fch_early_init(void)
{
	sb_enable_rom();
	sb_lpc_port80();
	sb_lpc_decode();
}
