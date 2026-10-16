#include "types.h"

typedef struct Gfx {
    u32 w0;
    u32 w1;
} Gfx;

#define _SHIFTL(v, s, w) ((u32)(((u32)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define GFX_WORDS(pkt, a, b)  \
    {                         \
        Gfx *_g = (Gfx *)(pkt); \
        _g->w0 = (a);         \
        _g->w1 = (b);         \
    }

#define gSPScisTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                                   \
    {                                                                                                         \
        Gfx *_g = (Gfx *)(pkt);                                                                               \
                                                                                                              \
        _g->w0 = (_SHIFTL(0xE4, 24, 8) | _SHIFTL(MAX((s16)(xh), 0), 12, 12) | _SHIFTL(MAX((s16)(yh), 0), 0, 12)); \
        _g->w1 = (_SHIFTL((tile), 24, 3) | _SHIFTL(MAX((s16)(xl), 0), 12, 12) |                             \
                  _SHIFTL(MAX((s16)(yl), 0), 0, 12));                                                         \
        GFX_WORDS(pkt, 0xB4000000,                                                                           \
                  (_SHIFTL(((s) - (((s16)(xl) < 0) ? (((s16)(dsdx) < 0) ? (MAX((((s16)(xl) * (s16)(dsdx)) >> 7), 0)) \
                                                                       : (MIN((((s16)(xl) * (s16)(dsdx)) >> 7), 0))) \
                                                    : 0)),                                                    \
                           16, 16) |                                                                          \
                   _SHIFTL(((t) - (((yl) < 0) ? (((s16)(dtdy) < 0) ? (MAX((((s16)(yl) * (s16)(dtdy)) >> 7), 0)) \
                                                                   : (MIN((((s16)(yl) * (s16)(dtdy)) >> 7), 0))) \
                                              : 0)),                                                          \
                           0, 16)));                                                                          \
        GFX_WORDS(pkt, 0xB3000000, (_SHIFTL((dsdx), 16, 16) | _SHIFTL((dtdy), 0, 16)));                       \
    }

#define gDPLoadTextureTileVar(pkt, timg, fmt, siz, lineSiz, width, height, uls, ult, lrs, lrt)                     \
    {                                                                                                          \
        GFX_WORDS(pkt, _SHIFTL(0xFD, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width) - 1, 0, 12), \
                  timg);                                                                                       \
        GFX_WORDS(pkt,                                                                                         \
                  _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |                           \
                      _SHIFTL((((((lrs) - (uls) + 1) * (lineSiz)) + 7) >> 3), 9, 9),                            \
                  0x07080200);                                                                                 \
        GFX_WORDS(pkt, 0xE6000000, 0);                                                                         \
        GFX_WORDS(pkt, _SHIFTL(0xF4, 24, 8) | _SHIFTL((uls) << 2, 12, 12) | _SHIFTL((ult) << 2, 0, 12),        \
                  _SHIFTL(7, 24, 3) | _SHIFTL((lrs) << 2, 12, 12) | _SHIFTL((lrt) << 2, 0, 12));              \
        GFX_WORDS(pkt, 0xE7000000, 0);                                                                         \
        GFX_WORDS(pkt,                                                                                         \
                  _SHIFTL(0xF5, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |                           \
                      _SHIFTL((((((lrs) - (uls) + 1) * (lineSiz)) + 7) >> 3), 9, 9),                            \
                  0x00080200);                                                                                 \
        GFX_WORDS(pkt, 0xF2000000, _SHIFTL((tileWidth) << 2, 12, 12) | _SHIFTL((tileHeight) << 2, 0, 12)); \
    }

void draw_paletted_image(Gfx **list, u8 *texels, s32 fmt, s32 siz, s32 width, s32 height, s32 tileWidth,
                         s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t, f32 scaleX,
                         f32 scaleY) __asm__("func_800F3D40");

void draw_paletted_image(Gfx **list, u8 *texels, s32 fmt, s32 siz, s32 width, s32 height, s32 tileWidth,
                         s32 tileHeight, s32 x, s32 y, s32 width2, s32 height2, s32 s, s32 t, f32 scaleX,
                         f32 scaleY) {
    Gfx *gfx = *list;
    s32 lineSiz;
    s32 dsdx;
    s32 dtdy;
    s32 stepX;
    s32 stepY;
    s32 px;
    s32 py;
    s32 ss;
    s32 tt;
    s32 px2;
    s32 py2;
    s32 xl;
    s32 yl;

    lineSiz = siz;
    switch ((u32)siz) {
    case 0:
        lineSiz = 0;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        lineSiz = 2;
        break;
    }
    dsdx = scaleX * 1024.0f;
    dtdy = scaleY * 1024.0f;
    stepX = (f32)tileWidth / scaleX;
    stepY = (f32)tileHeight / scaleY;
    for (py = y, tt = t; py < y + height2; py += stepY, tt += tileHeight) {
        for (px = x, ss = s; px < x + width2; px += stepX, ss += tileWidth) {
            gDPLoadTextureTileVar(gfx++, texels, fmt, siz, lineSiz, width, height, ss, tt, ss + tileWidth,
                                  tt + tileHeight);
            px2 = px + stepX;
            if (px2 > x + width2) {
                px2 = x + width2;
            }
            py2 = py + stepY;
            if (py2 > y + height2) {
                py2 = y + height2;
            }
            xl = px * 4;
            yl = py * 4;
            px2 *= 4;
            py2 *= 4;
            gSPScisTextureRectangle(gfx++, xl, yl, px2, py2, 0, 0, 0, dsdx, dtdy);
        }
    }
    *list = gfx;
}
