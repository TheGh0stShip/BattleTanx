#include "types.h"

typedef struct {
    u32 w0;
    u32 w1;
} GfxWords;

typedef union {
    GfxWords words;
    u64 force_structure_alignment;
} Gfx;

typedef struct TextureInfo {
    u16 fmt;
    u16 siz;
    u16 width;
    u16 height;
    u16 masks;
    u16 maskt;
} TextureInfo;

typedef struct RenderFrame {
    Gfx *main;
    Gfx *overlay;
    u8 pad08[0x20];
    TextureInfo *texture;
} RenderFrame;

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define G_SETTIMG 0xFD
#define G_SETTILE 0xF5
#define G_RDPLOADSYNC 0xE6
#define G_RDPPIPESYNC 0xE7
#define G_RDPTILESYNC 0xE8
#define G_LOADBLOCK 0xF3
#define G_LOADTLUT 0xF0
#define G_SETTILESIZE 0xF2
#define G_SETOTHERMODE_H 0xBA
#define G_MDSFT_TEXTLUT 14
#define G_TT_RGBA16 (2 << G_MDSFT_TEXTLUT)
#define G_TX_LOADTILE 7
#define G_TX_RENDERTILE 0
#define G_TEXTURE_IMAGE_FRAC 2
#define G_TX_DXT_FRAC 11
#define G_TX_LDBLK_MAX_TXL 2047
#define G_IM_FMT_RGBA 0
#define G_IM_FMT_CI 2
#define G_IM_SIZ_4b 0
#define G_IM_SIZ_8b 1
#define G_IM_SIZ_16b 2
#define G_IM_SIZ_32b 3
#define G_IM_SIZ_8b_BYTES 1
#define G_IM_SIZ_8b_LINE_BYTES 1
#define G_IM_SIZ_16b_BYTES 2
#define G_IM_SIZ_16b_LINE_BYTES 2
#define G_IM_SIZ_32b_BYTES 4
#define G_IM_SIZ_32b_LINE_BYTES 2
#define G_IM_SIZ_8b_LOAD_BLOCK G_IM_SIZ_16b
#define G_IM_SIZ_16b_LOAD_BLOCK G_IM_SIZ_16b
#define G_IM_SIZ_32b_LOAD_BLOCK G_IM_SIZ_32b
#define G_IM_SIZ_8b_SHIFT 1
#define G_IM_SIZ_16b_SHIFT 0
#define G_IM_SIZ_32b_SHIFT 0
#define G_IM_SIZ_8b_INCR 1
#define G_IM_SIZ_16b_INCR 0
#define G_IM_SIZ_32b_INCR 0
#define G_TX_MIRROR 1
#define G_TX_NOMIRROR 0
#define G_TX_NOLOD 0

#define gSPSetOtherMode(pkt, cmd, sft, len, data)                                                     \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = (_SHIFTL(cmd, 24, 8) | _SHIFTL(sft, 8, 8) | _SHIFTL(len, 0, 8)); \
        _g->words.w1 = (unsigned int)(data);                                                          \
    }
#define gDPSetTextureLUT(pkt, type) gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_TEXTLUT, 2, type)
#define gSetImage(pkt, cmd, fmt, siz, width, i)                                                       \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |             \
                       _SHIFTL((width)-1, 0, 12);                                                     \
        _g->words.w1 = (unsigned int)(i);                                                             \
    }
#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, G_SETTIMG, f, s, w, i)
#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts)  \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = _SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |       \
                       _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9);                                     \
        _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) |        \
                       _SHIFTL(maskt, 14, 4) | _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) |         \
                       _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4);                                  \
    }
#define gDPNoParam(pkt, cmd)                                                                          \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = _SHIFTL(cmd, 24, 8);                                                           \
        _g->words.w1 = 0;                                                                             \
    }
#define gDPLoadSync(pkt) gDPNoParam(pkt, G_RDPLOADSYNC)
#define gDPPipeSync(pkt) gDPNoParam(pkt, G_RDPPIPESYNC)
#define gDPTileSync(pkt) gDPNoParam(pkt, G_RDPTILESYNC)
#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt)                                          \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12);                \
        _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12);            \
    }
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, G_SETTILESIZE, t, uls, ult, lrs, lrt)
#define gDPLoadBlock(pkt, tile, uls, ult, lrs, dxt)                                                   \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
        _g->words.w0 = (_SHIFTL(G_LOADBLOCK, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12));   \
        _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL((MIN(lrs, G_TX_LDBLK_MAX_TXL)), 12, 12) |       \
                        _SHIFTL(dxt, 0, 12));                                                         \
    }
#define gDPLoadTLUTCmd(pkt, tile, count)                                                              \
    {                                                                                                 \
        Gfx *_g = (Gfx *)pkt;                                                                         \
        _g->words.w0 = _SHIFTL(G_LOADTLUT, 24, 8);                                                    \
        _g->words.w1 = _SHIFTL((tile), 24, 3) | _SHIFTL((count), 14, 10);                            \
    }
#define gDPLoadTLUT_pal16(pkt, pal, dram)                                                             \
    {                                                                                                 \
        gDPSetTextureImage(pkt, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram);                               \
        gDPTileSync(pkt);                                                                             \
        gDPSetTile(pkt, 0, 0, 0, (256 + (((pal)&0xf) * 16)), G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0);     \
        gDPLoadSync(pkt);                                                                             \
        gDPLoadTLUTCmd(pkt, G_TX_LOADTILE, 15);                                                       \
        gDPPipeSync(pkt)                                                                              \
    }
#define TXL2WORDS(txls, b_txl) MAX(1, ((txls) * (b_txl) / 8))
#define CALC_DXT(width, b_txl) (((1 << G_TX_DXT_FRAC) + TXL2WORDS(width, b_txl) - 1) / TXL2WORDS(width, b_txl))
#define TXL2WORDS_4b(txls) MAX(1, ((txls) / 16))
#define CALC_DXT_4b(width) (((1 << G_TX_DXT_FRAC) + TXL2WORDS_4b(width) - 1) / TXL2WORDS_4b(width))
#define gDPLoadTextureBlock(pkt, timg, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    {                                                                                                 \
        gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);                                     \
        gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        gDPLoadSync(pkt);                                                                             \
        gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, (((width) * (height) + siz##_INCR) >> siz##_SHIFT) - 1, \
                     CALC_DXT(width, siz##_BYTES));                                                   \
        gDPPipeSync(pkt);                                                                             \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_LINE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, \
                   maskt, shiftt, cms, masks, shifts);                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,              \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC)                                          \
    }
#define gDPLoadTextureBlock_4b(pkt, timg, fmt, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    {                                                                                                 \
        gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);                                          \
        gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts); \
        gDPLoadSync(pkt);                                                                             \
        gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0, (((width) * (height) + 3) >> 2) - 1, CALC_DXT_4b(width)); \
        gDPPipeSync(pkt);                                                                             \
        gDPSetTile(pkt, fmt, G_IM_SIZ_4b, ((((width) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, pal, cmt, maskt, \
                   shiftt, cms, masks, shifts);                                                       \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,              \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC)                                          \
    }

extern RenderFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");
extern s32 lookup_texture_table_entry(u32 table, u16 index) __asm__("func_800AB520");
extern s32 lookup_audio_table_stride_two(s32 index) __asm__("func_800AB61C");
extern s32 func_800AB614(u32 table, u16 index);

void load_table_texture_block(u32 table, u16 index) __asm__("func_800AA518");

void load_table_texture_block(u32 table, u16 index)
{
    RenderFrame *frame = get_render_frame_record_alt();
    s32 texture = lookup_texture_table_entry(table, index);
    TextureInfo *info;

    if (texture != 0) {
    info = (TextureInfo *)lookup_audio_table_stride_two(table);
    frame->texture = info;
    switch (info->siz) {
    case G_IM_SIZ_4b:
        if (info->fmt == G_IM_FMT_CI) {
            s32 palette = func_800AB614(table, index);

            gDPSetTextureLUT(frame->overlay++, G_TT_RGBA16);
            gDPLoadTLUT_pal16(frame->overlay++, 0, palette);
        }
        gDPLoadTextureBlock_4b(frame->overlay++, texture, info->fmt, info->width, info->height, 0, G_TX_MIRROR,
                               G_TX_MIRROR, info->masks, info->maskt, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case G_IM_SIZ_8b:
        gDPLoadTextureBlock(frame->overlay++, texture, info->fmt, G_IM_SIZ_8b, info->width, info->height, 0,
                            G_TX_NOMIRROR, G_TX_NOMIRROR, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case G_IM_SIZ_16b:
        gDPLoadTextureBlock(frame->overlay++, texture, info->fmt, G_IM_SIZ_16b, info->width, info->height, 0,
                            G_TX_NOMIRROR, G_TX_NOMIRROR, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case G_IM_SIZ_32b:
        gDPLoadTextureBlock(frame->overlay++, texture, info->fmt, G_IM_SIZ_32b, info->width, info->height, 0,
                            G_TX_NOMIRROR, G_TX_MIRROR, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    } else {
        frame->texture = 0;
    }
}
