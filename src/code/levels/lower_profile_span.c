#include "types.h"

typedef struct ProfileCell {
    s32 height;
    s32 region;
} ProfileCell;

extern ProfileCell D_802D5BC0[][3][100];

void lower_profile_span(s32 startX, s32 startHeight, s32 endX, s32 endHeight, s32 rows, s32 region,
                        s32 layer) __asm__("func_800949D8");

void lower_profile_span(s32 startX, s32 startHeight, s32 endX, s32 endHeight, s32 rows, s32 region,
                        s32 layer)
{
    s32 regions[2][3];
    s32 dx = endX - startX;
    s32 same = 1;
    s32 row;
    s32 x;
    s32 dh;
    s32 height;
    ProfileCell *cell;

    if (dx == 0) {
        for (row = 0; row < rows; row++) {
            cell = (ProfileCell *)(startX * 8 + (row * 800 + layer * 2400));
            cell = (ProfileCell *)((u8 *)cell + (u32)D_802D5BC0);
            if (startHeight < cell->height) {
                cell->height = startHeight;
                cell->region = region;
            }
        }
        return;
    }
    for (row = 0; row < rows; row++) {
        cell = &D_802D5BC0[layer][row][startX];
            if (startHeight < cell->height) {
            same = 0;
            cell->height = startHeight;
            cell->region = region;
        } else {
            regions[0][row] = cell->region;
        }
    }
    for (row = 0; row < rows; row++) {
        cell = &D_802D5BC0[layer][row][endX];
            if (endHeight < cell->height) {
            same = 0;
            cell->height = endHeight;
            cell->region = region;
        } else {
            regions[1][row] = cell->region;
        }
    }
    if (same) {
        for (row = 0; row < rows && same; row++) {
            if (regions[0][row] != regions[1][row]) {
                same = 0;
            }
        }
    }
    if (same) {
        return;
    }
    dh = endHeight - startHeight;
    for (x = startX + 1; x <= endX - 1; x++) {
        height = startHeight + (x - startX) * dh / dx;
        for (row = 0; row < rows; row++) {
            cell = (ProfileCell *)(x * 8 + (layer * 2400 + row * 800));
            cell = (ProfileCell *)((u8 *)cell + (u32)D_802D5BC0);
            if (height < cell->height) {
                cell->height = height;
                cell->region = region;
            }
        }
    }
}
