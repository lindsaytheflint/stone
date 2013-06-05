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
	{ 0x6d044c26, "param_ops_uint" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x25f366dc, "no_llseek" },
	{ 0x3ac3c368, "device_unregister" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x556acb67, "class_destroy" },
	{ 0x81a61ed0, "driver_unregister" },
	{ 0xc5a9ef1e, "spi_new_device" },
	{ 0x4d891bde, "spi_busnum_to_master" },
	{ 0x6743a5d8, "spi_register_driver" },
	{ 0x2c1ef9fb, "__class_create" },
	{ 0x851bb3f8, "__register_chrdev" },
	{ 0xa45f7a1c, "put_device" },
	{ 0x8debb213, "spi_setup" },
	{ 0xd29b3c9f, "get_device" },
	{ 0x4f7b0e59, "complete" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xcc9ce6d7, "wait_for_completion" },
	{ 0x5a847dc8, "spi_async" },
	{ 0x9d669763, "memcpy" },
	{ 0x5f754e5a, "memset" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x5b105777, "nonseekable_open" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x7583dd9d, "__dynamic_dev_dbg" },
	{ 0xb3d2ee52, "device_create" },
	{ 0xd3dbfbc4, "_find_first_zero_bit_le" },
	{ 0x1a1962a9, "__mutex_init" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x37a0cba, "kfree" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x362825af, "device_destroy" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0xf7a424d2, "_raw_spin_unlock_irq" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0x1d7d6e7b, "_raw_spin_lock_irq" },
	{ 0x6b8b79e7, "dev_get_drvdata" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

