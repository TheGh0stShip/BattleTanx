#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define OVERLAY_LIST_SIZE 0x400
#define OVERLAY_LIST_COUNT 8

extern u8 gRenderBytes[5] __asm__("D_801257F0");
extern u8 gOverlayListIndex __asm__("D_801257F5");
extern u8 gIndexedRenderBytes[][4] __asm__("D_801257E0");
extern u8 gOverlayLists[OVERLAY_LIST_COUNT][OVERLAY_LIST_SIZE] __asm__("D_801B4C00");
extern GfxCommand *gOverlayListHead __asm__("D_801B6C00");

extern void func_8008B48C(void);
extern void func_80080EEC(void);
extern void func_80081934(void);
extern void func_80081788(void);
extern void func_800F5B6C(void);
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void draw_filled_rectangle(GfxCommand **head, s32 x, s32 y, s32 width, s32 height, u8 red, u8 green,
                                  u8 blue, u8 alpha) __asm__("func_800F4DFC");
extern void append_display_list_call_2(void *displayList) __asm__("func_8007EF40");
extern void draw_indexed_overlay(u8 red, u8 green, u8 blue, u8 alpha, s32 index) __asm__("func_8008011C");

void draw_render_overlays(void) __asm__("func_800803A4");

void draw_render_overlays(void)
{
    GfxCommand *command;
    s32 i;
    s32 offset;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 boxed;

    func_8008B48C();
    func_80080EEC();
    func_80081934();
    func_80081788();
    func_800F5B6C();
    alpha = gRenderBytes[3];
    if (alpha != 0) {
        gOverlayListHead = (GfxCommand *)gOverlayLists[gOverlayListIndex];
        green = gRenderBytes[1];
        boxed = gRenderBytes[4];
        blue = gRenderBytes[2];
        red = gRenderBytes[0];
        if (boxed) {
            draw_filled_rectangle(&gOverlayListHead, 34, 19, 252, 114, red, green, blue, alpha);
        } else {
            draw_filled_rectangle(&gOverlayListHead, 0, 0, 320, 240, red, green, blue, alpha);
        }
        command = gOverlayListHead++;
        command->w0 = 0xB8000000;
        command->w1 = 0;
        append_display_list_call_2(gOverlayLists[gOverlayListIndex]);
        gOverlayListIndex = (gOverlayListIndex + 1) & 7;
    }
    i = 0;
    offset = 0;
    while (i < get_difficulty_level()) {
        if (gIndexedRenderBytes[0][offset + 3] != 0) {
            draw_indexed_overlay(gIndexedRenderBytes[0][offset], gIndexedRenderBytes[0][offset + 1],
                                 gIndexedRenderBytes[0][offset + 2], gIndexedRenderBytes[0][offset + 3], i);
        }
        offset += 4;
        i++;
    }
}
