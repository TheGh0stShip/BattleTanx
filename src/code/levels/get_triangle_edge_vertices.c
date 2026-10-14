#include "types.h"

typedef struct MeshCorner {
    u16 vertex;
    u16 value02;
} MeshCorner;

typedef struct MeshVertex {
    u8 pad00[0x8];
} MeshVertex;

typedef struct Mesh {
    u8 pad00[0x8];
    u16 vertexCount;
    u8 pad0A[0x2];
    MeshVertex *vertices;
    MeshCorner *corners;
} Mesh;

extern Mesh *D_80135834;

static inline MeshVertex *mesh_vertex(u16 *index)
{
    if (*index >= D_80135834->vertexCount) {
        return 0;
    }
    if (*index == 0) {
        return 0;
    }
    return &D_80135834->vertices[*index];
}

void get_triangle_edge_vertices(u16 corner, MeshVertex **start, MeshVertex **end) __asm__("func_800E18B0");

void get_triangle_edge_vertices(u16 corner, MeshVertex **start, MeshVertex **end)
{
    u16 first;
    u16 second;
    u16 offset;
    u16 next;

    offset = corner % 3;
    next = (offset + 1) % 3 + (corner - offset);
    first = D_80135834->corners[corner].vertex;
    second = D_80135834->corners[next].vertex;
    *start = mesh_vertex(&first);
    *end = mesh_vertex(&second);
}
