cmd_drivers/media/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/media/built-in.o drivers/media/media.o drivers/media/common/built-in.o drivers/media/rc/built-in.o drivers/media/video/built-in.o drivers/media/radio/built-in.o ; scripts/mod/modpost drivers/media/built-in.o
