cmd_fs/fat/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o fs/fat/built-in.o fs/fat/fat.o fs/fat/vfat.o fs/fat/msdos.o ; scripts/mod/modpost fs/fat/built-in.o