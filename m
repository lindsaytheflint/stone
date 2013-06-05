#export ARCH=arm

#export CROSS_COMPILE=arm-linux-androideabi-
#echo make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 -w
#make ARCH=arm CROSS_COMPILE=arm-linux-androideabi- -j3 -w

#CFLAGS_MODULE=-fno-pic

#export CROSS_COMPILE=arm-eabi-
#echo make ARCH=arm CROSS_COMPILE=arm-eabi- -j3 -w
#make ARCH=arm CROSS_COMPILE=arm-eabi- -j3 -w 

rm arch/arm/boot/zImage

echo make ARCH=arm CROSS_COMPILE=~/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi- CFLAGS_MODULE=-fno-pic -j8 -w
make ARCH=arm CROSS_COMPILE=~/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi- CFLAGS_MODULE=-fno-pic -j8 -w CONFIG_DEBUG_SECTION_MISMATCH=y


#make ARCH=arm CROSS_COMPILE=~/android/prebuilts/gcc/linux-x86/arm/arm-eabi-4.7/bin/arm-eabi- CFLAGS_MODULE=-fno-pic -j8 -w 



#CONFIG_NO_ERROR_ON_MISMATCH=y

echo "checking for compiled kernel..."
if [ -f arch/arm/boot/zImage ]
then

sudo rm ~/0_Image/boot.img
sudo rm ~/0_Image/zImage
sudo cp arch/arm/boot/zImage ~/0_Image/
~/0_Image/b

sudo cp drivers/staging/prima_legacy/wlan.ko ~/0_Image/prima_wlan.ko
sudo cp drivers/staging/prima/wlan.ko ~/0_Image/prima_wlan.ko
sudo cp net/wireless/cfg80211.ko ~/0_Image/

mkdir ~/0_Image/Flashable/StoneK_A68_v0.6/
cd ~/0_Image/Flashable/StoneK_A68_v0.6/
sudo cp ~/0_Image/prima_wlan.ko ~/0_Image/Flashable/StoneK_A68_v0.6/system/lib/modules/prima/
sudo cp ~/0_Image/cfg80211.ko ~/0_Image/Flashable/StoneK_A68_v0.6/system/lib/modules/prima/
sudo cp ~/0_Image/boot.img ~/0_Image/Flashable/StoneK_A68_v0.6/
sudo rm ~/0_Image/Flashable/StoneK_A68_v0.6.zip
sudo zip -ro9 ~/0_Image/Flashable/StoneK_A68_v0.6.zip *
cd $OLDPWD

~/android/out/host/linux-x86/obj/EXECUTABLES/adb_intermediates/adb push ~/0_Image/Flashable/StoneK_A68_v0.6.zip /sdcard/StoneK_A68_v0.6.zip
~/android/out/host/linux-x86/obj/EXECUTABLES/adb_intermediates/adb reboot recovery

fi
