#include "types.h"

#define PASSWORD_KEY 0xEFF8DF2B
#define PASSWORD_CHECK_MULTIPLIER 0x19660D
#define PASSWORD_CHECK_ADDEND 0x5F
#define PASSWORD_CHECK_KEY 0xB2

/* Sixteen-character alphabet used for each password nibble. */
extern u8 gPasswordAlphabet[16] __asm__("D_80135778");

void encode_password(u32 value, u8 *password) __asm__("func_800DCFCC");

void encode_password(u32 value, u8 *password)
{
    u32 check;

    value ^= PASSWORD_KEY;
    password[0] = gPasswordAlphabet[value >> 28];
    password[1] = gPasswordAlphabet[(value >> 24) & 0xF];
    password[2] = gPasswordAlphabet[(value >> 20) & 0xF];
    password[3] = gPasswordAlphabet[(value >> 16) & 0xF];
    password[4] = gPasswordAlphabet[(value >> 12) & 0xF];
    password[5] = gPasswordAlphabet[(value >> 8) & 0xF];
    password[6] = gPasswordAlphabet[(value >> 4) & 0xF];
    check = ((value * PASSWORD_CHECK_MULTIPLIER + PASSWORD_CHECK_ADDEND) & 0xFF) ^ PASSWORD_CHECK_KEY;
    password[7] = gPasswordAlphabet[value & 0xF];
    password[8] = gPasswordAlphabet[check >> 4];
    password[9] = gPasswordAlphabet[check & 0xF];
    password[10] = 0;
}
