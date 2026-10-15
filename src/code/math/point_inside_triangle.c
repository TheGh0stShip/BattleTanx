#include "types.h"

typedef struct TriangleVertexRef {
    u16 vertexIndex;
    u16 value;
} TriangleVertexRef;

typedef struct TriangleGeometry {
    u8 pad00[0xC];
    u8 (*vertices)[8];
} TriangleGeometry;

extern TriangleGeometry *gTriangleGeometry __asm__("D_80135834");
extern TriangleVertexRef *get_triangle_vertices(u16 triangleId) __asm__("func_800E09B0");
extern s32 planar_cross_is_negative(void *a, void *b, void *point) __asm__("func_800E0EA8");

s32 point_inside_triangle(void *point, u16 triangleId) __asm__("func_800DE2FC");

s32 point_inside_triangle(void *point, u16 triangleId)
{
    TriangleVertexRef *vertices = get_triangle_vertices(triangleId);
    s32 outside = 0;
    u16 i;

    if (vertices == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        u16 next = (i + 1) % 3;
        if (planar_cross_is_negative(
                gTriangleGeometry->vertices[vertices[i].vertexIndex],
                gTriangleGeometry->vertices[vertices[next].vertexIndex],
                point) == 0) {
            outside = 1;
        }
    }
    return outside ^ 1;
}
