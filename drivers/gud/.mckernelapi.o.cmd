cmd_drivers/gud/mckernelapi.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/gud/mckernelapi.o drivers/gud/mobicore_kernelapi/main.o drivers/gud/mobicore_kernelapi/clientlib.o drivers/gud/mobicore_kernelapi/device.o drivers/gud/mobicore_kernelapi/session.o drivers/gud/mobicore_kernelapi/connection.o ; scripts/mod/modpost drivers/gud/mckernelapi.o