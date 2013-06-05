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
	{ 0xa31a8580, "smd_close" },
	{ 0x4b3eddf2, "radio_hci_register_dev" },
	{ 0x426e2ee2, "smd_disable_read_intr" },
	{ 0x774408a6, "smd_named_open_on_edge" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0x8949858b, "schedule_work" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0x53296091, "smd_read" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x64dc388f, "smd_read_avail" },
	{ 0x82be1d65, "kfree_skb" },
	{ 0x5019e598, "smd_write" },
	{ 0xbba882d8, "radio_hci_unregister_dev" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x37a0cba, "kfree" },
	{ 0x698983a8, "radio_hci_recv_frame" },
	{ 0x84abd419, "skb_put" },
	{ 0x27e1a049, "printk" },
	{ 0x98fa50fc, "__alloc_skb" },
	{ 0x9d669763, "memcpy" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";
