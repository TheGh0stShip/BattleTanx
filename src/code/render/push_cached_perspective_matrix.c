#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x14];
    u32 base;
} MatrixPoolBank;

typedef struct MatrixRenderState {
    u8 pad00[0x90];
    MatrixPoolBank banks[1];
    u8 padA8[0x28];
    u16 bank;
    u8 padD2[0xA];
    u32 *list;
    u8 padE0[0x8];
    u32 cursor;
} MatrixRenderState;

typedef struct CachedProjection {
    u8 pad00[0x40];
    u32 matrix;
} CachedProjection;

extern MatrixRenderState *D_801257D0;
extern void convert_matrix_to_fixed(CachedProjection *source, u32 dest) __asm__("func_801146A0");

void push_cached_perspective_matrix(CachedProjection *proj, u16 perspNorm) __asm__("func_8007E9C8");

void push_cached_perspective_matrix(CachedProjection *proj, u16 perspNorm) {
    MatrixRenderState *state = D_801257D0;
    MatrixPoolBank *bank = &state->banks[state->bank];
    u32 matrix = proj->matrix;
    u32 *cmd;
    u32 *cmd2;

    if (matrix == 0) {
        if (state->cursor >= bank->base + 0xC000) {
            return;
        }
        convert_matrix_to_fixed(proj, state->cursor);
        matrix = state->cursor;
        proj->matrix = matrix;
        state->cursor += 0x40;
    }
    cmd = state->list;
    state->list = cmd + 2;
    cmd[0] = 0xBC00000E;
    cmd[1] = perspNorm;
    cmd2 = state->list;
    state->list = cmd2 + 2;
    cmd2[0] = 0x01030040;
    cmd2[1] = matrix - 0x80000000;
}
