export ARCH=arm

#export CROSS_COMPILE=arm-linux-androideabi-
#echo make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic
#make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 CFLAGS_MODULE=-fno-pic

export CROSS_COMPILE=arm-eabi-
#echo make ARCH=arm CROSS_COMPILE=arm-eabi- msm8960-perf_defconfig
#make ARCH=arm CROSS_COMPILE=arm-eabi- msm8960-perf_defconfig

echo make ARCH=arm CROSS_COMPILE=arm-eabi- msm8960-userdebug_defconfig
make ARCH=arm CROSS_COMPILE=arm-eabi- msm8960-userdebug_defconfig

