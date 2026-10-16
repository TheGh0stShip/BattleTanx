#include "types.h"

typedef struct LocalBox {
    u16 flags;
    s16 centerY;
    s16 centerX;
    s16 minY;
    s16 maxY;
    s16 minX;
    s16 maxX;
    u8 pad0E[0x2];
    u16 angle;
} LocalBox;

extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");

u8 intersect_segment_box(f32 *from, f32 *to, LocalBox *box, f32 *point, f32 *normal) __asm__("func_801095D0");

#define HIT_Y(face, ns, nc)                                              \
    t = ((face) - start[1]) / localDelta[1];                             \
    v = start[0] + t * localDelta[0];                                    \
    if (box->minX <= v && v <= box->maxX) {                              \
        point[1] = from[1] + t * delta[1];                               \
        point[0] = from[0] + t * delta[0];                               \
        normal[1] = ns;                                                  \
        normal[0] = nc;                                                  \
        return 1;                                                        \
    }

#define HIT_X(face, ns, nc)                                              \
    t = ((face) - start[0]) / localDelta[0];                             \
    v = start[1] + t * localDelta[1];                                    \
    if (box->minY <= v && v <= box->maxY) {                              \
        point[1] = from[1] + t * delta[1];                               \
        point[0] = from[0] + t * delta[0];                               \
        normal[1] = ns;                                                  \
        normal[0] = nc;                                                  \
        return 1;                                                        \
    }

/* Same as HIT_X with the upper bound test written as maxY >= v. */
#define HIT_X_ALT(face, ns, nc)                                              \
    t = ((face) - start[0]) / localDelta[0];                             \
    v = start[1] + t * localDelta[1];                                    \
    if (box->minY <= v && box->maxY >= v) {                              \
        point[1] = from[1] + t * delta[1];                               \
        point[0] = from[0] + t * delta[0];                               \
        normal[1] = ns;                                                  \
        normal[0] = nc;                                                  \
        return 1;                                                        \
    }

#define HIT_MAX_X_ALT HIT_X_ALT(box->maxX, angle_sin(box->angle), angle_cos(box->angle))
#define HIT_MIN_Y HIT_Y(box->minY, -angle_cos(box->angle), angle_sin(box->angle))
#define HIT_MAX_Y HIT_Y(box->maxY, angle_cos(box->angle), -angle_sin(box->angle))
#define HIT_MIN_X HIT_X(box->minX, -angle_sin(box->angle), -angle_cos(box->angle))
#define HIT_MAX_X HIT_X(box->maxX, angle_sin(box->angle), angle_cos(box->angle))

u8 intersect_segment_box(f32 *from, f32 *to, LocalBox *box, f32 *point, f32 *normal)
{
    f32 start[2];
    f32 end[2];
    f32 localDelta[2];
    f32 delta[2];
    f32 s;
    f32 c;
    f32 t;
    f32 v;

    delta[1] = to[1] - from[1];
    delta[0] = to[0] - from[0];
    if (delta[1] == 0.0f && delta[0] == 0.0f) {
        return 0;
    }
    if (box->flags & 1) {
        start[1] = from[1] - box->centerY;
        start[0] = from[0] - box->centerX;
        localDelta[1] = delta[1];
        localDelta[0] = delta[0];
        end[1] = to[1] - box->centerY;
        end[0] = to[0] - box->centerX;
    } else {
        s = angle_sin(box->angle);
        c = angle_cos(box->angle);
        start[1] = c * (from[1] - box->centerY) + -s * (from[0] - box->centerX);
        start[0] = s * (from[1] - box->centerY) + c * (from[0] - box->centerX);
        localDelta[1] = c * delta[1] + -s * delta[0];
        localDelta[0] = s * delta[1] + c * delta[0];
        end[1] = start[1] + localDelta[1];
        end[0] = start[0] + localDelta[0];
    }
    if (start[1] < box->minY) {
        if (!(box->minY <= end[1])) {
            return 0;
        }
        if (start[0] < box->minX) {
            if (box->minX <= end[0]) {
                HIT_MIN_X
            }
            HIT_MIN_Y
        } else if (box->maxX < start[0]) {
            if (end[0] <= box->maxX) {
                HIT_MAX_X
            }
            HIT_MIN_Y
        } else {
            HIT_MIN_Y
        }
        return 0;
    } else if (box->maxY < start[1]) {
        if (!(end[1] <= box->maxY)) {
            return 0;
        }
        if (start[0] < box->minX) {
            if (box->minX <= end[0]) {
                HIT_MIN_X
            }
            HIT_MAX_Y
        } else if (box->maxX < start[0]) {
            if (end[0] <= box->maxX) {
                HIT_MAX_X
            }
            HIT_MAX_Y
        } else {
            HIT_MAX_Y
        }
        return 0;
    } else if (start[0] < box->minX) {
        if (!(box->minX <= end[0])) {
            return 0;
        }
        if (box->minY > start[1]) {
            HIT_MIN_Y
            HIT_MIN_X
        } else if (start[1] > box->maxY) {
            HIT_MAX_Y
            HIT_MIN_X
        } else {
            HIT_MIN_X
        }
        return 0;
    } else if (box->maxX < start[0]) {
        if (!(end[0] <= box->maxX)) {
            return 0;
        }
        if (box->minY > start[1]) {
            HIT_MIN_Y
            HIT_MAX_X
            return 0;
        } else if (start[1] > box->maxY) {
            HIT_MAX_Y
            HIT_MAX_X_ALT
            return 0;
        } else {
            HIT_MAX_X
        }
        return 0;
    }
    point[1] = from[1];
    point[0] = from[0];
    normal[1] = 0.0f;
    normal[0] = 1.0f;
    return 1;
}
