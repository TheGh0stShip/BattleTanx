#include "types.h"

typedef struct SaveRecordBlock {
    s32 words[4];
} SaveRecordBlock;

extern s32 controller_pak_write_save_file(void) __asm__("func_800D0690");
extern void wait_for_loading_state_change(void) __asm__("func_800D0940");
extern s32 gSoundVolume __asm__("D_80125790");
extern s32 gMusicVolume __asm__("D_80125794");
extern u8 D_80134E64;
extern u8 D_80134E65;
extern u8 D_80134E66;
extern u8 D_80134E67;
extern u8 D_80134E69;
extern void *gSaveRecord __asm__("D_80134E78");

s32 write_controller_pak_progress(s8 value08, s32 value0C, s32 value10,
                                  s16 value14, u8 value19,
                                  SaveRecordBlock *records)
    __asm__("func_800D0828");

s32 write_controller_pak_progress(s8 value08, s32 value0C, s32 value10,
                                  s16 value14, u8 value19,
                                  SaveRecordBlock *records)
{
    SaveRecordBlock *source;
    u8 option;
    SaveRecordBlock *destination;
    SaveRecordBlock *end;
    register s32 soundVolume __asm__("$8");
    register s32 musicVolume __asm__("$9");
    register u8 value17 __asm__("$4");
    u8 *first;
    u8 *record;
    u8 *other;
    u8 *fourth;
    u8 value18;

    first = gSaveRecord;
    source = records;
    option = value19;
    first[8] = value08;
    record = gSaveRecord;
    record[0x16] = D_80134E64;
    other = gSaveRecord;
    soundVolume = gSoundVolume;
    musicVolume = gMusicVolume;
    value17 = D_80134E65;
    *(s32 *)(record + 0xC) = value0C;
    *(s32 *)(record + 0x10) = value10;
    *(s16 *)(record + 0x14) = value14;
    other[0x17] = value17;
    fourth = gSaveRecord;
    value18 = D_80134E66;
    *(s32 *)(other + 0x1C) = soundVolume;
    *(s32 *)(other + 0x20) = musicVolume;
    fourth[0x18] = value18;
    ((u8 *)gSaveRecord)[0x1A] = D_80134E67;
    ((u8 *)gSaveRecord)[0x1B] = D_80134E69;
    ((u8 *)gSaveRecord)[0x19] = option;

    end = source + 4;
    destination = (SaveRecordBlock *)((u8 *)gSaveRecord + 0x24);
    do {
        *destination = *source;
        source++;
        destination++;
    } while (source != end);
    *(s32 *)destination = *(s32 *)source;
    if (controller_pak_write_save_file() != 0) {
        wait_for_loading_state_change();
    }
    return 0;
}
