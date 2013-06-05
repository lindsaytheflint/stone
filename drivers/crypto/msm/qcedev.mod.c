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
	{ 0x226f9bff, "platform_driver_unregister" },
	{ 0xa6b1a724, "platform_driver_register" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xf9318674, "__init_waitqueue_head" },
	{ 0x528c709d, "simple_read_from_buffer" },
	{ 0xad1f1c2a, "debugfs_remove_recursive" },
	{ 0xfc186c34, "debugfs_create_file" },
	{ 0x45b0fc5b, "debugfs_create_dir" },
	{ 0xb81960ca, "snprintf" },
	{ 0x4f7b0e59, "complete" },
	{ 0x1bcefad4, "misc_register" },
	{ 0xc3593841, "msm_bus_scale_register_client" },
	{ 0x544253c4, "qce_hw_support" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0x10fa6f85, "qce_open" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0x76c6f7a2, "mem_section" },
	{ 0xd53cd7b5, "membank0_size" },
	{ 0x46ce1a07, "membank1_start" },
	{ 0xcda02189, "put_pmem_file" },
	{ 0x37a0cba, "kfree" },
	{ 0x198636b3, "get_pmem_file" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xcc9ce6d7, "wait_for_completion" },
	{ 0x9cd9dce, "_raw_spin_unlock_irqrestore" },
	{ 0x56f31e92, "_raw_spin_lock_irqsave" },
	{ 0xad90232b, "qce_process_sha_req" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x9d669763, "memcpy" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xb03f0e17, "qce_ablk_cipher_req" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xdfabe0ff, "scm_call" },
	{ 0x7a4497db, "kzfree" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x27e1a049, "printk" },
	{ 0x78f062cb, "msm_bus_scale_client_update_request" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0x82072614, "tasklet_kill" },
	{ 0x77294755, "misc_deregister" },
	{ 0xcf8cc5ee, "msm_bus_scale_unregister_client" },
	{ 0x575c81e1, "qce_close" },
	{ 0x6b8b79e7, "dev_get_drvdata" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=qce40";


MODULE_INFO(srcversion, "B7D860EB68A8FBF6BE8C675");
