#include "types.h"

typedef struct LevelModelTransform {
    f32 m[4][4];
    s32 value40;
} LevelModelTransform;

typedef struct GroundPoint {
    f32 z;
    f32 x;
} GroundPoint;

typedef struct KindModelObject {
    u8 pad00[0xC];
    s32 kind;
    s32 x;
    s32 y;
    s32 z;
    u16 angle;
    u8 pad1E[7];
    u8 variant;
    u8 value26;
} KindModelObject;

extern LevelModelTransform D_80072AE0;
extern f32 D_80072B24;
extern s16 D_802D5A30[];

extern s32 get_spawn_session(void) __asm__("func_800821C0");
extern void set_yaw_transform(LevelModelTransform *xf, s32 x, s32 y, s32 z, u16 angle) __asm__("func_800A7744");
extern void submit_level_model_at_point(s32 world, s16 model, LevelModelTransform *xf, s32 a3, s32 mode, s32 a5,
                                        GroundPoint *point, f32 scale) __asm__("func_80084CC4");

void draw_kind_selected_level_model(void *arg) __asm__("func_800A05A0");

void draw_kind_selected_level_model(void *arg) {
    GroundPoint point;
    LevelModelTransform transform = D_80072AE0;
    KindModelObject *obj = arg;
    s32 model;

    point.x = *(f32 *)&obj->x;
    point.z = *(f32 *)&obj->z;
    switch ((u32)obj->kind) {
        case 0:
            model = D_802D5A30[0x15];
            break;
        case 2:
            model = D_802D5A30[0x2F];
            break;
        case 1:
            if (obj->variant != 0) {
                model = D_802D5A30[0x48];
            } else {
                model = D_802D5A30[0x23];
            }
            break;
        default:
            model = 0;
            break;
    }
    set_yaw_transform(&transform, obj->x, obj->y, obj->z, obj->angle);
    submit_level_model_at_point(get_spawn_session(), model, &transform, 0, 3, obj->value26, &point, D_80072B24);
}
