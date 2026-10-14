#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef union DisplayCommand {
    struct {
        u8 opcode;
        u8 pad01;
        u16 value02;
        void *value04;
    } vtx;
    struct {
        u32 w0;
        u32 w1;
    } words;
} DisplayCommand;

typedef struct ModelSet {
    u8 pad000[0x580];
    DisplayCommand *commands;
} ModelSet;

typedef struct ModelRef {
    u8 pad00[0x4];
    s32 index;
} ModelRef;

extern Vec3f D_80071C64;
extern Vec3f D_80071C70;
extern f32 D_80071C7C;

extern void expand_vertex_bounds(f32 *max, f32 *min, void *vertices, s32 count) __asm__("func_8008F4EC");

void compute_display_list_center(ModelSet *set, ModelRef *ref, f32 *center) __asm__("func_8008F5D4");

void compute_display_list_center(ModelSet *set, ModelRef *ref, f32 *center) {
    Vec3f min = D_80071C64;
    Vec3f max = D_80071C70;
    DisplayCommand *cmd;

    s32 i;
    f32 scale;

    cmd = &set->commands[ref->index];
    for (i = 0; cmd[i].words.w0 != 0xB8000000; i++) {
        if (cmd[i].vtx.opcode == 4) {
            expand_vertex_bounds(&max.x, &min.x, cmd[i].vtx.value04, cmd[i].vtx.value02 >> 10);
        }
    }
    scale = D_80071C7C;
    center[0] = (min.x + max.x) / scale;
    center[1] = (min.y + max.y) / scale;
    center[2] = (min.z + max.z) / scale;
}
