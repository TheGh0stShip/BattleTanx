#include "types.h"

typedef struct DisplayListCommand {
    u32 word0;
    u32 word1;
} DisplayListCommand;

extern void func_8007EEF8(void *context);

void end_display_list_and_finalize(DisplayListCommand *command, void *context) __asm__("func_80106B28");

void end_display_list_and_finalize(DisplayListCommand *command, void *context)
{
    command->word0 = 0xB8000000;
    command->word1 = 0;
    func_8007EEF8(context);
}
