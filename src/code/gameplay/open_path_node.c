#include "types.h"

typedef struct PathNode {
    u8 active;
    u8 open;
    u16 parent;
    s16 value04;
    s16 value06;
    f32 pathCost;
    f32 totalCost;
    f32 position[2];
} PathNode;

typedef struct PathGraph {
    PathNode nodes[1];
    u8 pad18[0x11940 - 0x18];
    f32 goal[2];
    u8 pad11948[4];
    u8 *weights;
} PathGraph;

extern s32 classify_object_record_kind(u16 id) __asm__("func_800DF214");
extern s32 get_object_link_by_id(u32 id) __asm__("func_800E09B0");
extern f32 ai_horizontal_distance(f32 *a, f32 *b) __asm__("func_800E0C8C");
extern void compute_waypoint_triangle_centroid(s32 corners, f32 *out) __asm__("func_800E1648");
extern f32 D_800743FC;
extern f32 D_80074400;
extern f32 D_80135840[];

void open_path_node(PathGraph *graph, u16 index, u16 parent) __asm__("func_800DF3A0");
void open_path_node(PathGraph *graph, u16 index, u16 parent) {
    PathNode *node = &graph->nodes[index];
    f32 *position = node->position;
    f32 goalDistance;

    compute_waypoint_triangle_centroid(get_object_link_by_id(index), position);
    node->active = 1;
    node->open = 1;
    node->parent = parent;
    node->value04 = 0;
    node->value06 = 0;
    goalDistance = ai_horizontal_distance(position, graph->goal);
    if (parent == 0) {
        node->pathCost = 0.0f;
    } else {
        PathNode *from = &graph->nodes[parent];
        f32 cost = graph->weights[parent] * D_800743FC + D_80074400 + D_80135840[classify_object_record_kind(parent)];

        node->pathCost = from->pathCost + ai_horizontal_distance(from->position, position) + cost;
    }
    node->totalCost = node->pathCost + goalDistance;
}
