cmd_net/bluetooth/bnep/bnep.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o net/bluetooth/bnep/bnep.o net/bluetooth/bnep/core.o net/bluetooth/bnep/sock.o net/bluetooth/bnep/netdev.o ; scripts/mod/modpost net/bluetooth/bnep/bnep.o