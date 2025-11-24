#ifndef __PORTING_INCLUDES_H_
#define __PORTING_INCLUDES_H_


#ifdef __KERNEL__
// Undefine 'free' to prevent macro expansion conflicts with struct eap_method's 'free' member
//#undef free
// Redefine os_free to use kernel's kfree for memory deallocation
//#define os_free kfree
// Ensure eap_method's free function uses kfree in kernel context
// (This assumes the eap_method's free pointer is set to os_free or similar in hostapd code)
#else
// User-space definitions (if any)
#define os_free free
#endif
#include "openssl/asn1_compat.h"

// Use a flag to completely remove the function body in the source file
// The hostapd source code likely wraps this function with #ifndef/endif
#define CONFIG_NO_STDOUT_DEBUG 1
#define CONFIG_NO_DUMP_STATE 1


// ADD/REPLACE with the following:
#define wpa_driver_nl80211_handle_eapol_tx_status \
	porting_wpa_driver_nl80211_handle_eapol_tx_status_stub


/* Disable OpenSSL backend when building inside kernel */
#undef CONFIG_TLS
#undef CONFIG_TLS_OPENSSL
#undef CONFIG_CRYPTO_OPENSSL

/* Force internal crypto */
#define CONFIG_TLS_INTERNAL
#define CONFIG_CRYPTO_INTERNAL

// ./porting/includes.h

// --- FIX: Command-Line Macro Conflicts ---
// These #undefs remove definitions forced via the Makefile's -D flags
// (seen as <command-line>: note: this is the location of the previous definition)
// This prevents the kernel headers from throwing 'redefined' warnings.

#ifdef CLOCK_BOOTTIME
#undef CLOCK_BOOTTIME
#endif

#ifdef SOL_NETLINK
#undef SOL_NETLINK
#endif

// --- Standard Includes and other necessary porting definitions below ---

// ... (Rest of your includes and definitions, including the Netlink guards and library includes)
#ifdef ETH_P_PREAUTH
#undef ETH_P_PREAUTH
#endif

#ifdef NLM_F_CAPPED
#undef NLM_F_CAPPED
#endif

#ifdef NLM_F_ACK_TLVS
#undef NLM_F_ACK_TLVS
#endif

#ifdef NETLINK_CAP_ACK
#undef NETLINK_CAP_ACK
#endif

#ifdef NETLINK_EXT_ACK
#undef NETLINK_EXT_ACK
#endif
#ifdef CONFIG_ELOOP_SELECT
#undef CONFIG_ELOOP_SELECT
#endif

#define OPENSSL_API_COMPAT 0x10100000L



/* Include kernel netlink definitions */
#include <linux/netlink.h>

#include "driver.h"
#include "porting_msghdr.h"
#include "file_ops.h"

#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
#include "kshim.h"
#ifndef HOSTAPD_LIBNL_H_ALREADY_INCLUDED
#define HOSTAPD_LIBNL_H_ALREADY_INCLUDED
/* In porting/includes.h (or the file that includes driver_nl80211.h) */

#include "../hostapd-2.11/src/drivers/driver_nl80211.h"

#ifdef nla_nest_start
#undef nla_nest_start
#endif
#include <linux/slab.h>
#include "libnl.h"

#include "libnl.h"
#endif
#ifndef HOSTAPD_NLATTR_ARRAY
#define HOSTAPD_NLATTR_ARRAY(name, size) struct nlattr *name[size] = {0}
#endif


#pragma once
#include <linux/socket.h>   // MUST come first so struct msghdr is defined
#include <linux/uio.h>      // struct iovec
#include <linux/types.h>    // size_t, __user
#include <linux/in.h>
#include <linux/in6.h>
#include "porting_msghdr.h"

#undef sendmsg
#define sendmsg    porting_sendmsg

#include <net/genetlink.h>





#ifdef __KERNEL__
#include <net/genetlink.h>  // for struct genlmsghdr

#ifndef GENL_HDRLEN
#define GENL_HDRLEN (sizeof(struct genlmsghdr))
#endif

#endif


/*
	 * Ensure networking address structs (in_addr, in6_addr) exist before hostapd uses them.
	 * Required when building hostapd in kernel space.
	 */
#include <linux/in.h>      // struct in_addr
	#include <linux/in6.h>     // struct in6_addr
#define strtol(buf, end, base)    simple_strtol(buf, end, base)


// Hostapd expects FILE*
// Replace FILE with struct file (kernel)

//typedef struct file FILE;
//#define fopen(path, mode)        k_fopen(path, mode)
//#define fgets(buf, size, fp)     k_fgets(buf, size, fp)
//#define fclose(fp)               k_fclose(fp)

#include "sys/socket.h"

#include <string.h>

#include "ieee80211_external.h"

// Fixes 'UINT32_MAX' undeclared error
#include <stdint.h>

/* This file gets force-included via Makefile to override random_init() */
#include "random.h"
#include "errno.h"

//#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "grp.h"
#include "common.h"
#include "wpabuf_fix.h"


#define CONFIG_AES_CRYPTO_OPENSSL
#include "aes_encrypt_fix.h"

#include "sha1_prf_fix.h"
#include "byteswap.h"
#include "signal.h"

#include "openssl/hmac.h"
#include "linux/types.h"
// Replace atoi() with kstrtoint() for kernel environment
#include <linux/kernel.h>    // kstrtoint()

/* required for size_t */
#include <linux/types.h>
#include <linux/kernel.h>

/* hostapd expects be16/be32 (big-endian) types from BSD socket headers.
 * Kernel equivalent types exist: __be16, __be32.
 */

typedef __be16 be16;
typedef __be32 be32;
typedef __be64 be64;


#include <linux/kstrtox.h>     // kstrtoul(), kstrtoint()

/* ---- Replacement for strtoul() ---- */
static inline unsigned long strtoul(const char *str, char **endp, int base)
{
    unsigned long val = 0;
        int ret = kstrtoul(str, base, &val);   // handle return value to avoid warning
    (void)ret;                             // silence unused warning

    if (endp)
	    *endp = (char *)str;  // hostapd never uses endp
    return val;
}
/*........atoi*/
static inline int k_atoi(const char *str)
{
    int val = 0;
        int ret = kstrtoint(str, 10, &val);    // handle return
        (void)ret;
    return val;
}

#define atoi(x) k_atoi(x)

/* Declare missing libc functions without including stdlib.h */
#ifndef __DECLARE_QSORT_ATOI_STRTOL
#define __DECLARE_QSORT_ATOI_STRTOL

/* qsort */
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));

#endif
// forward declaration (instead of including pbkdf2.h)
int pbkdf2_sha1(const char *passphrase, const unsigned char *ssid, size_t ssid_len,
                int iterations, unsigned char *buf, size_t buflen);


#include <linux/ip.h>
#include <linux/udp.h>
/* Map struct ip → struct iphdr for hostapd */
#define ip     iphdr

/* Kernel-space replacement for daemon() */
#ifndef PORTING_DAEMON_OVERRIDE
#define PORTING_DAEMON_OVERRIDE

/* Replace userspace daemon() with a stub that returns success */
static inline int daemon(int nochdir, int noclose)
{
    /* kernel modules cannot daemonize */
    return 0;
}

#endif

#include "perror.h"

#ifdef HOSTAPD_KERNEL
#ifdef HOSTAPD_EAP_SERVER
//#undef free   // Temporarily disable the kernel macro for eap_server
#endif
#endif



#include "rfkill_patch.h"
#include "rfkill_compat.h"
#include "ioctl_compat.h"
#include "arp_compat.h"
#include "readlink_compat.h"
#include "errno_compat.h"
#include "rand_compat.h"


#ifndef __KERNEL__

#include <openssl/asn1.h>
#include <openssl/x509.h>

#endif
#define NEED_X509_COMPAT
#include "openssl/x509.h"
#ifdef __KERNEL__
#include "openssl/ec.h"
#endif

#include "ctype.h"

#undef CMSG_FIRSTHDR
#define CMSG_FIRSTHDR(mhdr) \
    __cmsg_nxthdr((struct msghdr *)(mhdr), (mhdr)->msg_controllen, NULL)

#undef CMSG_NXTHDR
#define CMSG_NXTHDR(mhdr, cmsg) \
    __cmsg_nxthdr((struct msghdr *)(mhdr),(mhdr)->msg_controllen, (struct cmsghdr *)(cmsg))

static inline ssize_t porting_write_stub(int fd, const void *buf, size_t count)
{
    /* Kernel modules cannot easily write to file descriptors like userspace.
       Stubbing out for compilation. */
    return count;
}
#define write(fd, buf, count) porting_write_stub(fd, buf, count)


/* Add this new stub function definition */
static inline int porting_kernel_recvmsg_stub(struct socket *sock, void *umsg_ptr,
                                              struct kvec *vec, size_t size, int flags)
{
    /* This stub disables the actual recvmsg functionality in the kernel module,
       which is the goal for userspace APIs like this. */
    (void)sock; (void)umsg_ptr; (void)vec; (void)size; (void)flags;
    return 0;
}

#undef recvmsg
#define recvmsg(sock, msg, flags) \
    porting_kernel_recvmsg_stub((struct socket *)(sock), (void *)(msg), NULL, 0, flags)

/*
#ifndef recvmsg
#define recvmsg(sock, msg, flags) \
	kernel_recvmsg((struct socket *)(sock), (struct msghdr *)(void *)(msg), NULL, 0, 0, flags)
#endif
*/
/* ... (Keep your macros for msghdr/iovec at the very end) ... */
#define msghdr porting_user_msghdr
#define iovec porting_iovec
#include "stdlib.h"

#endif

