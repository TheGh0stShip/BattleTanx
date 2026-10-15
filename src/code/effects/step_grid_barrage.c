#include "types.h"

typedef struct PointZX {
    f32 z;
    f32 x;
} PointZX;

typedef struct EntityRecord {
    u8 pad000[0x1AE];
    u8 value1AE;
} EntityRecord;

typedef struct GridBarrage {
    u8 pad00[0xC];
    s32 column;
    s32 row;
    f32 originZ;
    f32 originX;
    f32 stepZ;
    f32 stepX;
    f32 sideZ;
    f32 sideX;
    s32 target;
    u16 value30;
    u8 useEntity;
} GridBarrage;

extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern EntityRecord *get_entity_record(u16 index) __asm__("func_800A6688");
extern void func_800A1408(s32 arg0, s32 arg1, s32 arg2, u16 arg3, PointZX *from, PointZX *to, s32 arg6,
                          s32 arg7, s32 arg8) __asm__("func_800A1408");
extern s32 func_8010DAA0(PointZX *pos, s32 arg1) __asm__("func_8010DAA0");
extern s32 start_sound_scaled_by_listener_distance(s32 soundId, f32 x, f32 z) __asm__("func_80085B4C");

void step_grid_barrage(void *arg, s32 *state) __asm__("func_8010DF90");

void step_grid_barrage(void *arg, s32 *state) {
    GridBarrage *barrage;
    PointZX pos;

    barrage = arg;
    pos.x = barrage->originX + barrage->stepX * (barrage->row + 1) +
            barrage->sideX * ((f32)barrage->column - 2.0f) + random_float_range(60.0f) - 30.0f;
    pos.z = barrage->originZ + barrage->stepZ * (barrage->row + 1) +
            barrage->sideZ * ((f32)barrage->column - 2.0f) + random_float_range(60.0f) - 30.0f;
    if (barrage->useEntity) {
        if ((barrage->column + barrage->row) % 3 == 0) {
            func_800A1408(get_entity_record(barrage->target)->value1AE, barrage->target, 1, barrage->value30,
                          &pos, &pos, 0, 0, 0);
        }
    } else if (func_8010DAA0(&pos, barrage->target) >= 0) {
        start_sound_scaled_by_listener_distance(0x19, pos.x, pos.z);
    }
    if (++barrage->column == 5) {
        barrage->column = 0;
        if (++barrage->row == 5) {
            *state = 2;
        }
    }
}
