cmd_drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o := /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/scripts/gcc-wrapper.py /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcc -Wp,-MD,drivers/staging/prima_legacy/CORE/HDD/src/.bap_hdd_main.o.d  -nostdinc -isystem /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -DASUS_SW_VER=\"A68_ENG\" -DANI_PRODUCT_TYPE_CLIENT=1 -DANI_BUS_TYPE_PLATFORM=1 -DANI_LITTLE_BYTE_ENDIAN -DANI_LITTLE_BIT_ENDIAN -DWLAN_STA=1 -DAP=2 -DWNI_POLARIS_FW_PRODUCT=1 -DQC_WLAN_CHIPSET_PRIMA -DINTEGRATION_READY -DVOSS_ENABLED -DDOT11F_LITTLE_ENDIAN_HOST -DGEN6_ONWARDS -DANI_COMPILER_TYPE_GCC -DANI_OS_TYPE_ANDROID=6 -DWNI_POLARIS_FW_OS=6 -DADVANCED=3 -DWNI_POLARIS_FW_PACKAGE=9 -DTRACE_RECORD -DPE_DEBUG_LOGW -DPE_DEBUG_LOGE -DDEBUG -DANI_LOGDUMP -DWLAN_PERF -DUSE_LOCKED_QUEUE -DPTT_SOCK_SVC_ENABLE -DFEATURE_WLAN_UAPSD_FW_TRG_FRAMES -DWLAN_SOFTAP_FEATURE -DWLAN_DEBUG -D__linux__ -DMSM_PLATFORM -DFEATURE_WLAN_INTEGRATED_SOC -DHAL_SELF_STA_PER_BSS=1 -DANI_MANF_DIAG -DWLAN_FEATURE_VOWIFI_11R -DWLAN_FEATURE_NEIGHBOR_ROAMING -DWLAN_FEATURE_NEIGHBOR_ROAMING_DEBUG -DWLAN_FEATURE_VOWIFI_11R_DEBUG -DFEATURE_WLAN_WAPI -DFEATURE_OEM_DATA_SUPPORT -DSOFTAP_CHANNEL_RANGE -DWLAN_AP_STA_CONCURRENCY -DFEATURE_WLAN_SCAN_PNO -DWLAN_FEATURE_PACKET_FILTERING -DWLAN_FEATURE_VOWIFI -DANI_CHIPSET_VOLANS -DWLAN_FEATURE_P2P -DWLAN_FEATURE_WFD -DWLAN_AUTOGEN_MACADDR_FEATURE -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCONFIG_CFG80211=1 -Idrivers/staging/prima_legacy/CORE/BAP/inc -Idrivers/staging/prima_legacy/CORE/BAP/src -Idrivers/staging/prima_legacy/CORE/DXE/inc -Idrivers/staging/prima_legacy/CORE/DXE/src -Idrivers/staging/prima_legacy/CORE/HDD/inc -Idrivers/staging/prima_legacy/CORE/HDD/src -Iinclude/linux -Idrivers/staging/prima_legacy/CORE/MAC/inc -Idrivers/staging/prima_legacy/CORE/MAC/src/dph -Idrivers/staging/prima_legacy/CORE/MAC/src/include -Idrivers/staging/prima_legacy/CORE/MAC/src/pe/include -Idrivers/staging/prima_legacy/CORE/MAC/src/pe/lim -Idrivers/staging/prima_legacy/riva/inc/ -Idrivers/staging/prima_legacy/CORE/SAP/inc -Idrivers/staging/prima_legacy/CORE/SAP/src -Idrivers/staging/prima_legacy/CORE/SME/inc -Idrivers/staging/prima_legacy/CORE/SME/src/csr -Idrivers/staging/prima_legacy/CORE/SVC/inc -Idrivers/staging/prima_legacy/CORE/SVC/external -Idrivers/staging/prima_legacy/CORE/SYS/common/inc -Idrivers/staging/prima_legacy/CORE/SYS/legacy/src/pal/inc -Idrivers/staging/prima_legacy/CORE/SYS/legacy/src/platform/inc -Idrivers/staging/prima_legacy/CORE/SYS/legacy/src/system/inc -Idrivers/staging/prima_legacy/CORE/SYS/legacy/src/utils/inc -Idrivers/staging/prima_legacy/CORE/TL/inc -Idrivers/staging/prima_legacy/CORE/TL/src -Idrivers/staging/prima_legacy/CORE/VOSS/inc -Idrivers/staging/prima_legacy/CORE/VOSS/src -Idrivers/staging/prima_legacy/CORE/WDA/inc -Idrivers/staging/prima_legacy/CORE/WDA/inc/legacy -Idrivers/staging/prima_legacy/CORE/WDA/src -Idrivers/staging/prima_legacy/CORE/WDI/CP/inc/ -Idrivers/staging/prima_legacy/CORE/WDI/DP/inc/ -Idrivers/staging/prima_legacy/CORE/WDI/TRP/CTS/inc/ -Idrivers/staging/prima_legacy/CORE/WDI/TRP/DTS/inc/ -Idrivers/staging/prima_legacy/CORE/WDI/WPAL/inc -w -Wframe-larger-than=4096 -O3  -DMODULE -fno-pic -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(bap_hdd_main)"  -D"KBUILD_MODNAME=KBUILD_STR(wlan)" -c -o drivers/staging/prima_legacy/CORE/HDD/src/.tmp_bap_hdd_main.o drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.c

source_drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o := drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.c

deps_drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o := \

drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o: $(deps_drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o)

$(deps_drivers/staging/prima_legacy/CORE/HDD/src/bap_hdd_main.o):