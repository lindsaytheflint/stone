#export ARCH=arm

#export CROSS_COMPILE=arm-linux-androideabi-
#echo make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic
#make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic

#export CROSS_COMPILE=arm-eabi-
#echo make ARCH=arm CROSS_COMPILE=arm-eabi- menuconfig
#make ARCH=arm CROSS_COMPILE=arm-eabi- menuconfig

make ARCH=arm CROSS_COMPILE=~/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.7/bin/arm-linux-androideabi- menuconfig

