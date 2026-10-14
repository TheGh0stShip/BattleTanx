#include "types.h"

typedef struct FrameVertexSource {
    u16 s;
    u16 t;
    f32 x;
    f32 y;
    f32 z;
} FrameVertexSource;

typedef struct FrameVertex {
    s16 ob[3];
    u16 flag;
    s16 tc[2];
    u8 cn[4];
} FrameVertex;

typedef struct FrameVertexRecord {
    u8 pad00[0xC];
    FrameVertex *vertices;
    u8 pad10[0x4];
    s16 overflow;
    u8 pad16[0x2];
    u16 totalVertices;
    u8 pad1A[0x4];
    u8 color[4];
    u8 pad22[0xA];
    u16 vertexCount;
} FrameVertexRecord;

extern FrameVertexRecord *get_render_frame_record_alt(void) __asm__("func_8007F060");

void push_frame_vertices(u16 count, FrameVertexSource *source) __asm__("func_800AA168");

void push_frame_vertices(u16 count, FrameVertexSource *source)
{
    FrameVertexRecord *record;
    FrameVertex *vertex;
    s32 i;
    u8 *color;

    record = get_render_frame_record_alt();
    if (record->vertexCount + count >= 0x20) {
        record->overflow = 1;
        return;
    }
    color = record->color;
    vertex = &record->vertices[record->vertexCount];
    for (i = 0; i < count; i++) {
        vertex->ob[0] = source->x;
        vertex->ob[1] = source->y;
        vertex->ob[2] = source->z;
        vertex->tc[0] = source->s << 6;
        vertex->tc[1] = source->t << 6;
        vertex->cn[0] = color[0];
        vertex->cn[1] = color[1];
        vertex->cn[2] = color[2];
        vertex->cn[3] = color[3];
        vertex++;
        source++;
    }
    record->totalVertices += count;
    record->vertexCount += count;
}
