#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct OverlayFrame {
    GfxCommand *main;
    GfxCommand *overlay;
} OverlayFrame;

#define GFX_DISPLAY_LIST_WORD 0x06000000

extern OverlayFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");
extern u8 D_80126770[];
extern u8 D_801267D8[];
extern u8 D_80126838[];
extern u8 D_801268A0[];
extern u8 D_80126900[];
extern u8 D_80126968[];
extern u8 D_801269E0[];

void push_overlay_display_list_variant(u16 variant) __asm__("func_800AA3D0");

void push_overlay_display_list_variant(u16 variant) {
    OverlayFrame *frame;
    GfxCommand *command;

    frame = get_render_frame_record_alt();
    switch (variant) {
        case 0:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_80126770;
            break;
        case 1:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_801267D8;
            break;
        case 2:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_80126838;
            break;
        case 3:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_801268A0;
            break;
        case 4:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_80126900;
            break;
        case 5:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_80126968;
            break;
        case 6:
            command = frame->overlay;
            frame->overlay = command + 1;
            command->w0 = GFX_DISPLAY_LIST_WORD;
            command->w1 = (u32)D_801269E0;
            break;
    }
}
