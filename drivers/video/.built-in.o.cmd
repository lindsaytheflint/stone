cmd_drivers/video/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o drivers/video/built-in.o drivers/video/fb_notify.o drivers/video/fb.o drivers/video/console/built-in.o drivers/video/backlight/built-in.o drivers/video/cfbfillrect.o drivers/video/cfbcopyarea.o drivers/video/cfbimgblt.o drivers/video/sysfillrect.o drivers/video/syscopyarea.o drivers/video/sysimgblt.o drivers/video/fb_sys_fops.o drivers/video/omap2/built-in.o drivers/video/msm/built-in.o drivers/video/vfb.o ; scripts/mod/modpost drivers/video/built-in.o
