#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

typedef struct CachedMatrix {
    f32 m[4][4];
    u32 fixed;
} CachedMatrix;

typedef struct FrameBuffers {
    u8 pad00[0x14];
    u32 matrixBase;
} FrameBuffers;

typedef struct GraphicsContext {
    u8 pad00[0x90];
    FrameBuffers frames[2];
    u8 padC0[0x10];
    u16 frameIndex;
    u8 padD2[6];
    Gfx *gfx;
    u8 padDC[0xC];
    u32 matrixNext;
} GraphicsContext;

extern GraphicsContext *D_801257D0;
extern void convert_matrix_to_fixed(CachedMatrix *src, u32 dst) __asm__("func_801146A0");

void push_cached_matrix(CachedMatrix *matrix, u8 params) __asm__("func_8007E5CC");

void push_cached_matrix(CachedMatrix *matrix, u8 params)
{
    GraphicsContext *ctx;
    u32 fixed;
    Gfx *gfx;
    FrameBuffers *frame;

    ctx = D_801257D0;
    frame = &ctx->frames[ctx->frameIndex];
    fixed = matrix->fixed;
    if (fixed == 0) {
        if (ctx->matrixNext >= frame->matrixBase + 0xC000) {
            return;
        }
        convert_matrix_to_fixed(matrix, ctx->matrixNext);
        fixed = ctx->matrixNext;
        matrix->fixed = fixed;
        ctx->matrixNext += 0x40;
    }
    gfx = ctx->gfx++;
    gfx->w0 = (params << 16) | 0x01000040;
    gfx->w1 = fixed - 0x80000000;
}
