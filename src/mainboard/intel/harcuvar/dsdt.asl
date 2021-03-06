/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 - 2009 coresystems GmbH
 * Copyright 2011 Google Inc.
 * Copyright (C) 2014 - 2017 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <arch/acpi.h>
DefinitionBlock(
	"dsdt.aml",
	"DSDT",
	0x02,		// DSDT revision: ACPI v2.0 and up
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x20110725	// OEM revision
)
{
	// Some generic macros
	#include <southbridge/intel/common/acpi/platform.asl>
	#include "acpi/platform.asl"
	#include "acpi/mainboard.asl"

	// General Purpose Events
	//#include "acpi/gpe.asl"

	// Thermal Handler
	#include "acpi/thermal.asl"

	// global NVS and variables
	#include <soc/intel/denverton_ns/acpi/globalnvs.asl>

	#include <cpu/intel/common/acpi/cpu.asl>

	Scope (\_SB) {
		Device (PCI0)
		{
			#include <soc/intel/denverton_ns/acpi/northcluster.asl>
			#include <soc/intel/denverton_ns/acpi/southcluster.asl>
		}
	}

	/* Chipset specific sleep states */
	#include <southbridge/intel/common/acpi/sleepstates.asl>
}
