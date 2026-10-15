#include "types.h"

typedef struct PlanarPoint {
    f32 x;
    f32 y;
} PlanarPoint;

typedef struct CellCorner {
    u16 vertex;
    u16 value02;
} CellCorner;

typedef struct LevelMesh {
    u8 pad00[8];
    u16 vertexCount;
    u16 cellCount;
    PlanarPoint *vertices;
} LevelMesh;

extern LevelMesh *gLevelMesh __asm__("D_80135834");
extern u8 func_800E19DC(u16 cell);
extern CellCorner *func_800E09B0(u16 cell);
extern f32 ai_horizontal_distance(PlanarPoint *a, PlanarPoint *b) __asm__("func_800E0C8C");

u16 find_nearest_level_cell(PlanarPoint *point) __asm__("func_800E05A4");

u16 find_nearest_level_cell(PlanarPoint *point)
{
    PlanarPoint center;
    CellCorner *corners;
    PlanarPoint *vertex;
    CellCorner *corner;
    u16 nearestDist;
    f32 nearest;
    u16 cell;
    u16 i;
    f32 dist;

    nearestDist = 16000;
    nearest = 0.0f;
    for (cell = 1; cell < gLevelMesh->cellCount; cell++) {
        if (func_800E19DC(cell)) {
            continue;
        }
        corners = func_800E09B0(cell);
        center.y = 0.0f;
        center.x = 0.0f;
        for (i = 0; i < 3; i++) {
            corner = &corners[i];
            vertex = &gLevelMesh->vertices[corner->vertex];
            center.y += vertex->y;
            center.x += vertex->x;
        }
        center.y /= 3.0f;
        center.x /= 3.0f;
        dist = ai_horizontal_distance(point, &center);
        if (dist < nearestDist) {
            nearestDist = dist;
            nearest = cell;
        }
    }
    return nearest;
}
