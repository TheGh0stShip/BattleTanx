#include "types.h"

typedef struct PakFileEntry {
    u8 pad00[0xE];
    u8 name[16];
    u8 pad1E[0x2];
} PakFileEntry;

extern PakFileEntry gPakFiles[15] __asm__("D_80327F50");
extern u8 gPakSaveName[16] __asm__("D_80126718");

s32 controller_pak_find_save_name(void) __asm__("func_800CF454");

s32 controller_pak_find_save_name(void) {
    s32 i;
    s32 j;
    u8 *name;

    for (i = 0; i < 15; i++) {
        name = gPakFiles[i].name;
        for (j = 0; j < 16; j++) {
            if (*name++ != gPakSaveName[j]) {
                break;
            }
        }
        if (j == 16) {
            return i;
        }
    }
    return -1;
}
