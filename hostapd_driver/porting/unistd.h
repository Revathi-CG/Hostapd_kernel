#ifndef __UNISTD_H_
#define __UNISTD_H_

/* Kernel-space stub for getopt */
static inline int getopt(int argc, char * const argv[], const char *optstring)
{
    /* Stub: do nothing, always return -1 to indicate end of options */
    return -1;
}

/* Provide stub for optind if code uses it */
static int optind = 1;

#endif
