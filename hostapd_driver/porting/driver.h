// In ./porting/driver.h

#include <linux/types.h>

// 1. Define the necessary macro alias (MUST stay outside the guard)
#define wpa_driver_nl80211_handle_eapol_tx_status \
    hostapd_nl80211_handle_eapol_tx_status_stub

// 2. Wrap the static inline definition in a guard
#ifndef __HOSTAPD_DRIVER_NL80211_C__
static inline void hostapd_nl80211_handle_eapol_tx_status_stub(
    int sock, void *data, void *event_data)
{
    /* Stubbed out. */
    (void)sock;
    (void)data;
    (void)event_data;
}
#endif // __HOSTAPD_DRIVER_NL80211_C__
