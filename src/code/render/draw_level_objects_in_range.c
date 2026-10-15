#include "types.h"

typedef struct LevelCamera {
    f32 z;
    f32 x;
    u8 mode;
    u8 pad09[0x23];
} LevelCamera;

typedef struct LevelGroup {
    u8 pad00[0x2];
    u16 object;
    f32 x0;
    f32 z0;
    f32 x1;
    f32 z1;
    s32 key;
} LevelGroup;

typedef struct LevelObject {
    u8 flags;
    u8 mode;
    u8 pad02[0x2];
    u32 kind;
    u8 transform[0x4C];
    u16 model;
    u8 pad56[0x2];
} LevelObject;

typedef struct LevelState {
    u8 pad000[0x564];
    LevelGroup *groups;
    LevelObject *objects;
    u8 pad56C[0x38];
    LevelCamera cameras[4];
    u8 pad654[0x0];
} LevelState;

typedef struct LevelCounts {
    u8 pad000[0x634];
    s32 objectCount;
    s32 groupCount;
} LevelCounts;

#define OBJECT_PHASE(obj) ((((obj)->flags & 0xF) < 14) ? ((obj)->flags & 0xF) : ((obj)->flags & 0xF) - 16)

extern void reset_slot_record_table(void) __asm__("func_8009491C");
extern s32 get_view_count(void) __asm__("func_8007AAA0");
extern void query_rect_edges_outside_zone(s32 x0, s32 z0, s32 x1, s32 z1, s32 arg4, s32 arg5, s32 key)
    __asm__("func_800953AC");
extern s32 collect_unique_slot_ids(s32 *out, s32 index) __asm__("func_80095C1C");
extern s32 test_rect_edges_facing_listener(s32 x0, s32 z0, s32 x1, s32 z1, s32 mode, s32 view)
    __asm__("func_80095F30");
extern void submit_model_group_view(LevelState *level, s32 index, s32 arg2, void *transform, s32 layer,
                                    s32 phase, s32 view) __asm__("func_800824E4");
extern void submit_model_group_view_layered(LevelState *level, s32 index, s32 arg2, void *transform, s32 layer,
                                            s32 lastLayer, s32 phase, s32 view) __asm__("func_800827AC");

extern s32 D_80125858;
extern s32 D_801C9174;
extern s32 D_801C9178;
extern void set_object_cull_range(s32 range) __asm__("func_800A5EB0");
extern void query_rect_edges_in_range(s32 x0, s32 z0, s32 x1, s32 z1, s32 mode, s32 object, s32 view, s32 range,
                                      s32 rangeSq)
    __asm__("func_80095768");
extern s32 test_rect_edges_in_range(s32 x0, s32 z0, s32 x1, s32 z1, s32 mode, s32 view, s32 range, s32 rangeSq)
    __asm__("func_800962B4");

static inline void submit_level_object(LevelState *level, LevelObject *obj, s32 view)
{
    switch (obj->kind) {
    case 0:
        submit_model_group_view(level, obj->model, 0, obj->transform, 0, OBJECT_PHASE(obj), view);
        break;
    case 0x1C:
        submit_model_group_view(level, obj->model, 0, obj->transform, 6, OBJECT_PHASE(obj), view);
        break;
    case 0x1D:
        submit_model_group_view_layered(level, obj->model, 0, obj->transform, 2, 6, OBJECT_PHASE(obj), view);
        break;
    default:
        submit_model_group_view(level, obj->model, 0, obj->transform, 2, OBJECT_PHASE(obj), view);
        break;
    }
}

void draw_level_objects_in_range(LevelState *level) __asm__("func_80083394");

void draw_level_objects_in_range(LevelState *level)
{
    s32 view[4][2];
    s32 state[4] = { 0, 0, 0, 0 };
    s32 modes[4];
    s32 range[4][2];
    s32 slots[256];
    s32 views;
    s32 objectCount;
    s32 groupCount;
    LevelObject *objects;
    LevelGroup *groups;
    LevelGroup *group;
    LevelObject *obj;
    s32 key;
    s32 minLo;
    s32 done;
    s32 g;
    s32 i;
    s32 k;
    s32 count;
    s32 zoneFlags;
    f32 *rect;

    done = 0;
    minLo = 1000000;
    if (D_801C9178 != D_80125858) {
        D_801C9178 = D_80125858;
        D_801C9174 = D_80125858 * D_80125858;
        set_object_cull_range(D_80125858);
    }
    i = 0;
    reset_slot_record_table();
    views = get_view_count();
    objectCount = ((LevelCounts *)level)->objectCount;
    groupCount = ((LevelCounts *)level)->groupCount;
    groups = level->groups;
    objects = level->objects;
    for (i = 0; i < views; i++) {
        view[i][0] = level->cameras[i].x;
        view[i][1] = level->cameras[i].z;
        range[i][0] = view[i][0] - D_80125858 - 450;
        range[i][1] = view[i][0] + D_80125858 + 450;
        if (range[i][0] < minLo) {
            minLo = range[i][0];
        }
        modes[i] = level->cameras[i].mode;
    }
    for (g = 0; g < groupCount && groups[g].key < minLo; g++) {
    }
    for (; g < groupCount; g++) {
        group = &groups[g];
        key = group->key;
        obj = &objects[group->object];
        for (i = 0; i < views; i++) {
            if (state[i] == 0 && key >= range[i][0]) {
                state[i] = modes[i] != 0 ? 2 : 1;
            }
            switch (state[i]) {
            case 1:
                    if (range[i][1] < key) {
                        state[i] = 3;
                        if (++done == views) {
                            goto pass1_done;
                        }
                        continue;
                    }
                    zoneFlags = obj->mode;
                    if ((zoneFlags & 0x80) && ((obj->flags >> (i + 4)) & 1)) {
                        query_rect_edges_in_range(group->x0, group->z0, group->x1, group->z1, zoneFlags & ~0x80,
                                                  group->object, i, D_80125858, D_801C9174);
                    }

                break;
            case 2:
                    if (range[i][1] < key) {
                        state[i] = 3;
                        if (++done == views) {
                            goto pass1_done;
                        }
                        continue;
                    }
                    zoneFlags = obj->mode;
                    if (!(zoneFlags & 0x80)) {
                        continue;
                    }
                    zoneFlags &= ~0x80;
                    if (zoneFlags >= 2 && ((obj->flags >> (i + 4)) & 1)) {
                        query_rect_edges_in_range(group->x0, group->z0, group->x1, group->z1, zoneFlags, group->object,
                                                  i, D_80125858, D_801C9174);
                    }
                break;
            }
        }
    }
pass1_done:
    for (i = 0; i < views; i++) {
        count = collect_unique_slot_ids(slots, i);
        for (k = 0; k < count; k++) {
            obj = &objects[slots[k]];
            submit_model_group_view(level, obj->model, 0, obj->transform, 2, OBJECT_PHASE(obj), i);
        }
    }
    done = 0;
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    state[3] = 0;
    for (g = 0; g < groupCount && groups[g].key < minLo; g++) {
    }
    for (; g < groupCount; g++) {
        group = &groups[g];
        key = group->key;
        obj = &objects[group->object];
        rect = &group->x0;
        for (i = 0; i < views; i++) {
            if (state[i] == 0 && key >= range[i][0]) {
                state[i] = modes[i] != 0 ? 2 : 1;
            }
            switch (state[i]) {
            case 1:
                    if (range[i][1] < key) {
                        state[i] = 3;
                        if (++done == views) {
                            goto pass2_done;
                        }
                    } else if (!(obj->mode & 0x80) && ((obj->flags >> (i + 4)) & 1) &&
                               test_rect_edges_in_range(rect[0], rect[1], rect[2], rect[3], obj->mode & ~0x80, i,
                                                        D_80125858, D_801C9174)) {
                        submit_level_object(level, obj, i);
                    }

                break;
            case 2:
                    if (range[i][1] < key) {
                        state[i] = 3;
                        if (++done == views) {
                            goto pass2_done;
                        }
                    } else if ((!(obj->mode & 0x80) || (obj->mode & ~0x80) == 1) && ((obj->flags >> (i + 4)) & 1) &&
                               test_rect_edges_in_range(rect[0], rect[1], rect[2], rect[3], obj->mode & ~0x80, i,
                                                        D_80125858, D_801C9174)) {
                        submit_level_object(level, obj, i);
                    }
                break;
            }
        }
    }
pass2_done:
    done = 0;
    state[0] = 0;
    state[1] = 0;
    state[2] = 0;
    state[3] = 0;
    for (g = groupCount; g < objectCount && groups[g].key < minLo; g++) {
    }
    for (; g < objectCount; g++) {
        group = &groups[g];
        obj = &objects[group->object];
        if (obj->flags == 0) {
            continue;
        }
        key = group->key;
        rect = &group->x0;
        for (i = 0; i < views; i++) {
            switch (state[i]) {
            case 0:
                if (key < range[i][0]) {
                    break;
                }
                state[i] = 1;
            case 1:
                if (range[i][1] < key) {
                    state[i] = 3;
                    if (++done == views) {
                        return;
                    }
                    break;
                }
                if (((obj->flags >> (i + 4)) & 1) &&
                    test_rect_edges_in_range(rect[0], rect[1], rect[2], rect[3], obj->mode & 0x7F, i,
                                             D_80125858, D_801C9174)) {
                    submit_level_object(level, obj, i);
                }
                break;
            }
        }
    }
}
