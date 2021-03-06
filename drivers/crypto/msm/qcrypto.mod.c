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
	{ 0x631b413d, "crypto_aead_type" },
	{ 0xeaab72e5, "crypto_ahash_type" },
	{ 0xf58542df, "crypto_ablkcipher_type" },
	{ 0x790b57dc, "platform_driver_unregister" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x784fbacc, "platform_driver_register" },
	{ 0xf9318674, "__init_waitqueue_head" },
	{ 0x528c709d, "simple_read_from_buffer" },
	{ 0xb2422a9, "debugfs_remove_recursive" },
	{ 0xa853328d, "debugfs_create_file" },
	{ 0x27dd566b, "debugfs_create_dir" },
	{ 0xb81960ca, "snprintf" },
	{ 0x86de10c0, "crypto_register_ahash" },
	{ 0xcd934a25, "_dev_info" },
	{ 0xa099e649, "dev_err" },
	{ 0xa54943be, "crypto_register_alg" },
	{ 0xc3593841, "msm_bus_scale_register_client" },
	{ 0x544253c4, "qce_hw_support" },
	{ 0x499043d3, "crypto_init_queue" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0x84164b42, "dev_set_drvdata" },
	{ 0xf2dd8cd8, "qce_open" },
	{ 0xcfd9a2c0, "des_ekey" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x4f7b0e59, "complete" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x78f062cb, "msm_bus_scale_client_update_request" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0xa820fd00, "wait_for_completion_interruptible" },
	{ 0xa1fe82ed, "crypto_enqueue_request" },
	{ 0x76c6f7a2, "mem_section" },
	{ 0xd53cd7b5, "membank0_size" },
	{ 0x46ce1a07, "membank1_start" },
	{ 0xbe917b8a, "qce_aead_req" },
	{ 0xad90232b, "qce_process_sha_req" },
	{ 0xb03f0e17, "qce_ablk_cipher_req" },
	{ 0x6b13be2f, "crypto_dequeue_request" },
	{ 0xd5152710, "sg_next" },
	{ 0xbaec3d71, "page_address" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0x27e1a049, "printk" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x8949858b, "schedule_work" },
	{ 0x71c90087, "memcmp" },
	{ 0x5f754e5a, "memset" },
	{ 0x91dda801, "scatterwalk_map_and_copy" },
	{ 0x7a4497db, "kzfree" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x9d669763, "memcpy" },
	{ 0x9cd9dce, "_raw_spin_unlock_irqrestore" },
	{ 0x56f31e92, "_raw_spin_lock_irqsave" },
	{ 0xdfabe0ff, "scm_call" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x82072614, "tasklet_kill" },
	{ 0x575c81e1, "qce_close" },
	{ 0x37a0cba, "kfree" },
	{ 0x5ff3a021, "crypto_unregister_ahash" },
	{ 0x791c5258, "crypto_unregister_alg" },
	{ 0xcf8cc5ee, "msm_bus_scale_unregister_client" },
	{ 0x2a87e02e, "dev_get_drvdata" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=qce40";


MODULE_INFO(srcversion, "D47ACD5E22578E7A8A7FAEA");
