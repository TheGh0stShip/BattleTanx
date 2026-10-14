#include "types.h"

typedef struct TimedMessageOwner {
    u8 pad000[0x1A6];
    u8 value1A6;
    u8 pad1A7[0x71];
    s32 state;
    s32 expireTick;
    char line0[0x20];
    char line1[0x20];
} TimedMessageOwner;

extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern char D_80072DE8[];
extern f32 D_80072DEC;
extern s32 gGameTicks __asm__("D_801B4AA8");

void set_timed_message_lines(TimedMessageOwner *owner, char *text0, char *text1, f32 seconds) __asm__("func_800A52AC");

void set_timed_message_lines(TimedMessageOwner *owner, char *text0, char *text1, f32 seconds) {
    if (owner->value1A6 == 0) {
        owner->expireTick = gGameTicks + (s32)(seconds * D_80072DEC);
        owner->state = 0x27;
        format_string(owner->line0, D_80072DE8, text0);
        format_string(owner->line1, D_80072DE8, text1);
    }
}
