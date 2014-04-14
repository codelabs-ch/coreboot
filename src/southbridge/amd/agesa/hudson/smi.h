/*
 * Utilities for SMI handlers and SMM setup
 *
 * Copyright (C) 2014 Alexandru Gagniuc <mr.nuke.me@gmail.com>
 * Subject to the GNU GPL v2, or (at your option) any later version.
 */

#ifndef _SOUTHBRIDGE_AMD_AGESA_HUDSON_SMI_H
#define _SOUTHBRIDGE_AMD_AGESA_HUDSON_SMI_H

#include <arch/io.h>

/* ACPI_MMIO_BASE + 0x200 -- leave this string here so grep catches it.
 * This is defined by AGESA, but we dpn't include AGESA headers to avoid
 * polluting the namesace.
 */
#define SMI_BASE 0xfed80200

#define SMI_REG_SMITRIG0	0x98
#define SMITRG0_EOS		(1 << 28)
#define SMITRG0_SMIENB		(1 << 31)

#define SMI_REG_CONTROL0	0xa0

enum smi_src_mode {
	SMI_SRC_MODE_DISABLE = 0,
	SMI_SRC_MODE_SMI = 1,
	SMI_SRC_MODE_NMI = 2,
	SMI_SRC_MODE_IRQ13 = 3,
};

static inline uint32_t smi_read32(uint8_t offset)
{
	return read32(SMI_BASE + offset);
}

static inline void smi_write32(uint8_t offset, uint32_t value)
{
	write32(SMI_BASE + offset, value);
}

static inline uint16_t smi_read16(uint8_t offset)
{
	return read16(SMI_BASE + offset);
}

static inline void smi_write16(uint8_t offset, uint16_t value)
{
	write16(SMI_BASE + offset, value);
}

#ifndef __SMM__
void hudson_enable_smi_generation(void);
void hudson_enable_gevent_smi(uint8_t gevent);
void hudson_enable_acpi_cmd_smi(void);
#endif

#endif /* _SOUTHBRIDGE_AMD_AGESA_HUDSON_SMI_H */
