#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include "i82801er.h"


static struct device_operations nic_ops  = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.init             = 0,
	.scan_bus         = 0,
};

static struct pci_driver nic_driver __pci_driver = {
	.ops    = &nic_ops,
	.vendor = PCI_VENDOR_ID_INTEL,
	.device = 0x1051,
};
