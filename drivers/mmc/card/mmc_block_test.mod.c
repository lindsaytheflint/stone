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
	{ 0x37a0cba, "kfree" },
	{ 0xfa799e30, "test_iosched_unregister" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0xf0372292, "test_iosched_register" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0xd9ce8f0c, "strnlen" },
	{ 0xb81960ca, "snprintf" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xa853328d, "debugfs_create_file" },
	{ 0xa064fe47, "debugfs_create_u32" },
	{ 0x77613892, "test_iosched_get_debugfs_tests_root" },
	{ 0x1bc1f7f2, "test_iosched_get_debugfs_utils_root" },
	{ 0x99f02115, "debugfs_remove" },
	{ 0xba5a86c6, "test_iosched_add_unique_test_req" },
	{ 0x37e74642, "get_jiffies_64" },
	{ 0xc7d70b42, "test_iosched_add_wr_rd_test_req" },
	{ 0x871803f0, "mmc_blk_init_packed_statistics" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x65043b59, "test_iosched_set_ignore_round" },
	{ 0x7c8e176, "print_mmc_packing_stats" },
	{ 0x1adb62a4, "_raw_spin_unlock" },
	{ 0x84741c31, "_raw_spin_lock" },
	{ 0x83c76b2c, "mmc_blk_get_packed_statistics" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0xf9a482f9, "msleep" },
	{ 0xa4956fea, "test_iosched_start_test" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x20c55ae0, "sscanf" },
	{ 0x76aa5377, "test_iosched_set_test_result" },
	{ 0x771e94e1, "test_iosched_get_req_queue" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=test-iosched";

