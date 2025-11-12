#ifndef __SOCKET_H_
#define __SOCKET_H_

#include <linux/net.h>
#include <linux/in.h>
#include <linux/uio.h>
#include <linux/socket.h>
#include <linux/file.h>
#include <linux/sched/signal.h>
#include <linux/errno.h>

// Kernel-space recvfrom wrapper
static inline int kernel_recvfrom(int sockfd, void *buf, size_t len, int flags,
                                  struct sockaddr *src_addr, int *addrlen)
{
    struct socket *sock;
    struct msghdr msg;
    struct kvec iov;
    int ret;

    // Look up kernel socket from integer fd
    sock = sockfd_lookup(sockfd, &ret);
    if (!sock)
        return ret;

    iov.iov_base = buf;
    iov.iov_len = len;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = src_addr;
    msg.msg_namelen = addrlen ? *addrlen : 0;

    ret = kernel_recvmsg(sock, &msg, &iov, 1, len, flags);

    if (addrlen)
        *addrlen = msg.msg_namelen;

    sockfd_put(sock);  // release reference

    return ret;
}

// Replace all user-space recvfrom calls
#define recvfrom kernel_recvfrom

// porting/sys/socket.h

static inline int kernel_sendto(int sockfd, const void *buf, size_t len, int flags,
                                struct sockaddr *addr, int addr_len)
{
    struct socket *sock;
    struct msghdr msg;
    struct kvec iov;
    int ret;

    sock = sockfd_lookup(sockfd, &ret);
    if (!sock)
        return ret;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = addr;
    msg.msg_namelen = addr_len;

    iov.iov_base = (void *)buf;
    iov.iov_len = len;

    ret = kernel_sendmsg(sock, &msg, &iov, 1, len);

    sockfd_put(sock);
    return ret;
}

#define sendto kernel_sendto


#endif
