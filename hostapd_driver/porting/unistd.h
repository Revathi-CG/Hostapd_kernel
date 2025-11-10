#ifndef __UNISTD_H_
#define __UNISTD_H_

/* Kernel-space stub for getopt */
static inline int getopt(int argc, char * const argv[], const char *optstring)
{
    /* Stub: do nothing, always return -1 to indicate end of options */
    return -1;
}

/* Provide stub for optind if code uses it */
static int optind  __attribute__((unused)) = 1;

/* Stub for optarg in kernel space */
static char *optarg  __attribute__((unused))= NULL;

#ifndef __KERNEL_GETPID_STUB__
#define __KERNEL_GETPID_STUB__

/* Kernel equivalent of getpid() is task_pid_nr(current) */
#include <linux/sched.h>

static inline int getpid(void)
{
    return task_pid_nr(current);
}

#endif


#endif
