cmd_drivers/net/phy/libphy.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/net/phy/libphy.o drivers/net/phy/phy.o drivers/net/phy/phy_device.o drivers/net/phy/mdio_bus.o ; scripts/mod/modpost drivers/net/phy/libphy.o
