cmd_net/sunrpc/sunrpc.o := /home/flint/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-ld -EL    -r -o net/sunrpc/sunrpc.o net/sunrpc/clnt.o net/sunrpc/xprt.o net/sunrpc/socklib.o net/sunrpc/xprtsock.o net/sunrpc/sched.o net/sunrpc/auth.o net/sunrpc/auth_null.o net/sunrpc/auth_unix.o net/sunrpc/auth_generic.o net/sunrpc/svc.o net/sunrpc/svcsock.o net/sunrpc/svcauth.o net/sunrpc/svcauth_unix.o net/sunrpc/addr.o net/sunrpc/rpcb_clnt.o net/sunrpc/timer.o net/sunrpc/xdr.o net/sunrpc/sunrpc_syms.o net/sunrpc/cache.o net/sunrpc/rpc_pipe.o net/sunrpc/svc_xprt.o net/sunrpc/stats.o net/sunrpc/sysctl.o ; scripts/mod/modpost net/sunrpc/sunrpc.o
