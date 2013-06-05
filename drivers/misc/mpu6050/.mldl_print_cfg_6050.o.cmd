cmd_drivers/misc/mpu6050/mldl_print_cfg_6050.o := /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/scripts/gcc-wrapper.py /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcc -Wp,-MD,drivers/misc/mpu6050/.mldl_print_cfg_6050.o.d  -nostdinc -isystem /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/flint/src_pf2/PF2-10.4.15.1-kernel-src/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/flint/src_pf2/PF2-10.4.15.1-kernel-src/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -DASUS_SW_VER=\"A68_ENG\" -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Idrivers/misc/mpu6050 -D__C99_DESIGNATED_INITIALIZER -DINV_CACHE_DMP=1    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(mldl_print_cfg_6050)"  -D"KBUILD_MODNAME=KBUILD_STR(mpu6050)" -c -o drivers/misc/mpu6050/.tmp_mldl_print_cfg_6050.o drivers/misc/mpu6050/mldl_print_cfg_6050.c

source_drivers/misc/mpu6050/mldl_print_cfg_6050.o := drivers/misc/mpu6050/mldl_print_cfg_6050.c

deps_drivers/misc/mpu6050/mldl_print_cfg_6050.o := \
  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include/stddef.h \
  drivers/misc/mpu6050/mldl_cfg.h \
  drivers/misc/mpu6050/mltypes.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
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
  include/asm-generic/errno-base.h \
  drivers/misc/mpu6050/mlsl.h \
  include/linux/mpu_6050.h \
    $(wildcard include/config/odr/suspend.h) \
    $(wildcard include/config/odr/resume.h) \
    $(wildcard include/config/fsr/suspend.h) \
    $(wildcard include/config/fsr/resume.h) \
    $(wildcard include/config/mot/ths.h) \
    $(wildcard include/config/nmot/ths.h) \
    $(wildcard include/config/mot/dur.h) \
    $(wildcard include/config/nmot/dur.h) \
    $(wildcard include/config/irq/suspend.h) \
    $(wildcard include/config/irq/resume.h) \
    $(wildcard include/config/internal/reference.h) \
    $(wildcard include/config/num/config/keys.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/gyro.h) \
    $(wildcard include/config/accel.h) \
    $(wildcard include/config/compass.h) \
    $(wildcard include/config/pressure.h) \
  include/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  drivers/misc/mpu6050/mpu6050b1.h \
    $(wildcard include/config/value.h) \
  drivers/misc/mpu6050/log.h \
  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include/stdarg.h \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  include/linux/sysinfo.h \
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

drivers/misc/mpu6050/mldl_print_cfg_6050.o: $(deps_drivers/misc/mpu6050/mldl_print_cfg_6050.o)

$(deps_drivers/misc/mpu6050/mldl_print_cfg_6050.o):
