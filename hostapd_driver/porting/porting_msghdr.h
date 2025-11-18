#ifndef __PORTING_MSGHDR_H__
#define __PORTING_MSGHDR_H__

#include <linux/file.h>
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/uio.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kernel.h>

/*
 * user_msghdr is the structure passed from user space. hostapd writes:
 *     msg.msg_iov
 *     msg.msg_iovlen
 *     msg.msg_name
 *     msg.msg_namelen
 * We reinterpret its pointer layout using our own struct.
 */
struct porting_iovec {
    void  *iov_base;
    size_t iov_len;
};

struct porting_user_msghdr {
    struct porting_iovec *msg_iov;
    size_t                msg_iovlen;
    void                 *msg_name;
    int                   msg_namelen;
    void                 *msg_control;
    size_t                msg_controllen;
    unsigned int          msg_flags;
};


/* hostapd calls sendmsg() → porting_sendmsg() */
static inline ssize_t porting_sendmsg(int sockfd,
                                      struct user_msghdr *umsg,
                                      int flags)
{
    struct porting_user_msghdr *u;
    struct socket *sock;
    struct kvec *kvecs = NULL;
    size_t total = 0;
    ssize_t ret;
    int err = 0;

    if (!umsg)
        return -EINVAL;

    /* reinterpret layout that hostapd filled */
    u = (struct porting_user_msghdr *)umsg;

    if (!u->msg_iov || u->msg_iovlen == 0)
        return 0;

    sock = sockfd_lookup(sockfd, &err);
    if (!sock)
        return err ? err : -EBADF;

    kvecs = kmalloc_array(u->msg_iovlen, sizeof(*kvecs), GFP_KERNEL);
    if (!kvecs) {
        sockfd_put(sock);
        return -ENOMEM;
    }

    for (size_t i = 0; i < u->msg_iovlen; i++) {
        kvecs[i].iov_base = u->msg_iov[i].iov_base;
        kvecs[i].iov_len  = u->msg_iov[i].iov_len;
        total += kvecs[i].iov_len;
    }

    /* Build kernel msghdr */
    struct msghdr kmsg = {
        .msg_name       = u->msg_name,
        .msg_namelen    = u->msg_namelen,
        .msg_control    = u->msg_control,
        .msg_controllen = u->msg_controllen,
        .msg_flags      = u->msg_flags,
    };

    ret = kernel_sendmsg(sock, &kmsg, kvecs,
                         u->msg_iovlen, total);

    kfree(kvecs);
    sockfd_put(sock);

    return ret;
}

#endif

