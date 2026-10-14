#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x4];
    u32 base;
    u8 pad08[0x10];
} MatrixPoolBank;

typedef struct MatrixRenderState {
    u8 pad00[0xA0];
    MatrixPoolBank banks[1];
    u8 padB8[0x18];
    u16 bank;
    u8 padD2[0x6];
    u32 *mainList;
    u32 *list;
    u8 padE0[0x8];
    u32 cursor;
} MatrixRenderState;

extern MatrixRenderState *D_801257D0;
extern void func_801146A0(s32 source, u32 dest);

u32 push_perspnorm_matrix_command(u32 source, u8 flags, u16 perspNorm) __asm__("func_8007E4F4");

u32 push_perspnorm_matrix_command(u32 source, u8 flags, u16 perspNorm)
{
    MatrixRenderState *state = D_801257D0;
    u32 matrix = 0;

    if (state->cursor < ((MatrixPoolBank *)(state->bank * sizeof(MatrixPoolBank) + (u8 *)state->banks))->base + 0xC000) {
        u32 *cmd;
        u32 *persp;

        persp = state->list;
        state->list = persp + 2;
        persp[0] = 0xBC00000E;
        persp[1] = perspNorm;
        func_801146A0(source, state->cursor);
        cmd = state->list;
        state->list = cmd + 2;
        cmd[0] = (flags << 16) | 0x01000040;
        cmd[1] = state->cursor - 0x80000000;
        matrix = state->cursor;
        state->cursor = matrix + 0x40;
    }
    return matrix;
}
