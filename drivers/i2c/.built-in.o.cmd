cmd_drivers/i2c/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/i2c/built-in.o drivers/i2c/i2c-boardinfo.o drivers/i2c/i2c-core.o drivers/i2c/i2c-dev.o drivers/i2c/algos/built-in.o drivers/i2c/busses/built-in.o drivers/i2c/muxes/built-in.o drivers/i2c/i2c-stresstest.o ; scripts/mod/modpost drivers/i2c/built-in.o
