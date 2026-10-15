#include "types.h"

typedef struct ColorFadeState {
    u8 pad00[0xC];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad0F;
    s32 duration;
    s32 elapsed;
    s32 index;
} ColorFadeState;

typedef struct OwnerRecordF4 {
    u8 pad00[0xF4];
    void *valueF4;
} OwnerRecordF4;

extern void set_screen_fade_color(s32 red, s32 green, s32 blue, s32 alpha, s32 flag)
    __asm__("func_8008054C");
extern void set_indexed_fade_color(s32 red, s32 green, s32 blue, s32 alpha, s32 index)
    __asm__("func_80080580");
extern OwnerRecordF4 *get_owner_record(u16 index) __asm__("func_800A6688");
extern s32 fade_owner_is_available(void) __asm__("func_800EC644");
extern u8 D_010001E0[];

void update_color_fade_overlay(ColorFadeState *state) __asm__("func_800F2EFC");

void update_color_fade_overlay(ColorFadeState *state)
{
    s32 index = state->index;
    s32 flag;
    __typeof__(index) savedIndex = index;

    if (index == -1) {
        flag = 0;
        if (fade_owner_is_available() != 0) {
            flag = get_owner_record(0)->valueF4 == D_010001E0;
        }
        set_screen_fade_color(state->red, state->green, state->blue,
                              (~((state->elapsed << 8) / state->duration)) & 0xFF,
                              flag);
        return;
    }
    set_indexed_fade_color(state->red, state->green, state->blue,
                           (~((state->elapsed << 8) / state->duration)) & 0xFF,
                           savedIndex);
}
