#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct RenderFrame {
    GfxCommand *main;
    GfxCommand *overlay;
    u8 pad08[0x1C];
    GfxCommand *pendingCall;
} RenderFrame;

#define GFX_ENDDL_WORD 0xB8000000
#define GFX_DL_BRANCH_WORD 0x06010000

extern RenderFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");

void close_overlay_display_list(void) __asm__("func_800AB1A0");

void close_overlay_display_list(void)
{
    RenderFrame *frame;
    GfxCommand *command;

    frame = get_render_frame_record_alt();
    if (frame->pendingCall != 0) {
        command = frame->overlay++;
        command->w0 = GFX_ENDDL_WORD;
        command->w1 = 0;
        command = frame->pendingCall;
        command->w0 = GFX_DL_BRANCH_WORD;
        command->w1 = (u32)frame->overlay;
        frame->pendingCall = 0;
    }
}
