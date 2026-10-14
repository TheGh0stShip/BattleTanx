#include "types.h"

typedef struct DisplayCommand {
    u32 word0;
    u32 word1;
} DisplayCommand;

typedef struct DisplayListState {
    u8 pad00[0xD8];
    DisplayCommand *head;
} DisplayListState;

extern DisplayListState *gDisplayListState __asm__("D_801257D0");

void append_display_commands(s32 count, DisplayCommand *src) __asm__("func_8007EF64");

void append_display_commands(s32 count, DisplayCommand *src) {
    DisplayCommand **head = &gDisplayListState->head;

    while (count--) {
        DisplayCommand *dst = *head;
        *head = dst + 1;
        *dst = *src++;
    }
}
