#include "types.h"

static inline s32 row_section(s32 row, s32 first, s32 header, s32 base, s32 *isFirst, s32 *offset, s32 section) {
    *isFirst = row == first;
    *offset = row - header - base;
    return section;
}

s32 classify_list_row(s32 row, s32 count1, s32 count2, s32 count3, s32 count4, s32 *isFirst, s32 *offset) __asm__("func_800D1F20");

s32 classify_list_row(s32 row, s32 count1, s32 count2, s32 count3, s32 count4, s32 *isFirst, s32 *offset) {
    s32 base6;
    s32 base7;
    s32 base8;
    s32 base9;
    s32 end5;
    s32 end6;
    s32 end7;
    s32 end8;
    s32 size;

    if (row < 10) {
        return row_section(row, 0, 0, 0, isFirst, offset, 0);
    }
    if (row < 40) {
        return row_section(row, 10, 10, 0, isFirst, offset, 1);
    }
    if (row < 70) {
        return row_section(row, 40, 40, 0, isFirst, offset, 2);
    }
    if (row < 100) {
        return row_section(row, 70, 70, 0, isFirst, offset, 3);
    }
    if (row < 130) {
        return row_section(row, 100, 100, 0, isFirst, offset, 4);
    }
    base6 = count3 / 200 * 2;
    end5 = base6 + 145;
    if (row < end5) {
        return row_section(row, 130, 130, 0, isFirst, offset, 5);
    }
    size = count1 * 6 + 145;
    base7 = base6 + size;
    end6 = base7 + 15;
    if (row < end6) {
        return row_section(row, end5, 145, base6, isFirst, offset, 6);
    }
    size = count2 * 40 + 15;
    base8 = base7 + size;
    end7 = base8 + 30;
    if (row < end7) {
        return row_section(row, end6, 15, base7, isFirst, offset, 7);
    }
    size = count4 * 40 + 30;
    base9 = base8 + size;
    end8 = base9 + 30;
    if (row < end8) {
        return row_section(row, end7, 30, base8, isFirst, offset, 8);
    }
    return row_section(row, end8, 30, base9, isFirst, offset, 9);
}
