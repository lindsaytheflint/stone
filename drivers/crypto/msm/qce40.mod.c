#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x78ec5434, "module_layout" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xb669788e, "dma_map_sg" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x9d669763, "memcpy" },
	{ 0xd5152710, "sg_next" },
	{ 0x1083fb9d, "dma_unmap_sg" },
	{ 0xcd934a25, "_dev_info" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0xea85e9a4, "msm_dmov_enqueue_cmd" },
	{ 0x14e4a47f, "clk_reset" },
	{ 0xfbfea7f7, "clk_enable" },
	{ 0x177dc17c, "clk_prepare" },
	{ 0x3baa8f87, "clk_set_rate" },
	{ 0x63bbd7c2, "clk_get" },
	{ 0x666f989, "dma_alloc_coherent" },
	{ 0x4f37e64b, "platform_get_resource_byname" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xec63a615, "platform_get_resource" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xa099e649, "dev_err" },
	{ 0x37a0cba, "kfree" },
	{ 0x2e1ca751, "clk_put" },
	{ 0xab4fa1f4, "clk_unprepare" },
	{ 0xa8477cad, "clk_disable" },
	{ 0xfa31204, "dma_free_coherent" },
	{ 0xc2165d85, "__arm_iounmap" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "48E2FF104E07D2FAEE85546");
