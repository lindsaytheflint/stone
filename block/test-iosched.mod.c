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
	{ 0x7b19b6a5, "module_layout" },
	{ 0xd05ae41c, "elv_unregister" },
	{ 0x62c2c99f, "elv_register" },
	{ 0x14086116, "init_request_from_bio" },
	{ 0x67cca5ae, "bio_alloc" },
	{ 0x860425b4, "bio_put" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x9acbff0a, "blk_rq_map_kern" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x4db2548f, "blk_get_request" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x7d11c268, "jiffies" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0x2824f314, "finish_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x76bff920, "prepare_to_wait" },
	{ 0x5f754e5a, "memset" },
	{ 0x6f14d00e, "__blk_run_queue" },
	{ 0x8834396c, "mod_timer" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x9d669763, "memcpy" },
	{ 0xf9a482f9, "msleep" },
	{ 0x37a0cba, "kfree" },
	{ 0x78c0a571, "blk_put_request" },
	{ 0x1adb62a4, "_raw_spin_unlock" },
	{ 0x84741c31, "_raw_spin_lock" },
	{ 0x287fc114, "elv_dispatch_sort" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x44b4693d, "__wake_up" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0xf9318674, "__init_waitqueue_head" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0xad1f1c2a, "debugfs_remove_recursive" },
	{ 0x3e47f90b, "debugfs_create_u32" },
	{ 0x45b0fc5b, "debugfs_create_dir" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

