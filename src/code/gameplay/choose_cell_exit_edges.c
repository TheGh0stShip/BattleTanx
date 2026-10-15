#include "types.h"

typedef struct ObjectLink {
    u16 value;
    u16 neighbor;
} ObjectLink;

typedef struct EdgeChoice {
    u16 id;
    u16 neighbor;
    s32 open;
    f32 midpoint[2];
    f32 distance;
    u8 pad14[0x4];
} EdgeChoice;

extern ObjectLink *get_object_link_by_id(u32 id) __asm__("func_800E09B0");
extern void get_waypoint_midpoint(u16 edge, f32 *out) __asm__("func_800E0B00");
extern f32 ai_horizontal_distance(f32 *a, f32 *b) __asm__("func_800E0C8C");
extern u8 get_mapped_runtime_status(u16 cell) __asm__("func_800E19DC");

s32 choose_cell_exit_edges(u16 cell, f32 *target, s32 requireNearOpen,
                           s32 requireFarOpen, u16 *nearEdge, u16 *farEdge)
    __asm__("func_800E004C");

s32 choose_cell_exit_edges(u16 cell, f32 *target, s32 requireNearOpen,
                           s32 requireFarOpen, u16 *nearEdge, u16 *farEdge)
{
    EdgeChoice edges[3];
    s32 foundNear;
    ObjectLink *links;
    s32 foundFar;
    f32 nearDistance;
    f32 farDistance;
    u16 nearIndex;
    u16 farIndex;
    u16 otherIndex;
    u16 i;
    s32 open;
    f32 distance;

    links = get_object_link_by_id(cell);
    nearDistance = 16000.0f;
    foundNear = 0;
    foundFar = 0;
    farDistance = 0.01f;
    nearIndex = 0;
    *nearEdge = 0;
    farIndex = 0;
    *farEdge = 0;
    if (links == 0) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        int id = i + cell * 3;
        EdgeChoice *edge;

        open = 0;
        edge = &edges[i];
        edge->id = id;
        edge->neighbor = links[i].neighbor;
        if (edge->neighbor != 0) {
            open = !get_mapped_runtime_status(edge->neighbor / 3);
        }
        edge->open = open;
        get_waypoint_midpoint(id, edge->midpoint);
        edge->distance = distance = ai_horizontal_distance(edge->midpoint, target);
        if (nearDistance < distance) {
            nearDistance = distance;
            nearIndex = i;
        }
        if (farDistance < distance) {
            farDistance = distance;
            farIndex = i;
        }
    }

    if (nearIndex == farIndex) {
        farIndex = (nearIndex + 1) % 3;
    }
    otherIndex = 3 - (nearIndex + farIndex);
    if (!requireNearOpen || edges[nearIndex].open) {
        *nearEdge = edges[nearIndex].id;
        foundNear = 1;
    } else if (edges[otherIndex].open) {
        *nearEdge = edges[otherIndex].id;
        foundNear = 1;
    }
    if (!requireFarOpen || edges[farIndex].open) {
        *farEdge = edges[farIndex].id;
        foundFar = 1;
    } else if (edges[otherIndex].open) {
        *farEdge = edges[otherIndex].id;
        foundFar = 1;
    }
    return foundNear & foundFar;
}
