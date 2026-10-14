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

extern s32 func_8007AAA0(void);
extern void draw_filled_rectangle(GfxCommand **head, s32 x, s32 y, s32 width, s32 height, u8 red, u8 green,
                                  u8 blue, u8 alpha) __asm__("func_800F4DFC");
extern void append_display_list_call_2(void *displayList) __asm__("func_8007EF40");

void draw_viewport_overlay(u8 red, u8 green, u8 blue, u8 alpha, s32 viewport) __asm__("func_8008011C");

void draw_viewport_overlay(u8 red, u8 green, u8 blue, u8 alpha, s32 viewport)
{
    GfxCommand *command;

    gOverlayListHead = (GfxCommand *)gOverlayLists[gOverlayListIndex];
    switch (func_8007AAA0()) {
    case 1:
        draw_filled_rectangle(&gOverlayListHead, 0, 0, 320, 240, red, green, blue, alpha);
        break;
    case 2:
        switch (viewport) {
        case 0:
            draw_filled_rectangle(&gOverlayListHead, 0, 0, 320, 119, red, green, blue, alpha);
            break;
        case 1:
            draw_filled_rectangle(&gOverlayListHead, 0, 121, 320, 240, red, green, blue, alpha);
            break;
        }
        break;
    case 3:
        switch (viewport) {
        case 0:
            draw_filled_rectangle(&gOverlayListHead, 0, 0, 320, 119, red, green, blue, alpha);
            break;
        case 1:
            draw_filled_rectangle(&gOverlayListHead, 0, 121, 159, 240, red, green, blue, alpha);
            break;
        case 2:
            draw_filled_rectangle(&gOverlayListHead, 161, 121, 320, 240, red, green, blue, alpha);
            break;
        }
        break;
    case 4:
        switch (viewport) {
        case 0:
            draw_filled_rectangle(&gOverlayListHead, 0, 0, 159, 119, red, green, blue, alpha);
            break;
        case 1:
            draw_filled_rectangle(&gOverlayListHead, 161, 0, 320, 119, red, green, blue, alpha);
            break;
        case 2:
            draw_filled_rectangle(&gOverlayListHead, 0, 121, 159, 240, red, green, blue, alpha);
            break;
        case 3:
            draw_filled_rectangle(&gOverlayListHead, 161, 121, 320, 240, red, green, blue, alpha);
            break;
        }
        break;
    }
    command = gOverlayListHead++;
    command->w0 = 0xB8000000;
    command->w1 = 0;
    append_display_list_call_2(gOverlayLists[gOverlayListIndex]);
    gOverlayListIndex = (gOverlayListIndex + 1) & 7;
}
