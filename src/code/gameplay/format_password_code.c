#include "types.h"

typedef struct PasswordBitRule {
    s32 start;
    s32 stride;
} PasswordBitRule;

extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern char D_80074314[];
extern char D_80074320[];
extern char gPasswordAlphabet[] __asm__("D_80135778");
extern PasswordBitRule gPasswordBitRules[] __asm__("D_8013578C");

void format_password_code(s32 value0, s32 value1, s32 value2, s32 value3, s32 value4, char *out)
    __asm__("func_800DD310");

void format_password_code(s32 value0, s32 value1, s32 value2, s32 value3, s32 value4, char *out)
{
    u32 code;
    u32 check;
    u32 encoded;
    s32 i;
    s32 stride;

    if (value0 == -1) {
        if (value2 > 0x1AB3F0) {
            format_string(out, D_80074314);
        } else {
            format_string(out, D_80074320);
        }
        return;
    }
    if (value2 > 0x1F3FC18) {
        value2 = 0x1F3FC18;
    }
    if (value1 >= 0x40) {
        value1 = 0x3F;
    }
    code = (value3 << 28) + (value4 << 26) + ((value2 / 1000) << 11) + (value1 << 5) + value0;
    for (i = 0; i < 16; i++) {
        value1 = gPasswordBitRules[i].start;
        stride = gPasswordBitRules[i].stride;
        if ((code >> value1) & 1) {
            for (value1 += stride; (u32) value1 < 32; value1 += stride) {
                code ^= 1 << value1;
            }
        }
    }
    encoded = code ^ 0xEFF8DF2B;
    out[0] = gPasswordAlphabet[encoded >> 28];
    out[1] = gPasswordAlphabet[(encoded >> 24) & 0xF];
    out[2] = gPasswordAlphabet[(encoded >> 20) & 0xF];
    out[3] = gPasswordAlphabet[(encoded >> 16) & 0xF];
    out[4] = gPasswordAlphabet[(encoded >> 12) & 0xF];
    out[5] = gPasswordAlphabet[(encoded >> 8) & 0xF];
    out[6] = gPasswordAlphabet[(encoded >> 4) & 0xF];
    check = ((encoded * 0x19660D + 0x5F) & 0xFF) ^ 0xB2;
    out[7] = gPasswordAlphabet[encoded & 0xF];
    out[8] = gPasswordAlphabet[check >> 4];
    out[9] = gPasswordAlphabet[check & 0xF];
    out[10] = 0;
}
