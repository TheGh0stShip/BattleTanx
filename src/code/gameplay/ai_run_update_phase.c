#include "types.h"

typedef struct LinkedObject {
    u8 pad00[8];
    s32 type;
    u8 pad0C[0x22];
    u16 ownerId;
} LinkedObject;

typedef struct Unit {
    u8 pad00;
    u8 active;
    u8 pad02[0x34A];
    LinkedObject *linked;
    u8 pad350[8];
    u8 linkedFlag;
    u8 pad359[0xB];
    s32 linkTime;
} Unit;

typedef struct Task {
    u8 pad00[0xC];
    s32 state;
} Task;

extern Unit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern void func_800E4AA4();
extern void update_unit_pairings(s32 arg0, s32 arg1) __asm__("func_800E5BA0");
extern void ai_update_units_round_robin(u16 arg0, void *arg1, s32 *budget) __asm__("func_800E63F4");
extern void ai_set_indexed_float(Unit *base, s32 key, f32 value) __asm__("func_800E986C");
extern u16 D_80135894;
extern u8 D_8033A980[];
extern s16 D_8033AAE0;
extern u8 D_8033B44A;
extern s16 D_8033B44C;
extern s16 D_8033B5E0;

static inline LinkedObject *get_linked_object(Unit *unit)
{
    LinkedObject *obj = unit->linked;

    if (obj == 0 || obj->type != 0x1B) {
        return 0;
    }
    return obj;
}

void ai_run_update_phase(Task *task, s32 *state) __asm__("func_800E6754");

void ai_run_update_phase(Task *task, s32 *state) {
    s32 flag;
    s16 i;
    Unit *unit;
    LinkedObject *obj;
    LinkedObject *linked;
    s32 match;
    s16 count;

    if (task->state == 2) {
        *state = task->state;
    }
    if (D_8033AAE0 > 0) {
        D_8033AAE0--;
    } else {
        D_8033AAE0 = 500;
        D_8033B44A = D_8033B44A == 0;
    }
    switch (D_8033B5E0) {
    case 0:
        update_unit_pairings(1, 0);
        D_8033B5E0++;
        break;
    case 1:
        update_unit_pairings(0, 1);
        for (i = 0; i < 20; i++) {
            unit = get_unit(i);
            if (unit->active != 0) {
                linked = get_linked_object(unit);
                match = 0;
                if (linked != 0 && linked->ownerId == i) {
                    match = 1;
                }
                if (match != unit->linkedFlag) {
                    if (match) {
                        ai_set_indexed_float(unit, 0x1002, 1.0f);
                        unit->linkTime = get_frame_time();
                        unit->linkedFlag = 1;
                    } else {
                        unit->linked = 0;
                        unit->linkedFlag = 0;
                    }
                }
            }
        }
        D_8033B5E0++;
        break;
    case 2:
        func_800E4AA4();
        D_8033B5E0++;
        break;
    case 3:
        count = D_8033B44C;
        if (count > 0) {
            flag = 0;
            D_8033B44C = count - 1;
        } else {
            flag = 1;
            D_8033B44C = 3;
        }
        ai_update_units_round_robin(D_80135894, D_8033A980, &flag);
        D_8033B5E0 = 0;
        break;
    }
}
