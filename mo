export ARCH=arm

#export CROSS_COMPILE=arm-linux-androideabi-
#echo make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic
#make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic

export CROSS_COMPILE=arm-eabi-
echo make ARCH=arm CROSS_COMPILE=arm-eabi- -j2 modules
make ARCH=arm CROSS_COMPILE=arm-eabi- -j2 modules


sudo cp arch/arm/boot/zImage ~/0_Image/
~/0_Image/b

