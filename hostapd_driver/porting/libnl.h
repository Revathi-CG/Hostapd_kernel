#ifndef __LIBNL_H_
#define __LIBNL_H_

#include <linux/netlink.h>
#include <stddef.h>

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

/* Hostapd calls nlmsg_hdr(struct nl_msg*) but kernel
 * nlmsg_hdr expects struct sk_buff*.
 * Provide macro ONLY for struct nl_msg.
 */
#define nlmsg_hdr(msg)  ((msg)->nlh)

#endif /* __KERNEL__ */

#endif /* __LIBNL_H_ */

