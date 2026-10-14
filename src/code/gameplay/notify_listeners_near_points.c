#include "types.h"

typedef struct Listener {
    u8 pad00[0x20];
    f32 value20;
    f32 value24;
    u8 pad28[0x4];
} Listener;

typedef struct ListenerOwner {
    u8 pad000[0x584];
    Listener listeners[1];
} ListenerOwner;

typedef struct PointXZ {
    f32 x;
    f32 z;
} PointXZ;

extern s32 func_8007AAA0(void);
extern void func_800824E4(ListenerOwner *, s32, s32, s32, s32, s32, s32);
extern s32 func_800942A8(PointXZ *, s32, Listener *);
extern s32 D_801C9174;

void notify_listeners_near_points(ListenerOwner *owner, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                                  PointXZ *points, s32 arg6) __asm__("func_8008463C");

void notify_listeners_near_points(ListenerOwner *owner, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                                  PointXZ *points, s32 arg6)
{
    s32 count;
    s32 i;
    s32 j;
    s32 inside;
    Listener *listener;
    PointXZ *point;

    count = func_8007AAA0();
    for (i = 0; i < count; i++) {
        j = 0;
        listener = &owner->listeners[i];
        point = points;
        for (; j < 4; j++, point++) {
            f32 pz = point->z;
            f32 dz = listener->value24 - pz;
            f32 dx = listener->value20 - point->x;
            inside = 0;
            if (dz * dz + dx * dx < D_801C9174) {
                inside = 1;
            }
            if (inside) {
                if (func_800942A8(points, arg6, listener) == 0) {
                    func_800824E4(owner, arg1, arg2, 0, arg3, arg4, i);
                }
                break;
            }
        }
    }
}
