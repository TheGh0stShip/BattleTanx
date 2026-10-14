#include "types.h"

typedef struct PointObject {
    u8 pad00[0x8];
    s32 kind;
} PointObject;

typedef struct PointQueryHit {
    PointObject *object;
    s32 value04;
} PointQueryHit;

typedef struct PointMessage {
    f32 x;
    f32 y;
    s32 value08;
    s32 value0C;
    s32 radius;
} PointMessage;

typedef void (*PointObjectHandler)(PointObject *object, s32 sender, s32 event, PointMessage *message, s32 extra);

typedef struct PointObjectKind {
    u8 pad00[0x4];
    PointObjectHandler handler;
    u8 pad08[0x4];
} PointObjectKind;

#define POINT_QUERY_CAPACITY 32

extern PointObjectKind D_802C3800[];

extern u8 func_8010823C(s32 y, s32 x, s32 radius, s32 capacity, PointQueryHit *hits, s32 *count);

void notify_objects_near_point(s32 sender, f32 *point, f32 radius, f32 value, u8 flag) __asm__("func_8009F958");

void notify_objects_near_point(s32 sender, f32 *point, f32 radius, f32 value, u8 flag)
{
    PointQueryHit hits[POINT_QUERY_CAPACITY];
    PointMessage message;
    s32 count;
    s32 i;
    s32 range;

    message.value08 = value;
    message.value0C = flag;
    message.y = point[1];
    message.x = point[0];
    range = radius;
    message.radius = range;
    if (func_8010823C(point[1], point[0], range, 0x40, hits, &count)) {
        for (i = 0; i < count; i++) {
            if ((u32)hits[i].object >= 4 && D_802C3800[hits[i].object->kind].handler != 0) {
                D_802C3800[hits[i].object->kind].handler(hits[i].object, sender, 7, &message, 0);
            }
        }
    }
}
