cmd_drivers/usb/gadget/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/usb/gadget/built-in.o drivers/usb/gadget/udc-core.o drivers/usb/gadget/ci13xxx_msm.o drivers/usb/gadget/g_android.o ; scripts/mod/modpost drivers/usb/gadget/built-in.o