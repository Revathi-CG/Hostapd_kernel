#ifndef __LIBNL_H_
#define __LIBNL_H_

#include <stddef.h>   // <-- Add this
static inline struct nl_sock *nl_socket_alloc_cb(void *cb)
{
    return NULL; /* or allocate dummy struct */
}

static inline int nl_connect(struct nl_sock *sock, int protocol)
{
    return 0;
}

static inline void nl_socket_free(struct nl_sock *sock)
{
}

static inline int genl_connect(struct nl_sock *sock)
{
    return 0;  // dummy stub for kernel-space compilation
}


#endif
