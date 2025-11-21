#ifndef __CTYPE_H_
#define __CTYPE_H_


/* Kernel-space replacement for isblank() */
/* Space ' ' and tab '\t' are considered blank */
static inline int kernel_isblank(int c)
{
    return c == ' ' || c == '\t';
}
/* Kernel-safe replacement for isblank() */
#ifndef isblank
#define isblank(c)   ((c) == ' ' || (c) == '\t')
#endif




#endif
