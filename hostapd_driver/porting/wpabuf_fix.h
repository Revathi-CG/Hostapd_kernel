// porting/wpabuf_fix.h
#ifndef WPABUF_FIX_H
#define WPABUF_FIX_H

struct wpabuf;
void wpabuf_printf(struct wpabuf *buf, char *fmt, ...);
static inline void wpa_debug_stop_log(void) {}
#endif

