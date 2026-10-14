#include "types.h"

extern s32 gControllerSlotCount __asm__("D_80134E58");
extern s32 gControllerStatus[] __asm__("D_802DF540");
extern s32 gControllerPresent[] __asm__("D_802DF560");

extern void func_800A90E0(void);

s32 check_controllers_still_present(void) __asm__("func_800A933C");
void refresh_controller_presence(void) __asm__("func_800A93C8");

s32 check_controllers_still_present(void)
{
    s32 stillPresent;
    s32 i;

    func_800A90E0();
    stillPresent = 1;
    for (i = 0; i < gControllerSlotCount; i++) {
        if (gControllerPresent[i] != 0 && gControllerStatus[i] == -1) {
            stillPresent = 0;
            break;
        }
        gControllerPresent[i] = gControllerStatus[i] != -1;
    }
    return stillPresent;
}

void refresh_controller_presence(void)
{
    s32 i;

    func_800A90E0();
    for (i = 0; i < gControllerSlotCount; i++) {
        gControllerPresent[i] = gControllerStatus[i] != -1;
    }
}
