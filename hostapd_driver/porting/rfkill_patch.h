#ifndef RFKILL_PATCH_H
#define RFKILL_PATCH_H

#include "rfkill_compat.h"
#undef close
#define close(fd)               rfkill_close(fd)

#ifndef open
#define open(path, flags)       rfkill_open(path)
#endif

#ifndef read
#define read(fd, buf, len)      rfkill_read(fd, buf, len)
#endif

#ifndef fcntl
#define fcntl(fd, cmd, arg)     rfkill_set_nonblock(fd)
#endif

#ifndef realpath
#define realpath(path, buf)     rfkill_realpath(path)
#endif
#endif /* RFKILL_PATCH_H */

