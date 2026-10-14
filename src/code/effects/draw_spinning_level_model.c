#include "types.h"

typedef struct LevelModelTransform {
    f32 m[4][4];
    s32 value40;
} LevelModelTransform;

typedef struct EntityRecord {
    u8 pad000[0x1AE];
    u8 value1AE;
} EntityRecord;

typedef struct SpinningModel {
    u8 pad00[0xC];
    s32 value0C;
    s32 value10;
    u16 angle;
    u8 pad16[2];
    s32 modelSlot;
    u8 pad1C[8];
    s32 value24;
    u8 pad28[4];
    s32 owner;
    u8 visibleMask;
} SpinningModel;

extern LevelModelTransform D_80071E20;
extern s16 D_802D5A30[];
extern s32 D_80125CE0[];

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void set_yaw_transform(LevelModelTransform *xf, s32 x, s32 y, s32 z, u16 angle) __asm__("func_800A7744");
extern void submit_masked_level_model(s32 world, s16 model, LevelModelTransform *xf, s32 mode, s32 a4, s32 *pos, s32 mask)
    __asm__("func_80084B90");

void draw_spinning_level_model(void *arg) __asm__("func_80090F94");

void draw_spinning_level_model(void *arg) {
    LevelModelTransform transform = D_80071E20;
    SpinningModel *obj = arg;
    u16 i;

    obj->angle += 0x600;
    if (obj->value24 == 0) {
        if (obj->visibleMask == 0xFF) {
            if (obj->owner == -1) {
                obj->visibleMask = 0xF;
            } else {
                obj->visibleMask = 0;
                for (i = 0; i < get_difficulty_level(); i++) {
                    if (get_entity_record(i)->value1AE != obj->owner) {
                        obj->visibleMask |= 1 << i;
                    }
                }
            }
        }
        set_yaw_transform(&transform, obj->value10, 0, obj->value0C, obj->angle);
        submit_masked_level_model(get_spawn_session(), D_802D5A30[D_80125CE0[obj->modelSlot]], &transform, 3, 0,
                                  &obj->value0C, obj->visibleMask);
    }
}
