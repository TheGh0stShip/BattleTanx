#include "types.h"

extern u32 gGameMode __asm__("D_80137904");
extern s32 gRuntimeStatus __asm__("D_80137908");

void update_runtime_status_for_mode(void) __asm__("func_800ECBA8");

void update_runtime_status_for_mode(void) {
    switch (gGameMode) {
    case 2:
    case 3:
    case 11:
        gRuntimeStatus = 0x11;
        break;
    case 7:
        gRuntimeStatus = 0x18;
        break;
    }
}
