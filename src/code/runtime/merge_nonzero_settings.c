#include "types.h"

typedef struct SettingsBlock {
    f32 value00;
    f32 value04;
    s32 value08;
    s32 value0C;
    s32 value10;
    s16 *listA;
    s16 *listB;
    u8 value1C;
    u8 value1D;
    u8 value1E;
    u8 value1F;
    u8 value20;
} SettingsBlock;

void merge_nonzero_settings(SettingsBlock *src, SettingsBlock *dst) __asm__("func_8007C770");

void merge_nonzero_settings(SettingsBlock *src, SettingsBlock *dst) {
    s32 i;

    if (src->value00 != 0.0f) dst->value00 = src->value00;
    if (src->value04 != 0.0f) dst->value04 = src->value04;
    if (src->value08 != 0) dst->value08 = src->value08;
    if (src->value0C != 0) dst->value0C = src->value0C;
    if (src->value10 != 0) dst->value10 = src->value10;
    for (i = 0; i < 4; i++) {
        if (src->listA[i] != 0) dst->listA[i] = src->listA[i];
        if (src->listB[i] != 0) dst->listB[i] = src->listB[i];
    }
    if (src->value1C != 0) dst->value1C = src->value1C;
    if (src->value1D != 0) dst->value1D = src->value1D;
    if (src->value1E != 0) dst->value1E = src->value1E;
    if (src->value1F != 0) dst->value1F = src->value1F;
    if (src->value20 != 0) dst->value20 = src->value20;
}
