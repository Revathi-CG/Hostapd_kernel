#ifndef __IEEE80211_EXTERNAL_H_
#define __IEEE80211_EXTERNAL_H_

#include <linux/types.h>    // u8, u32
struct hostapd_data;        // forward declaration only
/* Add missing prototypes */
u8 * hostapd_eid_rnr_colocation(struct hostapd_data *hapd,
                                u8 *eid, size_t *len);

u8 * hostapd_eid_rnr_mlo(struct hostapd_data *hapd,
                         u32 type, u8 *eid, size_t *len);

#endif /* __IEEE80211_EXTERNAL_H_ */
