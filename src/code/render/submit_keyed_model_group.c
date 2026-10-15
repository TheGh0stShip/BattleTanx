#include "types.h"

typedef struct ModelGroupRef {
    u8 lodMode;
    u8 pad01;
    u16 group;
    u8 pad04[0x8];
} ModelGroupRef;

typedef struct ModelGroup {
    u8 count;
    u8 pad01;
    u16 first;
} ModelGroup;

typedef struct ModelPart {
    u32 frame;
    u32 part;
    u16 animation;
    u8 pad0A[0x2];
} ModelPart;

typedef struct SectorPoint {
    u8 pad00[0x20];
    f32 value20;
    f32 value24;
    u8 pad28[4];
} SectorPoint;

typedef struct ModelSession {
    u8 pad000[0x570];
    ModelGroupRef *refs;
    ModelGroup *groups;
    ModelPart *modelParts;
    u8 (*frames)[8];
    u8 (*parts)[8];
    SectorPoint points[4];
} ModelSession;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void *func_8008067C(s32 arg0, s32 arg1, void *part);
extern s32 add_keyed_pool_item(void *key, void *value, f32 *position, f32 a, f32 b, u16 c, s32 list, s32 table)
    __asm__("func_80080910");
extern s32 test_point_outside_sector(f32 x, f32 y, f32 r, SectorPoint *point) __asm__("func_800941E0");
extern s32 D_801C9174;

void submit_keyed_model_group(ModelSession *session, s32 index, f32 *pos, s32 table, f32 a, f32 b, u16 c,
                              s32 arg7, s32 arg8, f32 radius) __asm__("func_80084F90");

void submit_keyed_model_group(ModelSession *session, s32 index, f32 *pos, s32 table, f32 a, f32 b, u16 c,
                              s32 arg7, s32 arg8, f32 radius)
{
    f32 center[2];
    u8 mask = 0;
    s32 count = get_difficulty_level();
    s32 i;
    s32 j;
    ModelGroupRef *ref;
    ModelGroup *group;
    ModelPart *modelPart;
    void *part;

    for (i = 0; i < count; i++) {
        f32 x = pos[0];
        SectorPoint *point = &session->points[i];
        f32 dx = point->value24 - x;
        f32 y = pos[2];
        f32 dy = point->value20 - y;
        s32 inRange = 0;

        if (dx * dx + dy * dy < D_801C9174) {
            inRange = 1;
        }
        if (inRange && test_point_outside_sector(x, y, radius, point) == 0) {
            mask |= 1 << i;
        }
    }
    if (mask == 0) {
        return;
    }
    if (index == -1) {
        return;
    }
    ref = &session->refs[index];
    center[1] = pos[0];
    center[0] = pos[2];
    group = &session->groups[ref->group];
    if (arg8 > 0) {
        for (j = 0; j < group->count; j++) {
            modelPart = &session->modelParts[group->first + j];
            part = func_8008067C(arg7, arg8, session->parts[modelPart->part]);
            for (i = 0; i < 4; i++) {
                if ((mask >> i) & 1) {
                    modelPart = &session->modelParts[group->first + j];
                    add_keyed_pool_item(session->frames[modelPart->frame], part, pos,
                                        a, b, c, i, table);
                }
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if ((mask >> i) & 1) {
                for (j = 0; j < group->count; j++) {
                    modelPart = &session->modelParts[group->first + j];
                    add_keyed_pool_item(session->frames[modelPart->frame], session->parts[modelPart->part], pos,
                                        a, b, c, i, table);
                }
            }
        }
    }
}
