#include "types.h"

typedef struct ProfileCell {
    s32 height;
    s32 region;
} ProfileCell;

extern ProfileCell D_802D5BC0[][3][100];

s32 is_profile_blocked(s32 startX, s32 startHeight, s32 endX, s32 endHeight, s32 row, s32 layer) __asm__("func_80095CDC");

s32 is_profile_blocked(s32 startX, s32 startHeight, s32 endX, s32 endHeight, s32 row, s32 layer)
{
    s32 dx = endX - startX;
    s32 rowIndex = row - 1;
    s32 dh;
    s32 startRegion;
    s32 x;

    if (dx == 0) {
        return startHeight < D_802D5BC0[layer][rowIndex][startX].height;
    }
    dh = endHeight - startHeight;
    if (startHeight < D_802D5BC0[layer][rowIndex][startX].height) {
        return 1;
    }
    startRegion = D_802D5BC0[layer][rowIndex][startX].region;
    if (endHeight < D_802D5BC0[layer][rowIndex][endX].height) {
        return 1;
    }
    if (startRegion == D_802D5BC0[layer][rowIndex][endX].region) {
        return 0;
    }
    if (dx < 10) {
        return D_802D5BC0[layer][rowIndex][startX + dx / 2].height > (startHeight + endHeight) / 2;
    }
    for (x = startX + 1; x <= endX - 1; x++) {
        if (startHeight + (x - startX) * dh / dx < D_802D5BC0[layer][rowIndex][x].height) {
            return 1;
        }
    }
    return 0;
}
