#include "types.h"

typedef struct LinkedObject {
    u8 pad00[0x4];
    s32 value04;
    s32 kind;
    u8 pad0C[0x10];
    f32 value1C;
    f32 value20;
} LinkedObject;

typedef struct LinkedOwner {
    u8 pad00[0x34C];
    LinkedObject *linked;
} LinkedOwner;

typedef struct LinkedCapture {
    s32 count;
    f32 *values;
    f32 data[2];
    LinkedObject *object;
    s32 value14;
} LinkedCapture;

void capture_linked_kind_1b_object(LinkedCapture *out, LinkedOwner *owner) __asm__("func_800E3A64");

void capture_linked_kind_1b_object(LinkedCapture *out, LinkedOwner *owner)
{
    LinkedObject *object = owner->linked;

    if (object != 0 && object->kind == 0x1B) {
        out->object = object;
        out->value14 = object->value04;
        out->data[1] = object->value20;
        out->data[0] = object->value1C;
        out->values = out->data;
        out->count = 3;
    }
}
