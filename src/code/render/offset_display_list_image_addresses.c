#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

void offset_display_list_image_addresses(DisplayCommand *commands, s32 count, s32 offset) __asm__("func_800852E0");

void offset_display_list_image_addresses(DisplayCommand *commands, s32 count, s32 offset) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (commands[i].w0 == 0xB8000000) {
            break;
        }
        if (*(u8 *)&commands[i] == 0xFD) {
            commands[i].w1 += offset;
        }
    }
}
