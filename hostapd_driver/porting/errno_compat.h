#ifndef ERRNO_COMPAT_H
#define ERRNO_COMPAT_H

static int saved_errno_stub __attribute__((unused)) = 0;

#ifdef errno
#undef errno
#endif
#define errno (saved_errno_stub)

#endif /* ERRNO_COMPAT_H */

