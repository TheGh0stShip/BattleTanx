#include "types.h"

typedef struct DisplayListState {
    u8 pad00[0xD8];
    u32 *list;
} DisplayListState;

extern DisplayListState *gMatrixRenderState __asm__("D_801257D0");

void push_projection_matrix(u32 matrix, u8 flags, u16 perspNorm) __asm__("func_8007EBDC");

/* Emits a perspective-normalize moveword followed by a matrix load. */
void push_projection_matrix(u32 matrix, u8 flags, u16 perspNorm)
{
    DisplayListState *state = gMatrixRenderState;
    u32 *cmd;
    u32 *cmd2;

    cmd = state->list;
    state->list = cmd + 2;
    cmd[0] = 0xBC00000E;
    cmd[1] = perspNorm;
    cmd2 = state->list;
    state->list = cmd2 + 2;
    cmd2[0] = (flags << 16) | 0x01000040;
    cmd2[1] = matrix - 0x80000000;
}
