cmd_drivers/input/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/input/built-in.o drivers/input/input-core.o drivers/input/mousedev.o drivers/input/joydev.o drivers/input/evdev.o drivers/input/keyboard/built-in.o drivers/input/mouse/built-in.o drivers/input/joystick/built-in.o drivers/input/touchscreen/built-in.o drivers/input/misc/built-in.o drivers/input/rmi4/built-in.o ; scripts/mod/modpost drivers/input/built-in.o
