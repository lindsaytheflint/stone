cmd_block/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o block/built-in.o block/elevator.o block/blk-core.o block/blk-tag.o block/blk-sysfs.o block/blk-flush.o block/blk-settings.o block/blk-ioc.o block/blk-map.o block/blk-exec.o block/blk-merge.o block/blk-softirq.o block/blk-timeout.o block/blk-iopoll.o block/blk-lib.o block/ioctl.o block/genhd.o block/scsi_ioctl.o block/partition-generic.o block/partitions/built-in.o block/bsg.o block/noop-iosched.o block/deadline-iosched.o block/cfq-iosched.o block/sio-iosched.o ; scripts/mod/modpost block/built-in.o