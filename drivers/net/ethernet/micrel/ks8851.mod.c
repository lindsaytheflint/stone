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
	{ 0x15692c87, "param_ops_int" },
	{ 0x72e62485, "eth_change_mtu" },
	{ 0x4e6d3404, "eth_validate_addr" },
	{ 0x81a61ed0, "driver_unregister" },
	{ 0x6743a5d8, "spi_register_driver" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x77f5ba1b, "__netif_schedule" },
	{ 0x2a3aa678, "_test_and_clear_bit" },
	{ 0xeda0f75b, "mii_check_link" },
	{ 0xda438250, "netif_rx_ni" },
	{ 0xd5a60dae, "eth_type_trans" },
	{ 0x84abd419, "skb_put" },
	{ 0xaf7090f6, "__netdev_alloc_skb" },
	{ 0xd8ad8dcb, "register_netdev" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xa126628, "netdev_warn" },
	{ 0x872de711, "dev_err" },
	{ 0x31f08540, "dev_set_drvdata" },
	{ 0x5083fed, "__raw_spin_lock_init" },
	{ 0x1a1962a9, "__mutex_init" },
	{ 0x88965783, "alloc_etherdev_mqs" },
	{ 0x79aa04a2, "get_random_bytes" },
	{ 0x27cb133b, "eeprom_93cx6_multiread" },
	{ 0x822222db, "eeprom_93cx6_write" },
	{ 0x98bb5a22, "eeprom_93cx6_read" },
	{ 0x63d2ff63, "eeprom_93cx6_wren" },
	{ 0xe4f730b8, "netif_device_detach" },
	{ 0x92b57248, "flush_work" },
	{ 0xf3dddc87, "netdev_info" },
	{ 0xf5b3ecb5, "netif_device_attach" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xe66ff68a, "consume_skb" },
	{ 0xc75e84fc, "skb_dequeue" },
	{ 0xa9dcc10e, "mutex_unlock" },
	{ 0x5366ee05, "mutex_lock" },
	{ 0x3808f6f4, "__dynamic_netdev_dbg" },
	{ 0x27bbf221, "disable_irq_nosync" },
	{ 0xa6208d83, "mii_ethtool_gset" },
	{ 0x6d360a78, "mii_ethtool_sset" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x5c7e9482, "mii_nway_restart" },
	{ 0x7420f0e, "mii_link_ok" },
	{ 0x8f851c99, "skb_queue_tail" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x27e1a049, "printk" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x1adb62a4, "_raw_spin_unlock" },
	{ 0x8949858b, "schedule_work" },
	{ 0x9d669763, "memcpy" },
	{ 0x71c90087, "memcmp" },
	{ 0x84741c31, "_raw_spin_lock" },
	{ 0xfaf98462, "bitrev32" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xc5d074a7, "generic_mii_ioctl" },
	{ 0x49829288, "free_netdev" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x60db9ac8, "unregister_netdev" },
	{ 0xd971e003, "_dev_info" },
	{ 0x6b8b79e7, "dev_get_drvdata" },
	{ 0x92f3c78a, "netdev_err" },
	{ 0xfe249207, "spi_sync" },
	{ 0x8e3a4abb, "netdev_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=eeprom_93cx6";

