cmd_drivers/input/misc/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/input/misc/built-in.o drivers/input/misc/uinput.o ; scripts/mod/modpost drivers/input/misc/built-in.o