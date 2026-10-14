#include "types.h"

typedef struct ModeState {
    u32 mode;
    u8 pad04[0x1CC - 0x4];
    s32 value1CC;
} ModeState;

extern void func_800A4B2C(void);
extern void func_800A66C8(void);
extern s32 D_801B4AC0;
extern s32 D_801B4AD4;

void apply_mode_display_rows(ModeState *state) __asm__("func_8007C2A0");

void apply_mode_display_rows(ModeState *state) {
    switch (state->mode) {
        case 0:
        case 3:
        case 4:
        case 6:
            func_800A4B2C();
            func_800A66C8();
            break;
    }
    if (state->value1CC == 1) {
        D_801B4AC0 = 0x18;
    } else {
        D_801B4AC0 = 0x12;
    }
    D_801B4AD4 = D_801B4AC0 * 5;
}
