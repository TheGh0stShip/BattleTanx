#include "types.h"

typedef struct SessionSlot {
    u8 pad00;
    s8 value01;
    u8 pad02[0x2];
    s32 mode;
    u8 pad08[0x4C];
    u16 value54;
    u8 pad56[0x2];
} SessionSlot;

typedef struct SlotSession {
    u8 pad000[0x568];
    SessionSlot *slots;
} SlotSession;

typedef struct Obj {
    u8 pad00[0xC];
    f32 pos[3];
    s16 slot;
    u8 pad1A[0x2];
    u8 triggered;
    u8 pad1D[0x3];
    s32 record;
    u8 burst;
} Obj;

extern SlotSession *func_800821C0(void);
extern void func_8008F248(void *, s32, s32, f32, f32, f32, s32);
extern void func_800ED8C0(f32 *pos, s32 kind);
extern void func_800F1E74(f32 *);
extern void func_800F2E50(s32, s32, s32, s32, s32);
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern s32 radians_to_angle(f32 radians) __asm__("func_800F3BE4");
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern void func_80108E74(s32, void *);
extern f32 sqrtf(f32);
extern f32 D_80074B14;
extern f32 D_80074B18;
extern f32 D_80074B1C;
extern f32 D_80074B20;

void trigger_slot_point_burst(Obj *obj, s32 unused, f32 *target) __asm__("func_800ED5C8");

void trigger_slot_point_burst(Obj *obj, s32 unused, f32 *target)
{
    f32 pt[3];
    u8 buf[0x20];
    SessionSlot *slot;
    f32 dz;
    f32 dx;
    f32 len;
    f32 ndx;
    s32 angle;
    s32 i;
    s32 nonzero;
    s32 nonzeroX;
    f32 range;
    f32 bias;

    if (obj->triggered == 0) {
        obj->triggered = 1;
        slot = &func_800821C0()->slots[obj->slot];
        slot->value01 = 1;
        slot->mode = 0x1C;
        slot->value54++;
        clear_record_halfword_flags(obj->record, 0x5D);
        dz = target[1] - obj->pos[0];
        dx = target[0] - obj->pos[2];
        nonzero = dz != 0.0f;
        nonzeroX = dx != 0.0f;
        angle = 0;
        if (nonzero | nonzeroX) {
            if (-dz < 0.0f) {
                ndx = -dx;
                len = sqrtf(dz * dz + dx * dx);
                angle = -radians_to_angle(ndx / len);
            } else {
                ndx = -dx;
                len = sqrtf(dz * dz + dx * dx);
                angle = radians_to_angle(ndx / len);
            }
        }
        if (obj->burst != 0) {
            func_800F2E50(0x84, 0xFF, 0, 0xC, -1);
            i = 0;
            range = D_80074B14;
            bias = D_80074B18;
            for (; i < 4; i++) {
                pt[0] = obj->pos[0] + random_float_range(range) - bias;
                pt[1] = obj->pos[1];
                pt[2] = obj->pos[2] + random_float_range(range) - bias;
                func_800F1E74(pt);
            }
            func_800ED8C0(obj->pos, 0x1B);
            return;
        }
        func_80108E74(obj->record, buf);
        func_8008F248(buf, 6, angle & 0xFFFF, 15.0f, D_80074B1C, D_80074B20, 0xF);
    }
}
