#ifndef __GRP_H_
#define __GRP_H_

/*
 * Kernel-space stub for getgrnam().
 * Returns NULL for any group, as group database doesn't exist in kernel.
 */

struct group {
    char *gr_name;
    char *gr_passwd;
    int   gr_gid;
    char **gr_mem;
};

static inline struct group *getgrnam(const char *name)
{
    (void)name;  // suppress unused parameter warning
    return NULL;  // no group database in kernel
}


#endif
