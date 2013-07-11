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
	{ 0xe35b78dd, "misc_deregister" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x65e0c700, "misc_register" },
	{ 0xd2a8caf0, "work_on_cpu" },
	{ 0xa594e333, "set_cpus_allowed_ptr" },
	{ 0xc6cbbc89, "capable" },
	{ 0x8a7d1c31, "high_memory" },
	{ 0xf4257a63, "__get_page_tail" },
	{ 0x5d2f0466, "vmalloc_to_page" },
	{ 0xa64d914a, "flush_dcache_page" },
	{ 0x2ccac4c9, "up_read" },
	{ 0xa8d79c1c, "get_user_pages" },
	{ 0x6389d4c5, "down_read" },
	{ 0x9b388444, "get_zeroed_page" },
	{ 0xc505dde9, "put_page" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xe1766a60, "up" },
	{ 0x69fbff20, "down_interruptible" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x76c6f7a2, "mem_section" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x7f58ee2a, "remap_pfn_range" },
	{ 0x6d044c26, "param_ops_uint" },
	{ 0x37a0cba, "kfree" },
	{ 0xd53cd7b5, "membank0_size" },
	{ 0x46ce1a07, "membank1_start" },
	{ 0xff088cfe, "kmalloc_caches" },
	{ 0x4302d0eb, "free_pages" },
	{ 0xbbcddc9c, "kthread_stop" },
	{ 0xdfabe0ff, "scm_call" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x93fca811, "__get_free_pages" },
	{ 0xd47e550b, "kthread_create_on_node" },
	{ 0xc3377a31, "kmem_cache_alloc_trace" },
	{ 0xeede9e9, "wake_up_process" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x77dfd55b, "__task_pid_nr_ns" },
	{ 0x9c55cec, "schedule_timeout_interruptible" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x27e1a049, "printk" },
	{ 0xd9ce8f0c, "strnlen" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

