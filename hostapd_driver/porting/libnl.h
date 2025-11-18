#ifndef __LIBNL_H_
#define __LIBNL_H_

#include <stddef.h>

#ifdef __KERNEL__
#ifndef NLE_NOMEM
#define NLE_NOMEM ENOMEM
#endif
#endif



/* =====================================
 * Basic stubs
 * ===================================== */
struct nl_sock;

/* Fake nl_msg (always defined) */
struct nl_msg {
    struct nlmsghdr *nlh;
};

/* Stub constants */
#define NL_STOP 0
#define NL_OK   1

/* If kernel is missing NL_SKIP, define it */
#ifndef NL_SKIP
#define NL_SKIP 2
#endif

static inline struct nl_sock *nl_socket_alloc_cb(void *cb) { return NULL; }
static inline int nl_connect(struct nl_sock *sock, int protocol) { return 0; }
static inline void nl_socket_free(struct nl_sock *sock) { }
static inline int genl_connect(struct nl_sock *sock) { return 0; }
static inline int nl_socket_set_buffer_size(struct nl_sock *sock, int txbuf, int rxbuf) { return 0; }
static inline const char *nl_geterror(int err) { return "libnl disabled"; }
static inline void nl_socket_set_nonblocking(struct nl_sock *sock) { }
static inline int nl_socket_get_fd(struct nl_sock *sock) { return -1; }

/* =====================================
 * KERNEL-ONLY compatibility layer
 * ===================================== */
#ifdef __KERNEL__

#include <linux/netlink.h>  // kernel nla_parse and nlmsghdr
/* Hostapd calls nlmsg_hdr(struct nl_msg*) but kernel
 * nlmsg_hdr expects struct sk_buff*.
 * Provide macro ONLY for struct nl_msg.
 */
#define nlmsg_hdr(msg)  ((msg)->nlh)



#endif

#ifdef __KERNEL__

#include <linux/netlink.h>

/* Stub for nlmsg_alloc to avoid implicit declaration in kernel space */
#ifndef HOSTAPD_NLMSG_ALLOC_STUB
#define HOSTAPD_NLMSG_ALLOC_STUB
static inline struct nl_msg *nlmsg_alloc(void)
{
    return NULL;  /* return NULL to satisfy compiler; not actually used in kernel build */
}
#endif

#endif /* __KERNEL__ */

#ifdef __KERNEL__

/* Stub nl_send_auto_complete for hostapd in kernel mode */
#ifndef HOSTAPD_NL_SEND_AUTO_COMPLETE_DEFINED
#define HOSTAPD_NL_SEND_AUTO_COMPLETE_DEFINED
static inline int nl_send_auto_complete(void *handle, void *msg)
{
    (void)handle;
    (void)msg;
    return 0;  // stub returns 0
}
#endif

#endif /* __KERNEL__ */


#endif /* __LIBNL_H_ */
