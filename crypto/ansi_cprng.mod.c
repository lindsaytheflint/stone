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
	{ 0x2593d91c, "crypto_rng_type" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x791c5258, "crypto_unregister_alg" },
	{ 0xa54943be, "crypto_register_alg" },
	{ 0x80dd5d90, "crypto_alloc_base" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0xfa4ebdd6, "_raw_spin_unlock_bh" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xf6432d52, "_raw_spin_lock_bh" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x71c90087, "memcmp" },
	{ 0x9d669763, "memcpy" },
	{ 0x4059792f, "print_hex_dump" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x8c49a44c, "crypto_destroy_tfm" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

