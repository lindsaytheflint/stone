cmd_fs/nls/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o fs/nls/built-in.o fs/nls/nls_base.o fs/nls/nls_cp437.o fs/nls/nls_ascii.o fs/nls/nls_iso8859-1.o fs/nls/nls_utf8.o ; scripts/mod/modpost fs/nls/built-in.o