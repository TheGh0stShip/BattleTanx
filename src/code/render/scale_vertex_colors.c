#include "types.h"

typedef struct ColorVertex {
    s16 position[3];
    u16 flag;
    s16 texCoord[2];
    u8 color[4];
} ColorVertex;

void scale_vertex_colors(s32 count, ColorVertex *vertices, f32 scale) __asm__("func_80086C84");

static inline u32 scale_color_component(u8 component, f32 scale)
{
    f32 scaled = component * scale;

    if (scaled > 255.0f) {
        return 255;
    }
    return scaled;
}

void scale_vertex_colors(s32 count, ColorVertex *vertices, f32 scale)
{
    s32 i;

    for (i = 0; i < count; i++) {
        ColorVertex *vertex = &vertices[i];

        vertex->color[0] = scale_color_component(vertex->color[0], scale);
        vertex->color[1] = scale_color_component(vertex->color[1], scale);
        vertex->color[2] = scale_color_component(vertex->color[2], scale);
    }
}
