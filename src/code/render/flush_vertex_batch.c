#include "types.h"

typedef struct GfxCommand {
    u32 w0;
    u32 w1;
} GfxCommand;

typedef struct BatchVertex {
    u8 bytes[0x10];
} BatchVertex;

typedef struct VertexBatchFrame {
    GfxCommand *main;
    GfxCommand *overlay;
    u8 pad08[0x4];
    BatchVertex *vertices;
    u8 pad10[0x4];
    u16 overflow;
    u16 first;
    u16 count;
} VertexBatchFrame;

/* F3DEX G_VTX: count in bits 10-15, byte length minus one in the low halfword. */
#define GFX_VERTEX_WORD(count) (0x04000000 | ((((count) << 10) | ((count) * (s32)sizeof(BatchVertex) - 1)) & 0xFFFF))
#define GFX_SEGMENT_ADDRESS(address) ((u32)(address) - 0x80000000)

extern VertexBatchFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");

void flush_vertex_batch_main(void) __asm__("func_800A9C48");
void flush_vertex_batch_overlay(void) __asm__("func_800A9CC4");

void flush_vertex_batch_main(void)
{
    VertexBatchFrame *frame;
    GfxCommand *command;
    BatchVertex *vertices;
    u32 count;
    u32 first;

    frame = get_render_frame_record_alt();
    if (frame->overflow == 0) {
        command = frame->main;
        count = frame->count;
        first = frame->first;
        frame->main = command + 1;
        vertices = frame->vertices;
        command->w0 = GFX_VERTEX_WORD(count);
        command->w1 = GFX_SEGMENT_ADDRESS(&vertices[first]);
    }
}

void flush_vertex_batch_overlay(void)
{
    VertexBatchFrame *frame;
    GfxCommand *command;
    BatchVertex *vertices;
    u32 count;
    u32 first;

    frame = get_render_frame_record_alt();
    if (frame->overflow == 0) {
        command = frame->overlay;
        count = frame->count;
        first = frame->first;
        frame->overlay = command + 1;
        vertices = frame->vertices;
        command->w0 = GFX_VERTEX_WORD(count);
        command->w1 = GFX_SEGMENT_ADDRESS(&vertices[first]);
    }
}
