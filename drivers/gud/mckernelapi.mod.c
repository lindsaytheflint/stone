#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x78ec5434, "module_layout" },
	{ 0xf8b58a67, "netlink_unicast" },
	{ 0xf0a6d312, "__nlmsg_put" },
	{ 0x9eb89c70, "__alloc_skb" },
	{ 0xe1766a60, "up" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x7ce5f400, "mutex_lock_interruptible" },
	{ 0x49d9fb1e, "down_timeout" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x823dcf75, "kfree_skb" },
	{ 0x1a1962a9, "__mutex_init" },
	{ 0x15d21d26, "mobicore_map_vmem" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x97538ac9, "mobicore_unmap_vmem" },
	{ 0x3ea9a9fd, "mobicore_free" },
	{ 0x40d5ee41, "mobicore_allocate_wsm" },
	{ 0xa46b6273, "mobicore_release" },
	{ 0x666f8c6a, "mobicore_open" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x9d669763, "memcpy" },
	{ 0x5f754e5a, "memset" },
	{ 0x37a0cba, "kfree" },
	{ 0x717a61f4, "netlink_kernel_release" },
	{ 0xaef1eb52, "init_net" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0x634b9b40, "netlink_kernel_create" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x69b40673, "netlink_ack" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mcdrvmodule";

