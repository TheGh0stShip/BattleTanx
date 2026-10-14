#include "types.h"

typedef struct {
    f32 field00;
    u8 pad04[4];
    f32 field08;
    u8 pad0C[0x14];
    f32 field20;
    u8 pad24[4];
    f32 field28;
    u8 pad2C[4];
    u32 field30;
    u32 field34;
    u32 field38;
} MatrixState;

void func_800A77D4(MatrixState* state, u32 field30, u32 field34, u32 field38,
                   f32 sine, f32 cosine) {
    state->field30 = field30;
    state->field34 = field34;
    state->field38 = field38;
    state->field20 = sine;
    state->field08 = -sine;
    state->field00 = cosine;
    state->field28 = cosine;
}
