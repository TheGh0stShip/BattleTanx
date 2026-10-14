#include "types.h"

typedef struct NodeEntry {
    u8 pad00[8];
    f32 value08;
    u8 pad0C[4];
    f32 position[2];
} NodeEntry;

typedef struct NodeGraph {
    NodeEntry entries[1];
    u8 pad18[0x1194C - 0x18];
    u8 *weights;
} NodeGraph;

typedef struct NodeTarget {
    u8 pad00[0x10];
    f32 position[2];
} NodeTarget;

extern s32 func_800DF214(u16 index);
extern f32 ai_horizontal_distance(f32 *a, f32 *b) __asm__("func_800E0C8C");
extern f32 D_800743F4;
extern f32 D_800743F8;
extern f32 D_80135840[];

f32 compute_path_node_cost(NodeGraph *graph, NodeTarget *target, u16 index) __asm__("func_800DF2DC");

f32 compute_path_node_cost(NodeGraph *graph, NodeTarget *target, u16 index) {
    NodeEntry *entry = &graph->entries[index];
    f32 cost = graph->weights[index] * D_800743F4 + D_800743F8 + D_80135840[func_800DF214(index)];

    return entry->value08 + ai_horizontal_distance(entry->position, target->position) + cost;
}
