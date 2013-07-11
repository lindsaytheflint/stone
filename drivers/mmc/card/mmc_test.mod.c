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
	{ 0x66cce43, "single_release" },
	{ 0x308b5970, "seq_read" },
	{ 0x67a03645, "seq_lseek" },
	{ 0x59fb1344, "mmc_unregister_driver" },
	{ 0x2a473f11, "mmc_register_driver" },
	{ 0x1424f59, "sg_copy_to_buffer" },
	{ 0x8371daff, "sg_copy_from_buffer" },
	{ 0x4b6abfe3, "mmc_start_req" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x66b2a859, "nr_free_buffer_pages" },
	{ 0xcd934a25, "_dev_info" },
	{ 0xefdd2345, "sg_init_one" },
	{ 0xd2c199a9, "mmc_set_blocklen" },
	{ 0x3c40da43, "mmc_can_trim" },
	{ 0x46608fa0, "getnstimeofday" },
	{ 0x4d40b3f8, "mmc_wait_for_req" },
	{ 0x79eef28e, "mmc_erase" },
	{ 0x5019b3cb, "mmc_can_erase" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x99f02115, "debugfs_remove" },
	{ 0xa099e649, "dev_err" },
	{ 0xa853328d, "debugfs_create_file" },
	{ 0x3a042c38, "contig_page_data" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x489f5864, "__alloc_pages_nodemask" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x11a13e31, "_kstrtol" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x735bd21e, "mmc_release_host" },
	{ 0xe5290631, "__mmc_claim_host" },
	{ 0x37a0cba, "kfree" },
	{ 0xb57ef54f, "__free_pages" },
	{ 0xe6da44a, "set_normalized_timespec" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0x59e5070d, "__do_div64" },
	{ 0x27e1a049, "printk" },
	{ 0xdbcf09cb, "mmc_wait_for_cmd" },
	{ 0x5f754e5a, "memset" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x2c17289d, "mmc_set_data_timeout" },
	{ 0xd53cd7b5, "membank0_size" },
	{ 0x46ce1a07, "membank1_start" },
	{ 0x76c6f7a2, "mem_section" },
	{ 0xd5152710, "sg_next" },
	{ 0xbaec3d71, "page_address" },
	{ 0xf88c3301, "sg_init_table" },
	{ 0x6d6e057f, "mmc_can_reset" },
	{ 0xd2a38810, "mmc_hw_reset_check" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0xa3a75f19, "seq_printf" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0x18f76244, "single_open" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

