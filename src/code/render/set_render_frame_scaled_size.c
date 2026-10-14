#include "types.h"

typedef struct FrameSizeSource {
    u8 pad00[0x4];
    u16 width;
    u16 height;
} FrameSizeSource;

typedef struct ScaledSizeFrame {
    u8 pad00[0x1A];
    s16 scaledWidth;
    s16 scaledHeight;
    u8 pad1E[0x28 - 0x1E];
    FrameSizeSource *source;
} ScaledSizeFrame;

extern ScaledSizeFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");

void set_render_frame_scaled_size(f32 scaleX, f32 scaleY) __asm__("func_800AB0A4");

void set_render_frame_scaled_size(f32 scaleX, f32 scaleY) {
    ScaledSizeFrame *frame = get_render_frame_record_alt();
    FrameSizeSource *source = frame->source;

    if (source != 0) {
        f32 width = source->width * scaleX;
        f32 height = source->height * scaleY;

        frame->scaledWidth = (s32)width << 6;
        frame->scaledHeight = (s32)height << 6;
    }
}
