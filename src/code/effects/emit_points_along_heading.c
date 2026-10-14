#include "types.h"

typedef struct SegmentLine {
    u8 pad00[0xC];
    f32 x;
    f32 y;
    f32 z;
    u16 angle;
    u8 pad1A[0x20 - 0x1A];
    u16 count;
    u8 pad22[0x28 - 0x22];
    f32 spacing;
} SegmentLine;

extern f32 angle_cos(u16 angle) __asm__("func_800F3B40");
extern f32 angle_sin(u16 angle) __asm__("func_800F3AE0");
extern void func_8010CE24(SegmentLine *line, f32 *pos);
extern f32 D_800755A0;

void emit_points_along_heading(SegmentLine *line) __asm__("func_8010D388");

void emit_points_along_heading(SegmentLine *line) {
    f32 pos[3];
    f32 c;
    f32 step;
    f32 s;
    f32 dx;
    f32 dz;
    s32 i;

    i = 0;
    c = angle_cos(line->angle);
    s = angle_sin(line->angle);
    step = line->spacing + line->spacing;
    dz = step * -s;
    dx = step * c;
    pos[2] = line->z - dz * line->count / D_800755A0;
    pos[0] = line->x - dx * line->count / D_800755A0;
    pos[1] = line->y;
    for (; i < line->count; i++) {
        func_8010CE24(line, pos);
        pos[2] += dz;
        pos[0] += dx;
    }
}
