cmd_drivers/mmc/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/mmc/built-in.o drivers/mmc/core/built-in.o drivers/mmc/card/built-in.o drivers/mmc/host/built-in.o ; scripts/mod/modpost drivers/mmc/built-in.o