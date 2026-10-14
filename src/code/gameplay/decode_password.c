#include "types.h"

#define PASSWORD_KEY 0xEFF8DF2B
#define PASSWORD_CHECK_MULTIPLIER 0x19660D
#define PASSWORD_CHECK_ADDEND 0x5F
#define PASSWORD_CHECK_KEY 0xB2

extern s32 string_length(const char *s) __asm__("func_8011D3DC");
extern u8 gPasswordAlphabet[16] __asm__("D_80135778");

s32 decode_password(u8 *password, s32 *outValue) __asm__("func_800DD0DC");

s32 decode_password(u8 *password, s32 *outValue)
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
