#include "types.h"

typedef struct {
    u8 pad00;
    s8 value01;
    u8 pad02[2];
    s32 value04;
    u8 pad08[0x54 - 0x08];
    u16 value54;
    u8 pad56[2];
} Slot58;

typedef struct {
    u8 pad00[0x568];
    Slot58 *slots;
} Session;

typedef struct {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    s16 slot;
    s16 timer;
    u8 triggered;
    u8 pad1D[3];
    s32 area;
    u8 burst;
} Obj;

typedef struct {
    u8 pad000[0x18];
    s32 mode;
    u8 pad01C[0x3B4 - 0x1C];
    f32 value3B4;
    u8 pad3B8[0x3D0 - 0x3B8];
    f32 value3D0;
    f32 value3D4;
} EventUnit;

typedef struct {
    u8 pad00[8];
    u32 event;
    EventUnit *unit;
} Event;

typedef struct {
    u8 pad00[4];
    f32 y;
    u8 pad08[4];
    u16 angle;
} Hit;

typedef struct {
    f32 z;
    f32 x;
} Target;

typedef struct { f32 x, y, z; } Vec3;
typedef struct { f32 v[8]; } Corners;

extern Session *get_spawn_session(void) __asm__("func_800821C0");
extern void clear_record_halfword_flags(s32 index, u16 flags) __asm__("func_80106CCC");
extern void spawn_effect_kind_19(s32 a, s32 b, s32 c, s32 d, s32 e) __asm__("func_800F2E50");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern void spawn_kind24_burst(Vec3 *origin) __asm__("func_800F1E74");
extern void spawn_effect_kind_26(Vec3 *position, s32 variant) __asm__("func_800ED8C0");
extern void area_box_corners(s32 index, Corners *out) __asm__("func_80108E74");
extern void func_8008F248(Corners *c, s32 a, u16 angle, f32 b, f32 d, f32 e, s32 f);
extern void func_80085B4C(s32 kind, f32 x, f32 z);

static inline void open_slot(Obj *obj)
{
    Slot58 *slot;

    obj->triggered = 1;
    slot = &get_spawn_session()->slots[obj->slot];
    slot->value01 = 1;
    slot->value04 = 0x1C;
    slot->value54++;
    clear_record_halfword_flags(obj->area, 0x5D);
}

static inline s32 burst_center(Obj *obj, f32 y)
{
    Vec3 center;
    Corners c2;
    Vec3 p;
    s32 i;

    area_box_corners(obj->area, &c2);
    center.y = y;
    center.x = (c2.v[1] + c2.v[5]) / 2.0f;
    center.z = (c2.v[0] + c2.v[4]) / 2.0f;
    if (obj->burst != 0) {
        spawn_effect_kind_19(0x84, 0xFF, 0, 0xC, -1);
        i = 0;
        do {
            i++;
            p.x = center.x + random_float_range(200.0f) - 100.0f;
            p.y = center.y;
            p.z = center.z + random_float_range(200.0f) - 100.0f;
            spawn_kind24_burst(&p);
        } while (i < 4);
        spawn_effect_kind_26(&center, 0x1B);
    } else {
        spawn_effect_kind_26(&center, 7);
    }
    return 0;
}

void handle_breakable_object_event(Obj *obj, Event *ev, Hit *hit, s32 *out) __asm__("func_800ECE4C");

void handle_breakable_object_event(Obj *obj, Event *ev, Hit *hit, s32 *out)
{
    Target t;
    Corners c;
    EventUnit *u;
    s32 n;
    f32 d;
    s32 v;

    switch (ev->event) {
    case 2:
    case 12:
    case 22:
    case 34:
    case 44:
        if (obj->triggered != 0) {
            return;
        }
        open_slot(obj);
        *out = 6;
        if ((ev->event == 2) | (ev->event == 22) || ev->event == 34) {
            area_box_corners(obj->area, &c);
            func_8008F248(&c, 6, hit->angle, 15.0f, 100.0f, 2.0f, 0xF);
        }
        hit->y = 30.0f;
        if (obj->burst != 0) {
            burst_center(obj, 30.0f);
        } else {
            spawn_effect_kind_26((Vec3 *)hit, 7);
        }
        func_80085B4C(0x13, obj->x, obj->z);
        t.x = obj->x;
        t.z = obj->z;
        obj->timer = 0;
        return;
    case 0:
        if (obj->triggered == 0) {
            if (obj->timer != 0) {
                u = ev->unit;
                u->value3D0 -= 3.0;
                if (obj->timer & 1) {
                    u->value3D4 -= 1.0f;
                } else {
                    u->value3D4 += 1.0f;
                }
                d = u->value3B4 * 12.0f;
                n = 1;
                if (1.0f < d) {
                    n = d;
                }
                if (u->mode == 1) {
                    n *= 3;
                }
                v = (u16)obj->timer - n;
                obj->timer = v & (~(s32)(s16)v >> 31);
                if (obj->timer == 0) {
                    clear_record_halfword_flags(obj->area, 0x10);
                }
                *out = 0;
            } else {
                open_slot(obj);
                {
                    Corners c3;

                    area_box_corners(obj->area, &c3);
                    func_8008F248(&c3, 6, hit->angle, 15.0f, 100.0f, 2.0f, 0xF);
                }
                hit->y = 30.0f;
                burst_center(obj, 30.0f);
                func_80085B4C(0x13, obj->x, obj->z);
                *out = 5;
            }
        } else {
            *out = 4;
        }
        break;
    default:
        *out = 0;
        break;
    }
}
