cmd_drivers/media/common/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/media/common/built-in.o drivers/media/common/tuners/built-in.o ; scripts/mod/modpost drivers/media/common/built-in.o