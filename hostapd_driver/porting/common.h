#ifndef __COMMON_H_
#define __COMMON_H_

#ifdef ARRAY_SIZE
#undef ARRAY_SIZE
#endif
/* Custom ARRAY_SIZE for kernel-space porting */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))


#endif /* __COMMON_H_ */

