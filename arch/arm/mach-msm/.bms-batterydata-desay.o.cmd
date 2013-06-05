cmd_arch/arm/mach-msm/bms-batterydata-desay.o := /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/scripts/gcc-wrapper.py /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcc -Wp,-MD,arch/arm/mach-msm/.bms-batterydata-desay.o.d  -nostdinc -isystem /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -DASUS_SW_VER=\"A68_ENG\" -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(bms_batterydata_desay)"  -D"KBUILD_MODNAME=KBUILD_STR(bms_batterydata_desay)" -c -o arch/arm/mach-msm/.tmp_bms-batterydata-desay.o arch/arm/mach-msm/bms-batterydata-desay.c

source_arch/arm/mach-msm/bms-batterydata-desay.o := arch/arm/mach-msm/bms-batterydata-desay.c

deps_arch/arm/mach-msm/bms-batterydata-desay.o := \
  include/linux/mfd/pm8xxx/pm8921-bms.h \
    $(wildcard include/config/pm8921/bms.h) \
  include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \

arch/arm/mach-msm/bms-batterydata-desay.o: $(deps_arch/arm/mach-msm/bms-batterydata-desay.o)

$(deps_arch/arm/mach-msm/bms-batterydata-desay.o):
