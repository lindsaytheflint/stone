cmd_drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o := /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/scripts/gcc-wrapper.py /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcc -Wp,-MD,drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/.si_drv_infoframe.o.d  -nostdinc -isystem /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -DASUS_SW_VER=\"A68_ENG\" -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Idrivers/video/msm/mhl8240/include -Idrivers/video/msm/mhl8240/platform -Idrivers/video/msm/mhl8240/platform/api -Idrivers/video/msm/mhl8240/platform/hal -Idrivers/video/msm/mhl8240/component/mhl2_tx -Idrivers/video/msm/mhl8240/component/hdmi_tx_lite_mhl2 -Idrivers/video/msm/mhl8240/driver/cra_drv -Idrivers/video/msm/mhl8240/driver/sii8240_drv -Idrivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240 -Idrivers/video/msm/mhl8240/driver/mhl2_tx_drv -Idrivers/video/msm/mhl8240/linux_kernel/kernel_module -Idrivers/video/msm/mhl8240/platform/include -DMAKE_8240_DRIVER -DBUILDNUM=0 -DC99_VA_ARG_SUPPORT -DSII8240_NO_TRANSCODE_MODE -DSII8240_VER68 -DSII8240_PM_SUPPORT    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(si_drv_infoframe)"  -D"KBUILD_MODNAME=KBUILD_STR(sii8240drv)" -c -o drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/.tmp_si_drv_infoframe.o drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.c

source_drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o := drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.c

deps_drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o := \
  drivers/video/msm/mhl8240/platform/include/si_memsegsupport.h \
  drivers/video/msm/mhl8240/include/si_common.h \
  drivers/video/msm/mhl8240/include/si_buildflags.h \
    $(wildcard include/config/resource/constrained.h) \
  drivers/video/msm/mhl8240/platform/include/si_c99support.h \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/sysinfo.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/posix_types.h \
  include/asm-generic/posix_types.h \
  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include/stdarg.h \
  include/linux/linkage.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/linkage.h \
  include/linux/bitops.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/irqflags.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/dynamic_debug.h \
  include/linux/asusdebug.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/div64.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/compiler.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  drivers/video/msm/mhl8240/platform/api/si_osdebug.h \
    $(wildcard include/config/no/file/line.h) \
  drivers/video/msm/mhl8240/include/si_app_gpio.h \
  drivers/video/msm/mhl8240/include/si_app_devcap.h \
  drivers/video/msm/mhl8240/platform/include/si_platform_gpio.h \
  drivers/video/msm/mhl8240/include/si_timer_cfg.h \
  drivers/video/msm/mhl8240/platform/api/si_bitdefs.h \
  drivers/video/msm/mhl8240/component/mhl2_tx/si_infoframe.h \
  drivers/video/msm/mhl8240/platform/hal/sii_hal.h \
  drivers/video/msm/mhl8240/platform/include/si_platform.h \
  drivers/video/msm/mhl8240/driver/cra_drv/si_cra.h \
  drivers/video/msm/mhl8240/driver/sii8240_drv/si_cra_cfg.h \
  drivers/video/msm/mhl8240/include/si_common_regs.h \
  drivers/video/msm/mhl8240/driver/sii8240_drv/si_8240_regs.h \
  drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_tpi_regs.h \
    $(wildcard include/config/3/audio/interface/mask.h) \
    $(wildcard include/config/3/audio/interface/disabled.h) \
    $(wildcard include/config/3/audio/interface/spdif.h) \
    $(wildcard include/config/3/audio/interface/i2s.h) \
    $(wildcard include/config/3/audio/interface/hd/audio.h) \
  drivers/video/msm/mhl8240/component/mhl2_tx/si_mhl_defs.h \
  drivers/video/msm/mhl8240/component/mhl2_tx/si_mhl_tx_base_drv_api.h \
  drivers/video/msm/mhl8240/component/hdmi_tx_lite_mhl2/si_hdmi_tx_lite_api.h \
  drivers/video/msm/mhl8240/include/si_app_devcap.h \
  drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_hdmi_tx_lite_edid.h \
  include/linux/delay.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/delay.h \
  /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \

drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o: $(deps_drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o)

$(deps_drivers/video/msm/mhl8240/driver/hdmi_tx_lite_drv_8240/si_drv_infoframe.o):
