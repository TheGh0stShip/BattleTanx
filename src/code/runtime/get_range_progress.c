#include "types.h"
typedef struct { s32 start; s32 end; } TimeRange;
extern f32 D_80071100;
f32 get_range_progress(TimeRange *r, s32 value) __asm__("func_8007B208");
f32 get_range_progress(TimeRange *r, s32 value) {
    s32 len = r->end - r->start;
    value -= r->start;
    if (value >= len) return D_80071100;
    if (len <= 0) return D_80071100;
    if (value < 0) return 0.0f;
    return (f32)value / (f32)len;
}
