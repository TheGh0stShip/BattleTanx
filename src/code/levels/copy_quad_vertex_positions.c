#include "types.h"

typedef struct VertexXY {
    f32 x;
    f32 y;
} VertexXY;

typedef struct LevelMesh {
    u8 pad00[8];
    u16 vertexCount;
    u8 pad0A[2];
    VertexXY *vertices;
} LevelMesh;

extern LevelMesh *gLevelMesh __asm__("D_80135834");

void copy_quad_vertex_positions(u16 *indices, VertexXY *out) __asm__("func_800E0A84");

void copy_quad_vertex_positions(u16 *indices, VertexXY *out) {
    u16 i;

    for (i = 0; i < 4; i++) {
        VertexXY *vertex;
        VertexXY *dst;
        u16 index = indices[i];

        if (index >= gLevelMesh->vertexCount) {
            vertex = 0;
        } else if (index == 0) {
            vertex = 0;
        } else {
            vertex = &gLevelMesh->vertices[index];
        }
        dst = &out[i];
        dst->y = vertex->y;
        dst->x = vertex->x;
    }
}
