cmd_drivers/coresight/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/coresight/built-in.o drivers/coresight/coresight.o drivers/coresight/coresight-etb.o drivers/coresight/coresight-tpiu.o drivers/coresight/coresight-funnel.o drivers/coresight/coresight-stm.o drivers/coresight/coresight-etm.o ; scripts/mod/modpost drivers/coresight/built-in.o
