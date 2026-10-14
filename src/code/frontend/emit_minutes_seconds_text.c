#include "types.h"

extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern s32 string_length(const char *s) __asm__("func_8011D3DC");
extern void func_8010647C(s32 ctx, s32 ch);
extern char D_80075424[];
extern char D_80075428[];
extern s32 D_803B75A0;

void emit_minutes_seconds_text(s32 ctx, s32 unused, s64 total) __asm__("func_8010595C");

void emit_minutes_seconds_text(s32 ctx, s32 unused, s64 total) {
    char secondsText[8];
    u8 text[0x10];
    s32 seconds;
    s32 minutes;
    s32 len;
    s32 i;

    seconds = total % 60;
    minutes = total / 60;
    format_string(secondsText, D_80075424, seconds + 100);
    format_string(text, D_80075428, minutes, secondsText + 1);
    len = string_length(text);
    D_803B75A0 = -1;
    for (i = 0; i < len; i++) {
        func_8010647C(ctx, text[len - 1 - i]);
    }
    D_803B75A0 = 1;
}
