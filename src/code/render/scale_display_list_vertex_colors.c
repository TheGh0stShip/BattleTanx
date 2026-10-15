#include "types.h"

typedef struct ColorVertex {
    s16 position[3];
    u16 flag;
    s16 texCoord[2];
    u8 color[4];
} ColorVertex;

typedef struct DisplayCommand {
    u8 opcode;
    u8 pad1;
    u16 vertexInfo;
    ColorVertex *vertices;
} DisplayCommand;

void scale_display_list_vertex_colors(DisplayCommand *command, f32 scale) __asm__("func_80086DC0");

static inline u32 scale_color_component(u8 component, f32 scale)
{
    f32 scaled = component * scale;

    if (scaled > 255.0f) {
        return 255;
    }
    return scaled;
}

void scale_display_list_vertex_colors(DisplayCommand *commands, f32 scale)
{
    s32 n;

    for (n = 0; *(u32 *)&commands[n] != 0xB8000000; n++) {
        if (commands[n].opcode == 4) {
            s32 count = commands[n].vertexInfo >> 10;
            ColorVertex *vertices = commands[n].vertices;
            s32 i;

            for (i = 0; i < count; i++) {
                ColorVertex *vertex = &vertices[i];

                vertex->color[0] = scale_color_component(vertex->color[0], scale);
                vertex->color[1] = scale_color_component(vertex->color[1], scale);
                vertex->color[2] = scale_color_component(vertex->color[2], scale);
            }
        }
    }
}
