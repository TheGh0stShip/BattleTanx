#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

#define OVERLAY_LIST_SIZE 0x400
#define OVERLAY_LIST_COUNT 8

extern u8 gOverlayListIndex __asm__("D_801257F5");
extern u8 gOverlayLists[OVERLAY_LIST_COUNT][OVERLAY_LIST_SIZE] __asm__("D_801B4C00");
extern GfxCommand *gOverlayListHead __asm__("D_801B6C00");

extern void draw_filled_rectangle(GfxCommand **head, s32 x, s32 y, s32 width, s32 height, u8 red, u8 green,
                                  u8 blue, u8 alpha) __asm__("func_800F4DFC");
extern void append_display_list_call_2(void *displayList) __asm__("func_8007EF40");

void draw_screen_overlay(u8 red, u8 green, u8 blue, u8 alpha, u8 boxed) __asm__("func_8008001C");

void draw_screen_overlay(u8 red, u8 green, u8 blue, u8 alpha, u8 boxed)
{
    GfxCommand *command;

    gOverlayListHead = (GfxCommand *)gOverlayLists[gOverlayListIndex];
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
