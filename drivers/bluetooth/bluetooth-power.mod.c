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
	{ 0x4cabed9, "rfkill_register" },
	{ 0xaad6d92f, "rfkill_init_sw_state" },
	{ 0x872de711, "dev_err" },
	{ 0x87b98146, "rfkill_alloc" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0xdb68bbad, "rfkill_destroy" },
	{ 0x83eb21c, "rfkill_unregister" },
	{ 0x6b8b79e7, "dev_get_drvdata" },
	{ 0x7583dd9d, "__dynamic_dev_dbg" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5135EFD2BE07BA9DA21C97E");
