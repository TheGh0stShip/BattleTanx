#include "types.h"

typedef struct AiOwnerState {
    u8 pad00[0x24];
    f32 value24;
    u8 pad28[0x4];
    f32 value2C;
    u8 pad30[0x9C - 0x30];
    s32 value9C;
} AiOwnerState;

extern f32 *ai_get_indexed_float_address(AiOwnerState *store, s32 index) __asm__("func_800E9880");
extern void func_800E5FA8(AiOwnerState *owner, s32 *mode, f32 *point, s32 *flag, f32 *a, f32 *b);

void reset_owner_state(AiOwnerState *owner) __asm__("func_800E5F30");

void reset_owner_state(AiOwnerState *owner) {
    f32 point[2];
    s32 flag;

    point[1] = owner->value24;
    flag = 1;
    point[0] = owner->value2C;
    func_800E5FA8(owner, &owner->value9C, point, &flag, ai_get_indexed_float_address(owner, 0x1004),
                  ai_get_indexed_float_address(owner, 0x1005));
}
