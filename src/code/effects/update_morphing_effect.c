#include "types.h"

/* LDSYM func_800821C0=0x800821C0 */
/* LDSYM func_80085B4C=0x80085B4C */
/* LDSYM func_80090428=0x80090428 */
/* LDSYM func_800905D8=0x800905D8 */
/* LDSYM func_80091A60=0x80091A60 */
/* LDSYM func_800ED8C0=0x800ED8C0 */
/* LDSYM func_80106CCC=0x80106CCC */
/* LDSYM func_80107170=0x80107170 */

typedef struct MorphObject {
    u8 flags;
    u8 pad01[3];
    s32 state;
    u8 pad08[0x40];
    f32 z;
    f32 x;
    u16 angle;
    s16 group;
    u16 model;
    u8 pad56[2];
} MorphObject;

typedef struct MorphGroup {
    u8 kind;
    u8 pad01;
    u16 first;
} MorphGroup;

typedef struct MorphModel {
    u8 pad00[2];
    u16 first;
    u8 pad04[8];
} MorphModel;

typedef struct MorphList {
    u8 count;
    u8 pad01;
    u16 first;
} MorphList;

typedef struct MorphPart {
    s32 value00;
    s32 commands;
    u16 value08;
    u8 pad0A[2];
} MorphPart;

typedef union MorphCommand {
    u64 raw;
} MorphCommand;

typedef struct MorphSession {
    u8 pad000[0x568];
    MorphObject *objects;
    MorphGroup *groups;
    MorphModel *models;
    MorphList *lists;
    MorphPart *parts;
    u8 pad57C[4];
    MorphCommand *commands;
} MorphSession;

typedef struct MorphEffect {
    u8 pad00[0xC];
    u8 flags;
    u8 pad0D;
    u8 stage;
    u8 pad0F;
    s16 frame;
    s16 object;
    s32 area;
    u8 pad18[6];
    u16 debrisValue;
} MorphEffect;

extern MorphSession *get_spawn_session(void) __asm__("func_800821C0");
extern void spawn_oriented_debris(s32, f32 *, u16, u16, u16, u16, s32) __asm__("func_80090428");
extern void spawn_oriented_effect(s32, f32 *, u16, u16, u16, s32, u8) __asm__("func_800905D8");
extern void morph_display_list_vertices(s32, MorphCommand *, MorphCommand *, MorphCommand *) __asm__("func_80091A60");
extern s32 mark_area_at_point(s32, f32, f32) __asm__("func_80085B4C");
extern void spawn_point_burst(f32 *, s32) __asm__("func_800ED8C0");
extern void release_effect_motion(s32) __asm__("func_80107170");
extern void send_effect_message(s32, s32) __asm__("func_80106CCC");

static inline MorphModel *model_at_offset(u8 *models, s32 offset)
{
    return (MorphModel *)(offset + models);
}

void update_morphing_effect(MorphEffect *effect, s32 *state) __asm__("func_8009201C");

void update_morphing_effect(MorphEffect *effect, s32 *state)
{
    f32 position[3];
    MorphObject *object;
    MorphSession *session;
    s32 range;
    MorphGroup *group;
    MorphList *current;
    MorphList *from;
    MorphList *to;
    s32 id;
    s32 i;
    s16 weight;
    s16 frame;
    u16 ci;
    s32 fi;
    s32 ti;
    u16 fromFirst;
    MorphModel *fromModel;
    MorphModel *toModel;
    MorphList *lists;

    if (effect->flags & 2) {
        session = get_spawn_session();
        object = &session->objects[effect->object];
        group = &session->groups[object->group];
        position[0] = object->x;
        *(s32 *)&position[1] = 0;
        position[2] = object->z;
        if (group->kind >= 3) {
            id = group->first + 2;
        } else {
            id = group->first;
        }
        if (effect->flags & 8) {
            spawn_oriented_debris(id, position, 0, object->angle, 0, effect->debrisValue, object->flags & 0xF);
        } else {
            spawn_oriented_effect(id, position, 0, object->angle, 0, object->flags & 0xF, 0);
        }
        object->flags &= 0xF;
        release_effect_motion(effect->area);
        *state = 2;
        return;
    }

    frame = effect->frame + 1;
    range = 225;
    weight = ((range - (15 - frame) * (15 - frame)) << 8) / range;
    effect->frame = frame;
    session = get_spawn_session();
    object = &session->objects[effect->object];
    group = &session->groups[object->group];
    ci = session->models[object->model].first;
    fromModel = model_at_offset((u8 *)session->models, (group->first + effect->stage) * 12);
    toModel = model_at_offset((u8 *)session->models, (effect->stage + group->first) * 12 + 12);
    lists = session->lists;
    fromFirst = fromModel->first;
    fi = fromFirst;
    current = &lists[ci];
    ti = toModel->first;
    from = &lists[fi];
    to = &lists[ti];
    if (current->count != from->count || current->count != to->count) {
        return;
    }

    if (effect->frame == 1) {
        f32 burst[3];

        mark_area_at_point(2, object->x, object->z);
        burst[0] = object->x;
        *(s32 *)&burst[1] = 0;
        burst[2] = object->z;
        spawn_point_burst(burst, 7);
        for (i = 0; i < current->count; i++) {
            register s32 srcIndex __asm__("$3");
            register s32 dstIndex __asm__("$4");
            register MorphPart *parts __asm__("$5");
            register volatile MorphPart *src __asm__("$6");
            register volatile MorphPart *dst __asm__("$7");
            register s32 srcValue __asm__("$3");
            register u16 srcHalf __asm__("$2");
            register s32 dstOffset __asm__("$2");

            srcIndex = to->first;
            dstIndex = current->first;
            parts = session->parts;
            srcIndex += i;
            src = &parts[srcIndex];
            dstIndex += i;
            dstOffset = dstIndex * 3;
            __asm__ volatile ("" : : : "memory");
            srcValue = src->value00;
            dstOffset *= 4;
            dst = (MorphPart *)((u8 *)parts + dstOffset);
            dst->value00 = srcValue;
            srcHalf = src->value08;
            dst->value08 = srcHalf;
        }
    }

    for (i = 0; i < current->count; i++) {
        register MorphPart *parts __asm__("$6");
        MorphCommand *cmds;
        register MorphPart *pc __asm__("$7");
        register MorphPart *pf __asm__("$3");
        register s32 callWeight __asm__("$4");
        s32 pcCommand;
        register s32 pfCommand __asm__("$5");
        register s32 ptCommand __asm__("$6");
        register s32 pcOffset __asm__("$3");
        register s32 ptOffset __asm__("$2");

        callWeight = weight;
        parts = session->parts;
        pcOffset = (current->first + i) * 12;
        pc = (MorphPart *)((u8 *)parts + pcOffset);
        pf = &parts[from->first + i];
        pcCommand = pc->commands;
        ptOffset = (to->first + i) * 12;
        pfCommand = pf->commands;
        parts = (MorphPart *)((u8 *)parts + ptOffset);
        ptCommand = parts->commands;
        cmds = session->commands;
        morph_display_list_vertices(callWeight, &cmds[pfCommand], &cmds[ptCommand], &cmds[pcCommand]);
    }

    if (effect->frame == 15) {
        effect->frame = 0;
        effect->stage++;
        send_effect_message(effect->area, 0x44);
        *state = 1;
        object->state = 0x1C;
    }
}
