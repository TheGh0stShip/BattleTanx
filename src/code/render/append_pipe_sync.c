#include "types.h"

typedef struct DisplayListCommand {
    u32 word0;
    u32 word1;
} DisplayListCommand;

typedef struct RenderRecord {
    u8 pad00[4];
    DisplayListCommand *displayList;
} RenderRecord;

extern RenderRecord *func_8007F060(void);

void append_pipe_sync(void) __asm__("func_800AB128");

void append_pipe_sync(void)
{
    RenderRecord *record = func_8007F060();
    DisplayListCommand *command = record->displayList++;
    command->word0 = 0xE7000000;
    command->word1 = 0;
}
