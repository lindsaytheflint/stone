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
	{ 0x27e1a049, "printk" },
	{ 0x2c1ef9fb, "__class_create" },
	{ 0x556acb67, "class_destroy" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0x5934392b, "fb_register_client" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x683e927d, "device_register" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0x72ca9bd1, "dev_set_name" },
	{ 0x1a1962a9, "__mutex_init" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x3ac3c368, "device_unregister" },
	{ 0xcc36f32e, "fb_unregister_client" },
	{ 0xf087137d, "__dynamic_pr_debug" },
	{ 0x996bdb64, "_kstrtoul" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x91715312, "sprintf" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

