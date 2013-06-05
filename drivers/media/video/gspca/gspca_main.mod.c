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
	{ 0x46f5213a, "video_ioctl2" },
	{ 0x49dbd601, "kmalloc_caches" },
	{ 0xdaa8e9b6, "__video_register_device" },
	{ 0xf9318674, "__init_waitqueue_head" },
	{ 0x1a1962a9, "__mutex_init" },
	{ 0x8ba9d67, "kmem_cache_alloc_trace" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x9dc25acd, "input_free_device" },
	{ 0x47feb66d, "input_register_device" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xa953b19c, "input_allocate_device" },
	{ 0x4cdb3178, "ns_to_timeval" },
	{ 0xc87c1f84, "ktime_get" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x746e450a, "vm_insert_page" },
	{ 0x50ff165f, "vmalloc_to_page" },
	{ 0xf43d756a, "try_module_get" },
	{ 0x8523188f, "video_devdata" },
	{ 0x18aa895, "module_put" },
	{ 0xb81960ca, "snprintf" },
	{ 0x999e8297, "vfree" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x2824f314, "finish_wait" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x76bff920, "prepare_to_wait" },
	{ 0x5f754e5a, "memset" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x9d669763, "memcpy" },
	{ 0x37a0cba, "kfree" },
	{ 0x686049a7, "video_unregister_device" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0x5bdc87b3, "input_unregister_device" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0x44b4693d, "__wake_up" },
	{ 0x6b8b79e7, "dev_get_drvdata" },
	{ 0xf9a482f9, "msleep" },
	{ 0xa74295af, "usb_clear_halt" },
	{ 0x6539bee1, "usb_set_interface" },
	{ 0xdc7a9490, "usb_kill_urb" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x7ce5f400, "mutex_lock_interruptible" },
	{ 0x7dddf804, "usb_ifnum_to_if" },
	{ 0x7d1fc1f7, "usb_free_urb" },
	{ 0x246bc0b2, "usb_free_coherent" },
	{ 0xa6155a32, "usb_submit_urb" },
	{ 0xa5388eee, "usb_alloc_coherent" },
	{ 0xa2d80725, "usb_alloc_urb" },
	{ 0x27e1a049, "printk" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FFBCF4BD2374601FE6CCFCE");
