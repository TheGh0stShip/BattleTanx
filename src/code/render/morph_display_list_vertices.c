#include "types.h"

typedef struct MorphVertex {
    s16 x;
    s16 y;
    s16 z;
    u8 pad06[6];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MorphVertex;

typedef union MorphCommand {
    u32 w0;
    struct {
        u8 opcode;
        u8 pad01;
        u16 count;
        u32 address;
    } vtx;
} MorphCommand;

extern void bcopy(void *src, void *dst, s32 size) __asm__("func_801106A0");

void morph_display_list_vertices(s32 weight, MorphCommand *from, MorphCommand *to, u8 *out) __asm__("func_80091A60");

void morph_display_list_vertices(s32 weight, MorphCommand *from, MorphCommand *to, u8 *out) {
    MorphVertex *a;
    MorphVertex *b;
    MorphVertex *dst;
    s32 offset;
    s32 count;
    s32 i;
    s32 k;

    if (weight == 0) {
        if (from->w0 != 0xB8000000) {
            i = 0;
            for (;;) {
                if (from[i].vtx.opcode == 4) {
                    offset = from[i].vtx.address - (u32)from;
                    bcopy((void *)from[i].vtx.address, out + offset, (from[i].vtx.count >> 10) * 16);
                }
                i++;
                if (from[i].w0 == 0xB8000000) {
                    break;
                }
            }
        }
    } else if (weight == 0x100) {
        if (from->w0 != 0xB8000000) {
            i = 0;
            do {
                if (to[i].vtx.opcode == 4) {
                    offset = to[i].vtx.address - (u32)to;
                    bcopy((void *)to[i].vtx.address, out + offset, (to[i].vtx.count >> 10) * 16);
                }
                i++;
            } while (from[i].w0 != 0xB8000000);
        }
    } else {
        if (from->w0 != 0xB8000000) {
            i = 0;
            do {
                if (from[i].vtx.opcode == 4) {
                    offset = from[i].vtx.address - (u32)from;
                    count = from[i].vtx.count >> 10;
                    a = (MorphVertex *)from[i].vtx.address;
                    b = (MorphVertex *)((u8 *)to + offset);
                    dst = (MorphVertex *)(out + offset);
                    for (k = 0; k < count; k++) {
                        dst[k].x = a[k].x + (((b[k].x - a[k].x) * weight) >> 8);
                        dst[k].y = a[k].y + (((b[k].y - a[k].y) * weight) >> 8);
                        dst[k].z = a[k].z + (((b[k].z - a[k].z) * weight) >> 8);
                        dst[k].r = a[k].r + (((b[k].r - a[k].r) * weight) >> 8);
                        dst[k].g = a[k].g + (((b[k].g - a[k].g) * weight) >> 8);
                        dst[k].b = a[k].b + (((b[k].b - a[k].b) * weight) >> 8);
                    }
                }
                i++;
            } while (from[i].w0 != 0xB8000000);
        }
    }
}
