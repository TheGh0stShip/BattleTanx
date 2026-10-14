#include "types.h"

typedef struct MarkerVec3 {
    f32 x;
    f32 y;
    f32 z;
} MarkerVec3;

typedef struct MarkerTransform {
    s32 words[17];
} MarkerTransform;

typedef struct MarkerTimer {
    u8 pad00[0x8];
    s32 value08;
    u8 *value0C;
} MarkerTimer;

typedef struct MarkerEntity {
    u8 pad00[0xD];
    u8 ownerId;
    u8 pad0E[0x2];
    s32 state;
    u8 pad14[0x8];
    f32 value1C;
    f32 value20;
    u8 pad24[0x4];
    MarkerTimer *timer;
} MarkerEntity;

typedef struct MarkerOwner {
    u8 pad000[0x1AE];
    u8 value1AE;
} MarkerOwner;

typedef struct MarkerMode {
    u8 pad00[0x4];
    s32 value04;
} MarkerMode;

extern MarkerTransform D_80073054;
extern f32 D_80073098;
extern f32 D_8007309C;
extern f32 D_800730A0;
extern f32 D_800730A4;
extern u8 D_80135776;
extern u32 D_801B4AA0;
extern s16 D_802D5A30[];
extern s16 D_802D5A60;

extern MarkerMode *func_8007AAF4(void);
extern void *func_800821C0(void);
extern void func_80084CC4(void *context, s16 id, MarkerTransform *transform, s32 arg3, s32 arg4, s32 arg5,
                          f32 *position, f32 scale);
extern void func_80084F90(void *context, s16 id, MarkerVec3 *position, s32 arg3, f32 arg4, f32 arg5, s32 arg6,
                          s32 arg7, s32 arg8, f32 arg9);
extern MarkerOwner *func_800A6688(u8 id);
extern void func_800A70BC(MarkerEntity *entity);
extern void func_800A7744(MarkerTransform *transform, MarkerVec3 position, u16 angle);
extern void func_800A823C(MarkerTransform *transform, f32 x, f32 y, f32 z);

void draw_marker_entity(MarkerEntity *entity) __asm__("func_800A6BE0");

void draw_marker_entity(MarkerEntity *entity)
{
    MarkerVec3 position;
    MarkerTransform transform;
    MarkerTransform *xf;
    MarkerEntity *self;
    void *context;
    s32 index;
    s32 state;

    self = entity;
    state = entity->state;
    if (state != 1) {
        if (state != 0) {
            if (state != 2) {
                return;
            }
        }
        position.x = entity->value20;
        position.z = entity->value1C;
        position.y = 0;
        context = func_800821C0();
        index = 0x5F - func_800A6688(entity->ownerId)->value1AE;
        if (func_8007AAF4()->value04 == 0x10 && entity->ownerId != 0) {
            index = 0xB3;
        }
        if (D_80135776 != 0) {
            transform = D_80073054;
            xf = &transform;
            func_800A7744(xf, position, (D_801B4AA0 % 30) * 0x888);
            func_800A823C(xf, D_80073098, D_80073098, D_80073098);
            func_80084CC4(context, D_802D5A60, xf, 0, 2, 0, &self->value1C, D_8007309C);
        } else {
            func_80084F90(context, D_802D5A30[index], &position, 0, D_800730A0, D_800730A0, 0, 0, 0, D_800730A4);
        }
    } else if (self->timer->value08 == 0 && self->timer->value0C[1] == 0) {
        func_800A70BC(self);
    }
}
