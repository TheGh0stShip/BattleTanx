#include "types.h"

extern u16 D_80132298;
extern s32 D_8013229C[];
extern u16 D_801322BC;
extern s32 D_801322C0[];
extern u16 D_801322CC;
extern s32 D_801322D0[];
extern u16 D_801322F0;
extern s32 D_801322F4[];

s32 lookup_texture_table_entry(u32 table, u16 index) __asm__("func_800AB520");

s32 lookup_texture_table_entry(u32 table, u16 index)
{
    switch (table) {
    case 0:
        if (index >= D_80132298) {
            index = D_80132298 - 1;
        }
        return D_8013229C[index];
    case 2:
        if (index >= D_801322CC) {
            index = D_801322CC - 1;
        }
        return D_801322D0[index];
    case 1:
        if (index >= D_801322F0) {
            index = D_801322F0 - 1;
        }
        return D_801322F4[index];
    case 3:
        if (index >= D_801322BC) {
            index = D_801322BC - 1;
        }
        return D_801322C0[index];
    }
    return 0;
}
