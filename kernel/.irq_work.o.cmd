cmd_kernel/irq_work.o := /home/flint/src_pf2/StoneK_10.4.16.8/scripts/gcc-wrapper.py /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcc -Wp,-MD,kernel/.irq_work.o.d  -nostdinc -isystem /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include -I/home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include /home/flint/src_pf2/StoneK_10.4.16.8/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -DASUS_SW_VER=\"A68_ENG\" -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fomit-frame-pointer -fno-inline-functions-called-once -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(irq_work)"  -D"KBUILD_MODNAME=KBUILD_STR(irq_work)" -c -o kernel/.tmp_irq_work.o kernel/irq_work.c

source_kernel/irq_work.o := kernel/irq_work.c

deps_kernel/irq_work.o := \
  include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  include/linux/linkage.h \
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
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/linkage.h \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
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
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/posix_types.h \
  include/asm-generic/posix_types.h \
  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/../lib/gcc/arm-linux-androideabi/4.6.x-google/include/stdarg.h \
  include/linux/bitops.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/bitops.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/irqflags.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/swab.h \
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
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/div64.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/compiler.h \
  include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  include/linux/irq_work.h \
  include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/asm-generic/cmpxchg-local.h \
  include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/domain.h \
    $(wildcard include/config/verify/permission/fault.h) \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
    $(wildcard include/config/emulate/domain/manager/v7.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/const.h \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  include/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/string.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/smp.h \
  include/linux/pfn.h \
  arch/arm/include/generated/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  include/linux/hardirq.h \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/hardirq.h \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/irq.h \
    $(wildcard include/config/sparse/irq.h) \
  arch/arm/mach-msm/include/mach/irqs.h \
    $(wildcard include/config/arch/msm8960.h) \
    $(wildcard include/config/arch/apq8064.h) \
    $(wildcard include/config/arch/msm8930.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/arch/msm8974.h) \
    $(wildcard include/config/arch/msm9615.h) \
    $(wildcard include/config/arch/msm9625.h) \
    $(wildcard include/config/arch/msm7x30.h) \
    $(wildcard include/config/arch/qsd8x50.h) \
    $(wildcard include/config/arch/msm8x60.h) \
    $(wildcard include/config/arch/msm7x01a.h) \
    $(wildcard include/config/arch/msm7x25.h) \
    $(wildcard include/config/arch/msm7x27.h) \
    $(wildcard include/config/arch/fsm9xxx.h) \
    $(wildcard include/config/msm/pcie.h) \
  arch/arm/mach-msm/include/mach/irqs-8625.h \
  arch/arm/mach-msm/include/mach/irqs-8960.h \
  arch/arm/mach-msm/include/mach/irqs-8930.h \
  arch/arm/mach-msm/include/mach/irqs-8064.h \
  include/linux/irq_cpustat.h \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/flint/src_pf2/StoneK_10.4.16.8/arch/arm/include/asm/hw_breakpoint.h \

kernel/irq_work.o: $(deps_kernel/irq_work.o)

$(deps_kernel/irq_work.o):
