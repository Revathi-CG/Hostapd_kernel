#ifndef HOSTAPD_ASN1_COMPAT_H
#define HOSTAPD_ASN1_COMPAT_H

/* Minimal ASN1_STRING definition ONLY. 
 * Do NOT declare or define ASN1_STRING_get0_data() here.
 * Hostapd already provides its own version in crypto_openssl.c.
 */

typedef struct {
    unsigned char *data;
    int length;
} ASN1_STRING;

/* Some older code uses ASN1_STRING_data() — provide a simple macro. */
#ifndef ASN1_STRING_data
#define ASN1_STRING_data(x) ((x) ? (x)->data : NULL)
#endif

#endif /* HOSTAPD_ASN1_COMPAT_H */

