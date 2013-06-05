export ARCH=arm
#export PATH=~/src_Android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin:$PATH

#export CROSS_COMPILE=arm-linux-androideabi-
#echo make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- clean
#make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- clean


export CROSS_COMPILE=arm-eabi-
echo make ARCH=arm CROSS_COMPILE=arm-eabi- clean -j3
make ARCH=arm CROSS_COMPILE=arm-eabi- clean -j3
