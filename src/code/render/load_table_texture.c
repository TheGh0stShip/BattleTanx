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
} TextureInfo;

typedef struct RenderFrame {
    Gfx *main;
    Gfx *overlay;
    u8 pad08[0x20];
    TextureInfo *texture;
} RenderFrame;

#define _SHIFTL(v, s, w) ((unsigned int)(((unsigned int)(v) & ((0x01 << (w)) - 1)) << (s)))
#define G_SETTIMG 0xFD
#define G_SETTILE 0xF5
#define G_RDPLOADSYNC 0xE6
#define G_RDPPIPESYNC 0xE7
#define G_LOADTILE 0xF4
#define G_SETTILESIZE 0xF2
#define G_TX_LOADTILE 7
#define G_TEXTURE_IMAGE_FRAC 2
#define G_IM_SIZ_4b 0
#define G_IM_SIZ_8b 1
#define G_IM_SIZ_8b_TILE_BYTES 1
#define G_IM_SIZ_8b_LINE_BYTES 1
#define G_TX_MIRROR 1
#define G_TX_NOLOD 0

#define gSetImage(pkt, cmd, fmt, siz, width, i)                                                       \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
                                                                                                      \
        _g->words.w0 = _SHIFTL(cmd, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |             \
                       _SHIFTL((width)-1, 0, 12);                                                     \
        _g->words.w1 = (unsigned int)(i);                                                             \
    }

#define gDPSetTextureImage(pkt, f, s, w, i) gSetImage(pkt, G_SETTIMG, f, s, w, i)

#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts)  \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
                                                                                                      \
        _g->words.w0 = _SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) |       \
                       _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9);                                     \
        _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) |        \
                       _SHIFTL(maskt, 14, 4) | _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) |         \
                       _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4);                                  \
    }

#define gDPNoParam(pkt, cmd)                                                                          \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
                                                                                                      \
        _g->words.w0 = _SHIFTL(cmd, 24, 8);                                                           \
        _g->words.w1 = 0;                                                                             \
    }

#define gDPLoadSync(pkt) gDPNoParam(pkt, G_RDPLOADSYNC)
#define gDPPipeSync(pkt) gDPNoParam(pkt, G_RDPPIPESYNC)

#define gDPLoadTileGeneric(pkt, c, tile, uls, ult, lrs, lrt)                                          \
    {                                                                                                 \
        Gfx *_g = (Gfx *)(pkt);                                                                       \
                                                                                                      \
        _g->words.w0 = _SHIFTL(c, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12);                \
        _g->words.w1 = _SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12);            \
    }

#define gDPLoadTile(pkt, t, uls, ult, lrs, lrt) gDPLoadTileGeneric(pkt, G_LOADTILE, t, uls, ult, lrs, lrt)
#define gDPSetTileSize(pkt, t, uls, ult, lrs, lrt)                                                    \
    gDPLoadTileGeneric(pkt, G_SETTILESIZE, t, uls, ult, lrs, lrt)

#define gDPLoadMultiTile(pkt, timg, tmem, rtile, fmt, siz, width, height, uls, ult, lrs, lrt, pal, cms, \
                         cmt, masks, maskt, shifts, shiftt)                                           \
    {                                                                                                 \
        gDPSetTextureImage(pkt, fmt, siz, width, timg);                                              \
        gDPSetTile(pkt, fmt, siz, (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), tmem,       \
                   G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);                        \
        gDPLoadSync(pkt);                                                                             \
        gDPLoadTile(pkt, G_TX_LOADTILE, (uls) << G_TEXTURE_IMAGE_FRAC, (ult) << G_TEXTURE_IMAGE_FRAC, \
                    (lrs) << G_TEXTURE_IMAGE_FRAC, (lrt) << G_TEXTURE_IMAGE_FRAC);                    \
        gDPPipeSync(pkt);                                                                             \
        gDPSetTile(pkt, fmt, siz, (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3), tmem, rtile, \
                   pal, cmt, maskt, shiftt, cms, masks, shifts);                                      \
        gDPSetTileSize(pkt, rtile, (uls) << G_TEXTURE_IMAGE_FRAC, (ult) << G_TEXTURE_IMAGE_FRAC,      \
                       (lrs) << G_TEXTURE_IMAGE_FRAC, (lrt) << G_TEXTURE_IMAGE_FRAC)                  \
    }

#define gDPLoadMultiTile_4b(pkt, timg, tmem, rtile, fmt, width, height, uls, ult, lrs, lrt, pal, cms, \
                            cmt, masks, maskt, shifts, shiftt)                                        \
    {                                                                                                 \
        gDPSetTextureImage(pkt, fmt, G_IM_SIZ_8b, ((width) >> 1), timg);                             \
        gDPSetTile(pkt, fmt, G_IM_SIZ_8b, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem,             \
                   G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts);                        \
        gDPLoadSync(pkt);                                                                             \
        gDPLoadTile(pkt, G_TX_LOADTILE, (uls) << (G_TEXTURE_IMAGE_FRAC - 1),                         \
                    (ult) << (G_TEXTURE_IMAGE_FRAC), (lrs) << (G_TEXTURE_IMAGE_FRAC - 1),             \
                    (lrt) << (G_TEXTURE_IMAGE_FRAC));                                                 \
        gDPPipeSync(pkt);                                                                             \
        gDPSetTile(pkt, fmt, G_IM_SIZ_4b, (((((lrs) - (uls) + 1) >> 1) + 7) >> 3), tmem, rtile, pal,  \
                   cmt, maskt, shiftt, cms, masks, shifts);                                           \
        gDPSetTileSize(pkt, rtile, (uls) << G_TEXTURE_IMAGE_FRAC, (ult) << G_TEXTURE_IMAGE_FRAC,      \
                       (lrs) << G_TEXTURE_IMAGE_FRAC, (lrt) << G_TEXTURE_IMAGE_FRAC)                  \
    }

extern RenderFrame *get_render_frame_record_alt(void) __asm__("func_8007F060");
extern s32 lookup_texture_table_entry(u32 table, u16 index) __asm__("func_800AB520");
extern s32 lookup_audio_table_stride_two(s32 index) __asm__("func_800AB61C");

static inline void load_tile_4b(RenderFrame *frame, TextureInfo *info, s32 texture, s32 tmem, s32 rtile)
{
    gDPLoadMultiTile_4b(frame->overlay++, texture, tmem, rtile, info->fmt, info->width,
                        info->height, 0, 0, info->width - 1, info->height - 1, 0, G_TX_MIRROR,
                        G_TX_MIRROR, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
}

static inline void load_tile_8b(RenderFrame *frame, TextureInfo *info, s32 texture, s32 tmem, s32 rtile)
{
    gDPLoadMultiTile(frame->overlay++, texture, tmem, rtile, info->fmt, G_IM_SIZ_8b, info->width,
                     info->height, 0, 0, info->width - 1, info->height - 1, 0, 0, 0, 0, 0, G_TX_NOLOD,
                     G_TX_NOLOD);
}

void load_table_texture(u32 table, u16 index, s32 tile) __asm__("func_800AACCC");

void load_table_texture(u32 table, u16 index, s32 tile)
{
    RenderFrame *frame = get_render_frame_record_alt();
    s32 texture = lookup_texture_table_entry(table, index);
    TextureInfo *info;

    if (texture != 0) {
        info = (TextureInfo *)lookup_audio_table_stride_two(table);
        frame->texture = info;
        if ((u16)tile < 2) {
            if (info->siz == 0) {
                load_tile_4b(frame, info, texture, (s16)tile * 256, (s16)tile);
            } else if (info->siz == 1) {
                load_tile_8b(frame, info, texture, (s16)tile * 256, (s16)tile);
            }
        }
    } else {
        frame->texture = 0;
    }
}
