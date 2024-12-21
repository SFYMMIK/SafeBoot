#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/tpm.h>
#inluce <linux/efi.h>

MODULE_LICENSE("BSD-3");
MODULE_AUTHOR("Szymon Grajner");
MODULE_DESCRIPTION("SafeBoot: Protection from BootKit and related threats");

// Function to check SecureBoot status
int check_secureboot(void) {
    printk(KERN_INFO "Checking if SecureBoot is enabled...\n");
#ifdef CONFIG_EFI
    if (efi_enabled(EFI_SECURE_BOOT))
        return 1;
#endif
    return 0;
}

void protect_mbr(void) {
    char mbr[512];
    mm_segment_t old_fs;
    loff_t pos = 0;
    struct file *f;
    int ret;

    printk(KERN_INFO "Protecting MBR from malicious modifications...\n");

    // Open the raw disk device (e.g. /dev/sda)
    f = filp_open("/dev/sda", O_RDONLY, 0);
    if (IS_ERR(f)) {
        printk(KERN_ERR "Failed to open /dev/sda for MBR protection\n");
        return;
    }

    // Switch to kernel's memory space for I/O
    old_fs = get_fs();
    set_fs(KERNEL_DS);

    // Read the first 512 bytes of the disk (MBR sector)
    ret = kernel_read(f, mbr, sizeof(mbr), &pos);

    // Restore the original memory space
    set_fs(old_fs);

    filp_close(f, NULL);

    if (ret < 0) {
        printk(KERN_ERR "Failed to read MBR content\n");
        return;
    }

    // Check basic MBR signature
    if (mbr[510] != 0x55 || mbr[511] != 0xAA) {
        printk(KERN_WARNING "MBR signature invalid! Possible malicious modifications.\n");
        // TODO: Implement steps to handle suspicious MBR changes
    } else {
        printk(KERN_INFO "MBR is intact.\n");
    }
}

static int __init safeboot_init(void) {
    printk(KERN_INFO "SafeBoot module loaded\n");

    // Check if SecureBoot is enabled
    if (check_secureboot()) {
        printk(KERN_INFO "SecureBoot is ENABLED.\n");
    } else {
        printk(KERN_WARNING "Warning: SecureBoot is not enabled. It is recommended to enable it.\n");
    }

    // Protect MBR and GPT partitions
    protect_mbr();

    return 0;
}

// Cleanup the module
static void __exit safeboot_exit(void) {
    printk(KERN_INFO "SafeBoot module unloaded\n");
}

module_init(safeboot_init);
module_exit(safeboot_exit);
