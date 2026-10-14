#include "types.h"

typedef struct KindObject {
    u8 pad00[0xC];
    u32 kind;
    u8 value10[0xC];
    u16 value1C;
    u8 pad1E[0x7];
    u8 alternate;
    u8 value26;
} KindObject;

extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern s16 D_802D5AC0;

extern void func_800905D8(s32 value, void *position, s32 a2, u16 a3, s32 a4, s32 a5, s32 a6);
extern void release_effect(KindObject *object) __asm__("func_8008B89C");

void release_kind_object_effect(KindObject *object) __asm__("func_800A0AD4");

void release_kind_object_effect(KindObject *object) {
    s32 value;

    switch (object->kind) {
    case 0:
        value = D_802D5A5A;
        break;
    case 2:
        value = D_802D5A8E;
        break;
    case 1:
        if (object->alternate) {
            value = D_802D5AC0;
        } else {
            value = D_802D5A76;
        }
        break;
    default:
        value = 0;
        break;
    }
    func_800905D8(value, object->value10, 0, object->value1C, 0, object->value26, 0);
    release_effect(object);
}
