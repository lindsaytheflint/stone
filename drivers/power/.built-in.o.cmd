cmd_drivers/power/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/power/built-in.o drivers/power/power_supply.o drivers/power/isl9519q.o drivers/power/smb349.o drivers/power/pm8xxx-ccadc.o drivers/power/pm8921-bms.o drivers/power/pm8921-charger.o drivers/power/asus_bat.o drivers/power/charger/built-in.o drivers/power/gauge/built-in.o drivers/power/capfilter/built-in.o drivers/power/fsm/built-in.o drivers/power/util/built-in.o drivers/power/service/built-in.o ; scripts/mod/modpost drivers/power/built-in.o
