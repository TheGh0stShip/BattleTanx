#include "types.h"

typedef struct SectorTable SectorTable;

extern void dispatch_sector_mask(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                                 s32 a7, s32 mask) __asm__("func_80082D60");

void dispatch_all_sector_mask(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                              s32 a7) __asm__("func_80084F4C");

void dispatch_all_sector_mask(SectorTable *table, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6,
                              s32 a7) {
    dispatch_sector_mask(table, a1, a2, a3, a4, a5, a6, a7, 0xF);
}
