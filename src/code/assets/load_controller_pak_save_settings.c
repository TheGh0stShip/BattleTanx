#include "types.h"

typedef struct {
    u8 pad00[0x16];
    u8 value16;
    u8 value17;
    u8 value18;
    u8 pad19;
    u8 value1A;
    u8 value1B;
    s32 value1C;
    s32 value20;
} SaveSettings;

extern s32 D_8032815C;
extern s32 D_8032816C;
extern s32 D_80328160;
extern u32 D_80328180;
extern SaveSettings *D_80134E78;
extern u8 D_80134E64;
extern u8 D_80134E65;
extern u8 D_80134E66;
extern u8 D_80134E67;
extern u8 D_80134E69;
extern s32 D_80125790;
extern s32 D_80125794;
extern s32 D_80134E5C;
extern s32 gControllerSlotCount __asm__("D_80134E58");

extern s32 read_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer) __asm__("func_800A9850");

s32 load_controller_pak_save_settings(void) __asm__("func_800D0B0C");

s32 load_controller_pak_save_settings(void) {
    s32 result = -1;

    D_80328160 = read_controller_pak_save(D_8032815C, D_8032816C, &D_80328180);
    if (D_80328160 == 0) {
        SaveSettings *save = D_80134E78;
        D_80134E64 = save->value16;
        D_80125790 = save->value1C;
        D_80125794 = save->value20;
        D_80134E65 = save->value17;
        D_80134E66 = save->value18;
        D_80134E67 = save->value1A;
        D_80134E69 = save->value1B;
        result = 0;
        D_80134E5C = 0;
        gControllerSlotCount = 1;
    }
    return result;
}
