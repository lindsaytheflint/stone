cmd_net/built-in.o :=  /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o net/built-in.o net/socket.o net/core/built-in.o net/ethernet/built-in.o net/802/built-in.o net/sched/built-in.o net/netlink/built-in.o net/netfilter/built-in.o net/ipv4/built-in.o net/xfrm/built-in.o net/unix/built-in.o net/ipv6/built-in.o net/packet/built-in.o net/key/built-in.o net/bluetooth/built-in.o net/sunrpc/built-in.o net/wireless/built-in.o net/rfkill/built-in.o net/sysctl_net.o net/dns_resolver/built-in.o net/activity_stats.o ; scripts/mod/modpost net/built-in.o