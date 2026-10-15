#include "types.h"

#define PASSWORD_KEY 0xEFF8DF2B
#define PASSWORD_CHECK_MULTIPLIER 0x19660D
#define PASSWORD_CHECK_ADDEND 0x5F
#define PASSWORD_CHECK_KEY 0xB2

typedef struct BitStrideEntry {
    s32 start;
    s32 stride;
} BitStrideEntry;

extern s32 string_length(const char *s) __asm__("func_8011D3DC");
extern u8 gPasswordAlphabet[16] __asm__("D_80135778");
extern u8 gBitStrideTable[] __asm__("D_8013578C");

static inline s32 decode_password(u8 *password, s32 *outValue)
{
    s32 value = 0;
    s32 check = 0;
    s32 i;
    s32 digit;
    s32 found;

    if (password == 0) {
        return -1;
    }
    if ((u32)string_length((const char *)password) < 10) {
        return -1;
    }
    for (i = 0; i < 10; i++) {
        found = 0;
        for (digit = 0; digit < 16; digit++) {
            if (password[i] == gPasswordAlphabet[digit]) {
                if (i < 8) {
                    value += digit << ((7 - i) * 4);
                    found = 1;
                } else {
                    check += digit << ((9 - i) * 4);
                    found = 1;
                }
            }
        }
        if (!found) {
            return -1;
        }
    }
    check ^= PASSWORD_CHECK_KEY;
    if (check != ((value * PASSWORD_CHECK_MULTIPLIER + PASSWORD_CHECK_ADDEND) & 0xFF)) {
        return -1;
    }
    *outValue = value ^ PASSWORD_KEY;
    return 0;
}

static inline u32 unpropagate_bit_stride_table(u32 value)
{
    u32 one = 1;
    s32 offset;
    u32 bit;
    s32 stride;
    u32 result;

    for (offset = 15 * sizeof(BitStrideEntry); offset >= 0; offset -= sizeof(BitStrideEntry)) {
        result = value;
        bit = ((BitStrideEntry *)(gBitStrideTable + offset))->start;
        stride = ((BitStrideEntry *)(gBitStrideTable + offset))->stride;
        if ((result >> bit) & 1) {
            for (bit += stride; bit < 32; bit += stride) {
                result ^= one << bit;
            }
        }
        value = result;
    }
    return value;
}

s32 parse_password_settings(u8 *code, s32 *level, s32 *stage, s32 *score, s32 *lives, s32 *mode) __asm__("func_800DD544");

s32 parse_password_settings(u8 *code, s32 *level, s32 *stage, s32 *score, s32 *lives, s32 *mode) {
    u32 value;
    s32 n;

    if (decode_password(code, (s32 *)&value) < 0) {
        goto fail;
    }
    value = unpropagate_bit_stride_table(value);
    n = value & 0x1F;
    *level = n;
    if (n >= 18) {
        goto fail;
    }
    if (n < 2) {
        goto fail;
    }
    *stage = (value >> 5) & 0x3F;
    *score = ((value >> 11) & 0x7FFF) * 1000;
    *mode = (value >> 26) & 3;
    *lives = value >> 28;
    if (*mode == 3) {
        goto fail;
    }
    if (*lives >= 10) {
        goto fail;
    }
    if (*lives < 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
