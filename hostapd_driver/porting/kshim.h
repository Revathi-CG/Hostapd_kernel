/* In ./porting/kshim.h */
#include <linux/slab.h>
#include <linux/string.h> // For kernel string functions like kstrdup


// 4. Redefine memory allocation macros (os.h:508)
// Hostapd uses os_realloc which points to realloc(). We must point to krealloc().
#ifdef os_realloc
#undef os_realloc
#endif
#define os_realloc(p, s) krealloc((p), (s), GFP_KERNEL)

#ifdef os_malloc
#undef os_malloc
#endif
#define os_malloc(s) kmalloc((s), GFP_KERNEL)

// Hostapd uses os_free which points to free(). We must point to kfree().
#ifdef os_free
#undef os_free
#endif
#define os_free(p) kfree(p)

// 5. Redefine os_strdup (porting/string.h:36)
// The compiler notes os_strdup is defined in os.h:517 as strdup(s).
// Since Hostapd overrides it later in your string.h, ensure it points to a kernel equivalent.
// The string.h warning indicates os_strdup is defined to hostapd_strdup in your porting/string.h,
// but os.h defines it as strdup(s) first.
// Since you are using a custom hostapd_strdup, ensure it uses kstrdup internally.
// However, the cleanest fix is often to undefine the original macro before defining yours.
#ifdef strdup
#undef strdup // Undefine user-space function if it sneaked in
#endif

