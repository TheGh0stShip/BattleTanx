#include "types.h"

typedef struct BoundsVertex {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[0xA];
} BoundsVertex;

void expand_vertex_bounds(f32 *max, f32 *min, BoundsVertex *vertices, s32 count) __asm__("func_8008F4EC");

void expand_vertex_bounds(f32 *max, f32 *min, BoundsVertex *vertices, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (vertices[i].x < min[0]) {
            min[0] = vertices[i].x;
        }
        if (vertices[i].y < min[1]) {
            min[1] = vertices[i].y;
        }
        if (vertices[i].z < min[2]) {
            min[2] = vertices[i].z;
        }
        if (max[0] < vertices[i].x) {
            max[0] = vertices[i].x;
        }
        if (max[1] < vertices[i].y) {
            max[1] = vertices[i].y;
        }
        if (max[2] < vertices[i].z) {
            max[2] = vertices[i].z;
        }
    }
}
