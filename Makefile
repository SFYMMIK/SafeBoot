# Kernel module compilation settings
obj-m += safeboot.o
KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

# AUR package directory and files
AUR_DIR = $(PWD)/pkgbuild
PKG_NAME = safeboot
SERVICE_DIR = $(PWD)/services

# Default target: Compile kernel module
all:
	make -C $(KDIR) M=$(PWD) modules
	$(MAKE) -C $(AUR_DIR)

# Create AUR package
aur-package:
	cp $(PWD)/PKGBUILD $(AUR_DIR)/
	cd $(AUR_DIR) && makepkg -si

# Install the module
install:
	sudo insmod safeboot.ko

# Create the service files
create-services:
	mkdir -p $(SERVICE_DIR)
	./create_systemd_service.sh
	./create_openrc_service.sh
	./create_runit_service.sh

# Clean up
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf $(SERVICE_DIR)
	rm -rf $(AUR_DIR)

.PHONY: all clean install create-services aur-package
