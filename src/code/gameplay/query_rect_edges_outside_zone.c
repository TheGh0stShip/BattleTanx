#include "types.h"

typedef struct QuadZone {
    u8 pad00[0x20];
    f32 z;
    f32 x;
    u8 pad28[4];
} QuadZone;

typedef struct QuadSession {
    u8 pad000[0x584];
    QuadZone zones[1];
} QuadSession;

extern QuadSession *get_spawn_session(void) __asm__("func_800821C0");
extern s32 func_80094C58(s32 x0, s32 z0, s32 x1, s32 z1, s32 key,
                         s32 *out0, s32 *out1, s32 *out2, s32 *out3) __asm__("func_80094C58");
extern void func_800949D8(s32 value0, s32 value1, s32 value2, s32 value3, s32 arg4, s32 arg5, s32 key)
    __asm__("func_800949D8");

void query_rect_edges_outside_zone(s32 x0, s32 z0, s32 x1, s32 z1, s32 arg4, s32 arg5, s32 key) __asm__("func_800953AC");

void query_rect_edges_outside_zone(s32 x0, s32 z0, s32 x1, s32 z1, s32 arg4, s32 arg5, s32 key) {
    QuadZone *zone;
    s32 cx;
    s32 cz;
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;

    zone = &get_spawn_session()->zones[key];
    cx = zone->x;
    cz = zone->z;
    if (cx < x0) {
        if (cz < z0) {
            if (func_80094C58(x0, z0, x1, z0, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
            if (func_80094C58(x0, z0, x0, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        } else if (z1 < cz) {
            if (func_80094C58(x0, z0, x0, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
            if (func_80094C58(x0, z1, x1, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        } else {
            if (func_80094C58(x0, z0, x0, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        }
    } else if (x1 < cx) {
        if (cz < z0) {
            if (func_80094C58(x0, z0, x1, z0, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
            if (func_80094C58(x1, z0, x1, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        } else if (z1 < cz) {
            if (func_80094C58(x1, z0, x1, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
            if (func_80094C58(x1, z1, x0, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        } else {
            if (func_80094C58(x1, z0, x1, z1, key, &v0, &v1, &v2, &v3)) {
                func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
            }
        }
    } else if (cz < z0) {
        if (func_80094C58(x0, z0, x1, z0, key, &v0, &v1, &v2, &v3)) {
            func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
        }
    } else if (z1 < cz) {
        if (func_80094C58(x0, z1, x1, z1, key, &v0, &v1, &v2, &v3)) {
            func_800949D8(v0, v1, v2, v3, arg4, arg5, key);
        }
    }
}
