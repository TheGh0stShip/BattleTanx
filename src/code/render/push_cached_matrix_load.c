#include "types.h"

typedef struct MatrixPoolBank {
    u8 pad00[0x14];
    u32 value14;
} MatrixPoolBank;

typedef struct MatrixRenderContext {
    u8 pad00[0x90];
    MatrixPoolBank banks[2];
    u8 padC0[0x10];
    u16 valueD0;
    u8 padD2[0xA];
    u32 *valueDC;
    u8 padE0[8];
    u32 valueE8;
} MatrixRenderContext;

typedef struct CachedMatrix {
    f32 mf[4][4];
    u32 value40;
} CachedMatrix;

extern void convert_float_matrix(CachedMatrix *src, u32 dst) __asm__("func_801146A0");
extern MatrixRenderContext *gMatrixRenderContext __asm__("D_801257D0");

void push_cached_matrix_load(CachedMatrix *matrix, u8 params) __asm__("func_8007E824");

void push_cached_matrix_load(CachedMatrix *matrix, u8 params) {
    u32 addr = matrix->value40;
    MatrixRenderContext *ctx = gMatrixRenderContext;
    MatrixPoolBank *bank = &ctx->banks[ctx->valueD0];
    u32 *cmd;

    if (addr == 0) {
        if (ctx->valueE8 >= bank->value14 + 0xC000) {
            return;
        }
        convert_float_matrix(matrix, ctx->valueE8);
        addr = ctx->valueE8;
        matrix->value40 = addr;
        ctx->valueE8 += 0x40;
    }
    cmd = ctx->valueDC;
    ctx->valueDC = cmd + 2;
    cmd[0] = (params << 16) | 0x01000040;
    cmd[1] = addr - 0x80000000;
}
