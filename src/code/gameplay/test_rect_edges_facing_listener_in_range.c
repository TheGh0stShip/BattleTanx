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

extern ListenerOwner *get_spawn_session(void) __asm__("func_800821C0");
extern s32 func_80094C58(s32 x0, s32 y0, s32 x1, s32 y1, s32 index, s32 *outA, s32 *outB, s32 *outC,
                         s32 *outD);
extern s32 func_80095CDC(s32 a, s32 b, s32 c, s32 d, s32 arg4, s32 index);

#define TEST_EDGE(x0, y0, x1, y1)                                             \
    (func_80094C58(x0, y0, x1, y1, index, &edgeA, &edgeB, &edgeC, &edgeD) != 0 \
         ? func_80095CDC(edgeA, edgeB, edgeC, edgeD, arg4, index)             \
         : 0)

/* Like test_rect_edges_facing_listener, but only when the listener is within range of the rectangle. */
s32 test_rect_edges_facing_listener_in_range(s32 left, s32 top, s32 right, s32 bottom, s32 arg4, s32 index,
                                             s32 range, s32 rangeSq) __asm__("func_800962B4");

s32 test_rect_edges_facing_listener_in_range(s32 left, s32 top, s32 right, s32 bottom, s32 arg4, s32 index,
                                             s32 range, s32 rangeSq)
{
    s32 edgeA, edgeB, edgeC, edgeD;
    s32 hit;
    Listener *listener = &get_spawn_session()->listeners[index];
    s32 px = listener->value24;
    s32 py = listener->value20;

    if (px < left) {
        if (py < top) {
            if ((px - left) * (px - left) + (py - top) * (py - top) > rangeSq) {
                return 0;
            }
            hit = TEST_EDGE(left, top, right, top);
            if (hit) {
                return 1;
            }
            return TEST_EDGE(left, top, left, bottom);
        }
        if (bottom < py) {
            if ((px - left) * (px - left) + (py - bottom) * (py - bottom) > rangeSq) {
                return 0;
            }
            hit = TEST_EDGE(left, top, left, bottom);
            if (hit) {
                return 1;
            }
            return TEST_EDGE(left, bottom, right, bottom);
        }
        if (left - px > range) {
            return 0;
        }
        return TEST_EDGE(left, top, left, bottom);
    }
    if (right < px) {
        if (py < top) {
            if ((px - right) * (px - right) + (py - top) * (py - top) > rangeSq) {
                return 0;
            }
            hit = TEST_EDGE(left, top, right, top);
            if (hit) {
                return 1;
            }
            return TEST_EDGE(right, top, right, bottom);
        }
        if (bottom < py) {
            if ((px - right) * (px - right) + (py - bottom) * (py - bottom) > rangeSq) {
                return 0;
            }
            hit = TEST_EDGE(right, top, right, bottom);
            if (hit) {
                return 1;
            }
            return TEST_EDGE(right, bottom, left, bottom);
        }
        if (px - right > range) {
            return 0;
        }
        return TEST_EDGE(right, top, right, bottom);
    }
    if (py < top) {
        if (top - py > range) {
            return 0;
        }
        return TEST_EDGE(left, top, right, top);
    }
    if (bottom < py) {
        if (py - bottom > range) {
            return 0;
        }
        return TEST_EDGE(left, bottom, right, bottom);
    }
    return 1;
}
