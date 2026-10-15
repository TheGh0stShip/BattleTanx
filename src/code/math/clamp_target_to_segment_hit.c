#include "types.h"

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct AreaObject {
    u8 pad00[8];
    s32 kind;
} AreaObject;

typedef struct SegmentHit {
    AreaObject *object;
    f32 x;
    f32 pad08;
    f32 z;
    u8 pad10[8];
} SegmentHit;

typedef struct AreaResponse {
    s32 passable;
    s32 value04;
    s32 value08;
    s32 value0C;
} AreaResponse;

typedef void (*AreaHandler)(AreaObject *object, void *source, s32 arg2, void *data, AreaResponse *response);

typedef struct AreaHandlerEntry {
    s32 value00;
    AreaHandler handler;
    s32 value08;
} AreaHandlerEntry;

extern s32 find_segment_hit(f32 *start, f32 *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern AreaHandlerEntry D_802C3800[];

#define ABSF(x) ((x) < 0.0f ? -(x) : (x))

void clamp_target_to_segment_hit(void *source, f32 *target, f32 *out, f32 *origin, f32 *fraction) __asm__("func_80077C78");

void clamp_target_to_segment_hit(void *source, f32 *target, f32 *out, f32 *origin, f32 *fraction) {
    SegmentHit hit;
    f32 end[2];
    u8 data[0x20];
    s32 blocked = 0;

    end[1] = target[0];
    end[0] = target[2];
    if (find_segment_hit(origin, end, 1, &hit, -1)) {
        if ((u32)hit.object < 4) {
            blocked = 1;
        } else {
            AreaResponse response = {1, 0, 0, 0};

            if (D_802C3800[hit.object->kind].handler != 0) {
                D_802C3800[hit.object->kind].handler(hit.object, source, 0, data, &response);
            }
            if (response.passable == 0) {
                blocked = 1;
            }
        }
    }
    if (blocked) {
        out[0] = hit.x;
        out[2] = hit.z;
        if (ABSF(target[0] - origin[1]) > ABSF(target[2] - origin[0])) {
            *fraction = (hit.x - origin[1]) / (target[0] - origin[1]);
        } else {
            *fraction = (hit.z - origin[0]) / (target[2] - origin[0]);
        }
        out[1] = (target[1] - 50.0f) * *fraction + 50.0f;
    } else {
        *(Vec3 *)out = *(Vec3 *)target;
        *fraction = 1.0f;
    }
}
