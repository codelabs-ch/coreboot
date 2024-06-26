TAG-$(CONFIG_FILO_HEAD)=origin/bsbsc-csl-24.02
NAME-$(CONFIG_FILO_HEAD)=bsbsc-csl
TAG-$(CONFIG_FILO_STABLE)=c2fa1ea6125c63e84cdf7779c37d76da8c5bc412
NAME-$(CONFIG_FILO_STABLE)=STABLE

project_git_repo=https://github.com/codelabs-ch/filo.git
project_dir=filo

unexport KCONFIG_AUTOHEADER
unexport KCONFIG_AUTOCONFIG
unexport KCONFIG_DEPENDENCIES
unexport KCONFIG_SPLITCONFIG
unexport KCONFIG_TRISTATE
unexport KCONFIG_NEGATIVES

all: filo

checkout:
	echo "    GIT        FILO $(NAME-y)"
	test -d filo || \
		git clone $(project_git_repo) $(project_dir)
	cd filo && \
		git remote update && \
		test -n $(TAG-y) && \
			git branch -f $(NAME-y) $(TAG-y) && \
			git checkout $(NAME-y)

config: libpayload
	echo "    CONFIG     FILO $(NAME-y)"
	$(MAKE) -C filo defconfig LIBCONFIG_PATH=../../../libpayload
	# This shows how to force a previously unset .config option *on*
	#echo "CONFIG_VGAHOOKS=y" >> filo/.config
	# This shows how to force a previously set .config option *off*
	#echo "# CONFIG_SMBIOS is not set" >> filo/.config
ifeq ($(CONFIG_FILO_USE_AUTOBOOT),y)
	echo "# CONFIG_USE_GRUB is not set" >> filo/.config
	echo "CONFIG_USE_AUTOBOOT=y" >> filo/.config
	echo 'CONFIG_AUTOBOOT_FILE="$(CONFIG_FILO_AUTOBOOT_FILE)"' >> filo/.config
	echo "CONFIG_AUTOBOOT_DELAY=$(CONFIG_FILO_AUTOBOOT_DELAY)" >> filo/.config
endif

	echo 'CONFIG_MENULST_FILE="hda0:/boot/filo/menu.lst"' >> filo/.config
	echo CONFIG_LIBPAYLOAD_STORAGE=y >> filo/.config
	echo CONFIG_CSL_BOOT=y >> filo/.config
	echo CONFIG_FSYS_CBFS=n >> filo/.config
	#echo CONFIG_DEBUG_ALL=y >> filo/.config
	$(MAKE) -C filo oldconfig LIBCONFIG_PATH=../../../libpayload

filo: config
	echo "    MAKE       FILO $(NAME-y)"
	$(MAKE) -C filo LIBCONFIG_PATH=../../../libpayload

libpayload: checkout
	cd ../../libpayload && $(MAKE) defconfig && \
		$(MAKE) && $(MAKE) DESTDIR=../external/FILO/filo/build install

clean:
	test -d filo && $(MAKE) -C filo clean LIBCONFIG_PATH=../../../libpayload || exit 0

distclean:
	rm -rf filo

print-repo-info:
	echo "$(project_git_repo) $(project_dir)"

.PHONY: checkout config filo clean distclean print-repo-info
