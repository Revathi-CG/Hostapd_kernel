#ifndef __LIBNL_H_
#define __LIBNL_H_

#include <net/genetlink.h>

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
struct nlattr;
struct nla_policy;
struct netlink_ext_ack;
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


/* Dummy nla_parse stub */
static inline int porting_nla_parse5(struct nlattr *tb[], int maxtype,
                                     const struct nlattr *head, int len,
                                     const struct nla_policy *policy)
{
    (void)tb; (void)maxtype; (void)head;
    (void)len; (void)policy;
    return 0;
}


/* Redirect hostapd includes to the stub — ONLY for hostapd */
#ifdef HOSTAPD_BUILD
#define nlmsg_free(msg) porting_nlmsg_free(msg)
#define nla_parse(...) porting_nla_parse5(__VA_ARGS__)
#endif

#ifdef __KERNEL__

/* ===============================
 * STUBS FOR USERSPACE LIBNL FUNCTIONS
 * =============================== */

/* nl_cb struct stub */
struct nl_cb { int dummy; };

/* Stub functions */
static inline struct nl_cb *nl_socket_get_cb(void *handle) {
    (void)handle;
    return (struct nl_cb *)0;
}

static inline struct nl_cb *nl_cb_clone(struct nl_cb *cb) {
    (void)cb;
    return (struct nl_cb *)0;
}

static inline void nl_cb_put(struct nl_cb *cb) {
    (void)cb;
}

static inline void nl_cb_err(struct nl_cb *cb, int type, void *func, void *arg) {
    (void)cb; (void)type; (void)func; (void)arg;
}

static inline void nl_cb_set(struct nl_cb *cb, int type, int flags, void *func, void *arg) {
    (void)cb; (void)type; (void)flags; (void)func; (void)arg;
}

/* Define missing NL_CB_* macros */
#ifndef NL_CB_CUSTOM
#define NL_CB_CUSTOM 0
#endif
#ifndef NL_CB_FINISH
#define NL_CB_FINISH 0
#endif
#ifndef NL_CB_ACK
#define NL_CB_ACK 0
#endif
#ifndef NL_CB_VALID
#define NL_CB_VALID 0
#endif

/* setsockopt stub for kernel build */
static inline int setsockopt(int sock, int level, int optname, const void *optval, int optlen) {
    (void)sock; (void)level; (void)optname; (void)optval; (void)optlen;
    return 0;
}

#endif /* __KERNEL__ */

#ifdef __KERNEL__
static inline int hostapd_nl_recvmsgs_stub(void *nl_handle, void *cb)
{
    (void)nl_handle;
    (void)cb;
    return 0;
}
#define nl_recvmsgs hostapd_nl_recvmsgs_stub
#endif

#ifdef __KERNEL__
#ifndef NLE_DUMP_INTR
#define NLE_DUMP_INTR NLM_F_DUMP_INTR
#endif
#endif

#ifdef __KERNEL__

#include <linux/netlink.h>
#include <linux/errno.h>
#include <net/netlink.h>
#include <net/genetlink.h>

#endif


/* porting stubs only if kernel version does not define them */
#ifndef nla_parse
#include <net/genetlink.h>
static inline void *genlmsg_attrdata(const void *nlh, int attroffset)
{
    (void)nlh;
    (void)attroffset;
    return NULL;
}

static inline int genlmsg_attrlen(const void *nlh, int attroffset)
{
    (void)nlh;
    (void)attroffset;
    return 0;
}

static inline int porting_nla_parse(struct nlattr *tb[], int maxtype,
                                    const struct nlattr *head, int len,
                                    const struct nla_policy *policy,
                                    struct netlink_ext_ack *extack)
{
    (void)tb; (void)maxtype; (void)head; (void)len;
    (void)policy; (void)extack;
    return 0;
}

/* Wrapper macro to allow 5 or 6 args */
#define nla_parse(...) porting_nla_parse(__VA_ARGS__, NULL)

#endif

#ifndef nlmsg_free
static inline void porting_nlmsg_free(struct nl_msg *msg)
{
    (void)msg;
}
#define nlmsg_free(msg) porting_nlmsg_free(msg)
#endif

#ifndef nla_put_flag
static inline int porting_nla_put_flag(struct nl_msg *msg, int attrtype)
{
    (void)msg; (void)attrtype; return 0;
}
#define nla_put_flag(msg, attrtype) porting_nla_put_flag(msg, attrtype)
#endif

#ifndef nla_put_u16
static inline int porting_nla_put_u16(struct nl_msg *msg, int attrtype, unsigned short val)
{
    (void)msg; (void)attrtype; (void)val; return 0;
}
#define nla_put_u16(msg, attrtype, val) porting_nla_put_u16(msg, attrtype, val)
#endif

#ifndef nla_put_u32
static inline int porting_nla_put_u32(struct nl_msg *msg, int attrtype, unsigned int val)
{
    (void)msg; (void)attrtype; (void)val; return 0;
}
#define nla_put_u32(msg, attrtype, val) porting_nla_put_u32(msg, attrtype, val)
#endif

#ifndef nla_put
static inline int porting_nla_put(struct nl_msg *msg, int attrtype, int len, const void *data)
{
    (void)msg; (void)attrtype; (void)len; (void)data; return 0;
}
#define nla_put(msg, attrtype, len, data) porting_nla_put(msg, attrtype, len, data)
#endif

/* Only for Hostapd internal porting: provide a stub so code compiles */
/* Stub for genlmsg_put to compile Hostapd against kernel 6.14 */
static inline void *porting_genlmsg_put(void *msg, u32 portid, u32 seq,
                                        int nlctrl_id, int unused1, int unused2,
                                        int cmd, int unused3)
{
    (void)msg;
    (void)portid;
    (void)seq;
    (void)nlctrl_id;
    (void)unused1;
    (void)unused2;
    (void)cmd;
    (void)unused3;
    return NULL;
}

/* Redirect genlmsg_put calls to stub */
#define genlmsg_put porting_genlmsg_put

/* porting stubs for kernel builds */
#ifndef nla_put_string
static inline int porting_nla_put_string(struct nl_msg *msg, int attrtype, const char *s)
{
    (void)msg;       /* ignore struct nl_msg */
    (void)attrtype;  /* ignore attribute type */
    (void)s;         /* ignore string */
    return 0;        /* pretend success */
}

#define nla_put_string porting_nla_put_string
#endif


#endif /* __LIBNL_H_ */
