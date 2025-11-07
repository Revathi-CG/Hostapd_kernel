#ifndef __AES_ENCRYPT_FIX_H
#define __AES_ENCRYPT_FIX_H


/* Bring in kernel AES declaration */
#include <crypto/aes.h>

#undef aes_encrypt
#undef aes_decrypt
#define aes_encrypt hostapd_aes_encrypt
#define aes_decrypt hostapd_aes_decrypt

/* Wrapper function expected by hostapd */
static inline int hostapd_aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
    /* Correct argument order for kernel aes_encrypt(): out, in */
    aes_encrypt((void *)ctx, crypt,(u8 *)plain);
    return 0;
}

static inline int hostapd_aes_decrypt(void *ctx, const u8 *crypt, u8 *plain)
{
    aes_decrypt((void *)ctx, plain, (u8 *)crypt);
    return 0;
}

#endif /* HOSTAPD_AES_ENCRYPT_FIX_H */

