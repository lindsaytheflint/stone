cmd_drivers/mmc/card/mmc_block.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/mmc/card/mmc_block.o drivers/mmc/card/block.o drivers/mmc/card/queue.o ; scripts/mod/modpost drivers/mmc/card/mmc_block.o