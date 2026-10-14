#include "types.h"

typedef struct FloatSlotOwner {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[4];
    f32 value2C;
    u8 pad30[0x6C];
    u8 value9C[0x18];
    u8 valueB4[0x18];
} FloatSlotOwner;

extern void func_800E5FA8(FloatSlotOwner *owner, void *block, f32 *pair, s32 arg,
                          f32 *first, f32 *second);
extern f32 *ai_get_indexed_float_address(FloatSlotOwner *store, s32 index) __asm__("func_800E9880");

void update_float_slot_pairs(FloatSlotOwner *owner, s32 arg) __asm__("func_800E6340");

void update_float_slot_pairs(FloatSlotOwner *owner, s32 arg) {
    f32 pair[2];

    pair[1] = owner->value24;
    pair[0] = owner->value2C;
    func_800E5FA8(owner, owner->value9C, pair, arg, ai_get_indexed_float_address(owner, 0x1004),
                  ai_get_indexed_float_address(owner, 0x1005));
    func_800E5FA8(owner, owner->valueB4, pair, 0, ai_get_indexed_float_address(owner, 0x1006),
                  ai_get_indexed_float_address(owner, 0x1007));
}
