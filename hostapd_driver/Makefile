obj-m += hostapd_driver.o
# Define the conflicting names to be replaced by Hostapd's unique names
ccflags-y += -DCONFIG_DRIVER_MODULE -DCONFIG_NO_INTERNAL_IEEE80211_CRYPTO
ccflags-y += -Daes_encrypt=hostapd_aes_encrypt
ccflags-y += -Daes_decrypt=hostapd_aes_decrypt
# Ensure the hostapd_driver-objs section lists all files correctly.

hostapd_driver-objs := 	hostapd-2.11/hostapd/main.o \
	hostapd-2.11/hostapd/config_file.o \
	hostapd-2.11/hostapd/../src/ap/hostapd.o \
	hostapd-2.11/hostapd/../src/ap/wpa_auth_glue.o \
	hostapd-2.11/hostapd/../src/ap/drv_callbacks.o \
	hostapd-2.11/hostapd/../src/ap/ap_drv_ops.o \
	hostapd-2.11/hostapd/../src/ap/utils.o \
	hostapd-2.11/hostapd/../src/ap/authsrv.o \
	hostapd-2.11/hostapd/../src/ap/ieee802_1x.o \
	hostapd-2.11/hostapd/../src/ap/ap_config.o \
	hostapd-2.11/hostapd/../src/ap/eap_user_db.o \
	hostapd-2.11/hostapd/../src/ap/ieee802_11_auth.o \
	hostapd-2.11/hostapd/../src/ap/sta_info.o \
	hostapd-2.11/hostapd/../src/ap/wpa_auth.o \
	hostapd-2.11/hostapd/../src/ap/tkip_countermeasures.o \
	hostapd-2.11/hostapd/../src/ap/ap_mlme.o \
	hostapd-2.11/hostapd/../src/ap/wpa_auth_ie.o \
	hostapd-2.11/hostapd/../src/ap/preauth_auth.o \
	hostapd-2.11/hostapd/../src/ap/pmksa_cache_auth.o \
	hostapd-2.11/hostapd/../src/ap/ieee802_11_shared.o \
	hostapd-2.11/hostapd/../src/ap/beacon.o \
	hostapd-2.11/hostapd/../src/ap/bss_load.o \
	hostapd-2.11/hostapd/../src/ap/neighbor_db.o \
	hostapd-2.11/hostapd/../src/ap/rrm.o \
	hostapd-2.11/hostapd/../src/common/ptksa_cache.o \
	hostapd-2.11/hostapd/../src/drivers/drivers.o \
	hostapd-2.11/hostapd/../src/utils/eloop.o \
	hostapd-2.11/hostapd/../src/utils/common.o \
	hostapd-2.11/hostapd/../src/utils/wpa_debug.o \
	hostapd-2.11/hostapd/../src/utils/wpabuf.o \
	hostapd-2.11/hostapd/../src/utils/os_unix.o \
	hostapd-2.11/hostapd/../src/utils/ip_addr.o \
	hostapd-2.11/hostapd/../src/utils/crc32.o \
	hostapd-2.11/hostapd/../src/common/ieee802_11_common.o \
	hostapd-2.11/hostapd/../src/common/wpa_common.o \
	hostapd-2.11/hostapd/../src/common/hw_features_common.o \
	hostapd-2.11/hostapd/../src/eapol_auth/eapol_auth_sm.o \
	hostapd-2.11/hostapd/../src/eapol_auth/eapol_auth_dump.o \
	hostapd-2.11/hostapd/../src/common/ctrl_iface_common.o \
	hostapd-2.11/hostapd/ctrl_iface.o \
	hostapd-2.11/hostapd/../src/ap/ctrl_iface_ap.o \
	hostapd-2.11/hostapd/../src/drivers/rfkill.o \
	hostapd-2.11/hostapd/../src/utils/radiotap.o \
	hostapd-2.11/hostapd/../src/drivers/linux_ioctl.o \
	hostapd-2.11/hostapd/../src/l2_packet/l2_packet_none.o \
	hostapd-2.11/hostapd/eap_register.o \
	hostapd-2.11/hostapd/../src/eap_server/eap_server.o \
	hostapd-2.11/hostapd/../src/eap_common/eap_common.o \
	hostapd-2.11/hostapd/../src/eap_server/eap_server_identity.o \
	hostapd-2.11/hostapd/../src/crypto/crypto_openssl.o \
	hostapd-2.11/hostapd/../src/crypto/tls_none.o \
	hostapd-2.11/hostapd/../src/crypto/sha1-prf.o \
	hostapd-2.11/hostapd/../src/crypto/sha256-prf.o \
	hostapd-2.11/hostapd/../src/crypto/sha256-tlsprf.o \
	hostapd-2.11/hostapd/../src/crypto/random.o \
	hostapd-2.11/hostapd/../src/ap/wmm.o \
	hostapd-2.11/hostapd/../src/ap/ap_list.o \
	hostapd-2.11/hostapd/../src/ap/comeback_token.o \
	hostapd-2.11/hostapd/../src/pasn/pasn_responder.o \
	hostapd-2.11/hostapd/../src/pasn/pasn_common.o \
	hostapd-2.11/hostapd/../src/ap/ieee802_11.o \
	hostapd-2.11/hostapd/../src/ap/hw_features.o \
	hostapd-2.11/hostapd/../src/ap/dfs.o \
	hostapd-2.11/hostapd/../src/ap/ieee802_11_ht.o \
	hostapd-2.11/hostapd/../src/drivers/driver_common.o \
        hostapd-2.11/hostapd/../src/drivers/driver_nl80211.o \
        hostapd-2.11/hostapd/../src/drivers/driver_nl80211_capa.o \
        hostapd-2.11/hostapd/../src/drivers/driver_nl80211_event.o \
        hostapd-2.11/hostapd/../src/drivers/driver_nl80211_monitor.o \
        hostapd-2.11/hostapd/../src/drivers/driver_nl80211_scan.o \
        hostapd-2.11/hostapd/../src/drivers/netlink.o \
        hostapd-2.11/hostapd/../src/eap_server/eap_server_methods.o \

ccflags-y += -I./porting -include porting/includes.h
EXTRA_CFLAGS += -include $(PWD)/hostapd-2.11/src/utils/common.h
ccflags-y += -I./hostapd-2.11/hostapd 
ccflags-y += -I./hostapd-2.11/src/ap 
ccflags-y += -I./hostapd-2.11/src/common 
ccflags-y += -I./hostapd-2.11/src/crypto 
ccflags-y += -I./hostapd-2.11/src/drivers 
ccflags-y += -I./hostapd-2.11/src/eap_common 
ccflags-y += -I./hostapd-2.11/src/eapol_auth 
ccflags-y += -I./hostapd-2.11/src/eapol_supp 
ccflags-y += -I./hostapd-2.11/src/eap_peer 
ccflags-y += -I./hostapd-2.11/src/eap_server 
ccflags-y += -I./hostapd-2.11/src/fst 
ccflags-y += -I./hostapd-2.11/src/l2_packet 
ccflags-y += -I./hostapd-2.11/src/p2p 
ccflags-y += -I./hostapd-2.11/src/pae 
ccflags-y += -I./hostapd-2.11/src/pasn 
ccflags-y += -I./hostapd-2.11/src/radius 
ccflags-y += -I./hostapd-2.11/src/rsn_supp 
ccflags-y += -I./hostapd-2.11/src/tls 
ccflags-y += -I./hostapd-2.11/src/utils 
ccflags-y += -I./hostapd-2.11/src/wps
ccflags-y += -I./hostapd-2.11/src
ccflags-y += -Wno-implicit-fallthrough
ccflags-y += -Wno-strict-prototypes
ccflags-y += -Wno-frame-larger-than
ccflags-y += -Wno-overflow -Wno-sign-conversion
ccflags-y += -Wno-format -Wno-format-extra-args
ccflags-y += -Wno-undef

CFLAGS += -Dhostapd_sendmsg_wrapper=hostapd_sendmsg_wrapper 
ccflags-y += -DHOSTAPD_COMPILING_CRYPTO_OPENSSL

ccflags-y += -DCONFIG_NO_VLAN
ccflags-y += -DCONFIG_NO_RADIUS
ccflags-y += -DNEED_AP_MLME
ccflags-y += -DHOSTAPD
ccflags-y += -DCRYPTO_RSA_OAEP_SHA256
ccflags-y += -DCONFIG_FIPS
ccflags-y += -DCONFIG_NO_RC4
ccflags-y += -DCONFIG_SHA256
ccflags-y += -DETH_P_PREAUTH
ccflags-y += -DCONFIG_DRIVER_NL80211
ccflags-y += -DCONFIG_ELOOP_SELECT
ccflags-y += -DANDROID_LOG_NAME
ccflags-y += -DLOG_HOSTAPD
ccflags-y += -D_WIN32
ccflags-y += -D_POSIX_C_SOURCE
ccflags-y += -DCLOCK_BOOTTIME
ccflags-y += -DCLOCK_MONOTONIC
ccflags-y += -DCONFIG_CTRL_IFACE_UNIX
ccflags-y += -DHOSTAPD_DUMP_STATE
ccflags-y += -DNETLINK_CAP_ACK
ccflags-y += -DNETLINK_EXT_ACK
ccflags-y += -DNLM_F_CAPPED
ccflags-y += -DNLM_F_ACK_TLVS
ccflags-y += -DSOL_NETLINK
ccflags-y += -DANDROID_LIB_STUB
ccflags-y += -DEAP_SERVER_IDENTITY


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

