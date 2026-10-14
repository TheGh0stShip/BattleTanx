#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x14];
    u32 base;
} MatrixPoolBank;

typedef struct MatrixRenderState {
    u8 pad00[0x90];
    MatrixPoolBank banks[2];
    u8 padC0[0x10];
    u16 bank;
    u8 padD2[0x6];
    u32 *list;
    u8 padDC[0xC];
    u32 cursor;
} MatrixRenderState;

typedef struct CachedMatrixSource {
    f32 mf[4][4];
    u32 matrix;
} CachedMatrixSource;

extern void convert_float_matrix(CachedMatrixSource *src, u32 dst) __asm__("func_801146A0");
extern MatrixRenderState *gMatrixRenderState __asm__("D_801257D0");

void push_cached_matrix_params(CachedMatrixSource *source, u8 flags) __asm__("func_8007E75C");

void push_cached_matrix_params(CachedMatrixSource *source, u8 flags) {
    MatrixRenderState *state = gMatrixRenderState;
    MatrixPoolBank *bank = &state->banks[state->bank];
    u32 matrix = source->matrix;
    u32 *cmd;

    if (matrix == 0) {
        if (state->cursor >= bank->base + 0xC000) {
            return;
        }
        convert_float_matrix(source, state->cursor);
        matrix = state->cursor;
        source->matrix = matrix;
        state->cursor += 0x40;
    }
    cmd = state->list;
    state->list = cmd + 2;
    cmd[0] = (flags << 16) | 0x01000040;
    cmd[1] = matrix - 0x80000000;
}
