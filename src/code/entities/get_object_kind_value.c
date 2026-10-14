#include "types.h"

typedef struct KindObject {
    u8 pad00[0xC];
    u32 kind;
    u8 pad10[0x15];
    u8 alternate;
} KindObject;

extern s16 D_802D5A5A;
extern s16 D_802D5A76;
extern s16 D_802D5A8E;
extern s16 D_802D5AC0;

s32 get_object_kind_value(KindObject *object) __asm__("func_800A052C");

s32 get_object_kind_value(KindObject *object)
{
    switch (object->kind) {
    case 0:
        return D_802D5A5A;
    case 2:
        return D_802D5A8E;
    case 1:
        if (object->alternate) {
            return D_802D5AC0;
        }
        return D_802D5A76;
    }
    return 0;
}
