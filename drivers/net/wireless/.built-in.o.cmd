cmd_drivers/net/wireless/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/net/wireless/built-in.o drivers/net/wireless/wcnss/built-in.o ; scripts/mod/modpost drivers/net/wireless/built-in.o