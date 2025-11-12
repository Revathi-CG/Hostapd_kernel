#ifndef __UN_H_
#define __UN_H_

#include <linux/kernel.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/string.h>

/* Kernel-space equivalent of sockaddr_un for porting */
struct sockaddr_un {
    sa_family_t sun_family;    /* AF_UNIX */
    char sun_path[108];        /* maximum path */
};

#endif /* __UN_H_ */
