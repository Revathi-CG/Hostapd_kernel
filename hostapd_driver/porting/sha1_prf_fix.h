#ifndef SHA1_PRF_FIX_H
#define SHA1_PRF_FIX_H

#include <linux/crypto.h>
#include <crypto/hash.h>
#include <linux/string.h>
#include <linux/slab.h>

/* hostapd SHA1-PRF wrapper using kernel HMAC-SHA1 */
static inline int hostapd_sha1_prf(const u8 *key, size_t key_len,
                                   const char *label, const u8 *data, size_t data_len,
                                   u8 *out, size_t out_len)
{
    struct crypto_shash *tfm;
    struct shash_desc *desc;

    tfm = crypto_alloc_shash("hmac(sha1)", 0, 0);
    if (IS_ERR(tfm))
        return -1;

    desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!desc) {
        crypto_free_shash(tfm);
        return -1;
    }

    desc->tfm = tfm;

    crypto_shash_setkey(tfm, key, key_len);
    crypto_shash_init(desc);
    crypto_shash_update(desc, (const u8 *)label, strlen(label));
    crypto_shash_update(desc, data, data_len);
    crypto_shash_final(desc, out);

    kfree(desc);
    crypto_free_shash(tfm);

    return 0;
}

/* Override */
#undef sha1_prf
#define sha1_prf hostapd_sha1_prf

#endif

