cmd_drivers/input/input-core.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/input/input-core.o drivers/input/input.o drivers/input/input-compat.o drivers/input/input-mt.o drivers/input/ff-core.o ; scripts/mod/modpost drivers/input/input-core.o
