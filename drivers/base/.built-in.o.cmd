cmd_drivers/base/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/base/built-in.o drivers/base/core.o drivers/base/bus.o drivers/base/dd.o drivers/base/syscore.o drivers/base/driver.o drivers/base/class.o drivers/base/platform.o drivers/base/cpu.o drivers/base/firmware.o drivers/base/init.o drivers/base/map.o drivers/base/devres.o drivers/base/attribute_container.o drivers/base/transport_class.o drivers/base/topology.o drivers/base/sys.o drivers/base/power/built-in.o drivers/base/dma-mapping.o drivers/base/dma-coherent.o drivers/base/dma-buf.o drivers/base/genlock.o drivers/base/firmware_class.o drivers/base/module.o drivers/base/regmap/built-in.o ; scripts/mod/modpost drivers/base/built-in.o
