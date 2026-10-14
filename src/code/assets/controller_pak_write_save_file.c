#include "types.h"

typedef struct PakFileEntry {
    u8 pad00[0xE];
    u8 name[16];
    u8 pad1E[0x2];
} PakFileEntry;

#define PAK_FILE_COUNT 15
#define PAK_NAME_LENGTH 16

extern s32 gPakHandle __asm__("D_8032815C");
extern s32 gPakStatus __asm__("D_80328160");
extern s32 gPakFreePages __asm__("D_80328164");
extern s32 gPakFileCount __asm__("D_80328168");
extern s32 gPakSaveFileIndex __asm__("D_8032816C");
extern PakFileEntry gPakFiles[PAK_FILE_COUNT] __asm__("D_80327F50");
extern s32 gPakDefaultStatus __asm__("D_80126710");
extern u8 gPakSaveName[PAK_NAME_LENGTH] __asm__("D_80126718");

extern s32 func_800A942C(void);
extern s32 func_800A9484(s32 handle);
extern s32 func_800A95C0(s32 handle, PakFileEntry *files, s32 *count);
extern s32 func_800A9B70(s32 handle, s32 *freePages);
extern u32 gPakSaveBuffer[] __asm__("D_80328180");
extern s32 write_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer) __asm__("func_800A9920");

s32 controller_pak_write_save_file(void) __asm__("func_800D0690");

s32 controller_pak_write_save_file(void)
{
    s32 found;
    s32 i;
    s32 j;
    u8 *name;

    gPakHandle = func_800A942C();
    if (gPakHandle != 0) {
        gPakStatus = func_800A9484(gPakHandle);
        if (gPakStatus == 2 || gPakStatus == 0) {
            gPakStatus = func_800A95C0(gPakHandle, gPakFiles, &gPakFileCount);
            if (gPakStatus != 0) {
                goto probed;
            }
            gPakStatus = func_800A9B70(gPakHandle, &gPakFreePages);
        }
    } else {
        gPakStatus = 0;
    }
    if (gPakStatus == 0) {
        gPakStatus = gPakDefaultStatus;
    }
probed:
    if (gPakHandle > 0 && gPakStatus == 0) {
        for (i = 0; i < PAK_FILE_COUNT; i++) {
            name = gPakFiles[i].name;
            for (j = 0; j < PAK_NAME_LENGTH; j++) {
                if (*name++ != gPakSaveName[j]) {
                    break;
                }
            }
            if (j == PAK_NAME_LENGTH) {
                found = i;
                goto searched;
            }
        }
        found = -1;
    searched:
        gPakSaveFileIndex = found;
        if (found != -1) {
            gPakStatus = write_controller_pak_save(gPakHandle, found, gPakSaveBuffer);
            if (gPakStatus == 0) {
                return 0;
            }
        }
    }
    return -1;
}
