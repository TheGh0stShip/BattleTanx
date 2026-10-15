#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct RuntimeState {
    u8 pad00[0xC0];
    s16 framebufferSlot;
} RuntimeState;

#define APPEND(first, second) \
    { \
        command = list++; \
        command->w0 = (first); \
        command->w1 = (second); \
    }

#define PACK_RGBA5551() \
    (((D_801257C4 << 8) & 0xF800) | ((D_801257C5 << 3) & 0x7C0) \
      | ((((u8)D_801257C6 >> 2) & 0x3E) & 0xFF) | 1)

extern s32 func_8007E150(s16 slot);
extern s32 func_80081A30();
extern s32 D_801257C0;
extern u8 D_801257C4;
extern u8 D_801257C5;
extern u8 D_801257C6;
extern u8 D_801257C7;
extern RuntimeState *D_801257C8;
extern u8 D_3DA800;
extern u8 D_1000080;
extern u8 D_801B4BF8;
extern u8 D_801B4BF9;

Gfx *build_runtime_display_list(s32 segmentAddress, Gfx *list) __asm__("func_8007DC5C");

Gfx *build_runtime_display_list(s32 segmentAddress, Gfx *list)
{
    Gfx *command;

    APPEND(0xBC000006, 0);
    APPEND(0xBC000406, D_801257C0 + 0x80000000);
    APPEND(0xBC000806, segmentAddress + 0x80000000);
    APPEND(0xED000000, 0x005003C0);
    APPEND(0xB900031D, 0);
    APPEND(0xFE000000, (u32)&D_3DA800);
    APPEND(0xE7000000, 0);
    APPEND(0xBA001402, 0x00300000);
    APPEND(0xFF10013F, (u32)&D_3DA800);
    APPEND(0xF7000000, 0xFFFCFFFC);
    if (D_801B4BF9 != 0) {
        APPEND(0xF64FC3BC, 0);
    }
    APPEND(0xE7000000, 0);
    APPEND(0xFF10013F, func_8007E150(D_801257C8->framebufferSlot) + 0x80000000);
    APPEND(0xF7000000, (PACK_RGBA5551() << 16) | PACK_RGBA5551());
    if (D_801B4BF8 == 0) {
        APPEND(0xF64FC3BC, 0);
        APPEND(0xE7000000, 0);
    }
    if ((func_80081A30() & 0xFF) && D_801B4BF8 == 0) {
        APPEND(0xB7000000, 0x00010000);
        APPEND(0xF8000000,
            (D_801257C4 << 24) | (D_801257C5 << 16) | (D_801257C6 << 8) | D_801257C7);
        APPEND(0xBC000008, 0x64009D00);
    }
    APPEND(0xBA001402, 0);
    APPEND(0x06000000, (u32)&D_1000080);
    return list;
}
