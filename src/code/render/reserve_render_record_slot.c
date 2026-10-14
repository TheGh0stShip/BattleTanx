#include "types.h"

typedef struct RenderCommand {
    u32 words[2];
} RenderCommand;

typedef struct RenderCursorRecord {
    u8 pad00[0x4];
    RenderCommand *cursor;
    u8 pad08[0x1C];
    RenderCommand *reserved;
} RenderCursorRecord;

extern RenderCursorRecord *get_render_record(void) __asm__("func_8007F060");

RenderCommand *reserve_render_record_slot(void) __asm__("func_800AB15C");

RenderCommand *reserve_render_record_slot(void)
{
    RenderCursorRecord *record = get_render_record();

    if (record->reserved == 0) {
        record->reserved = record->cursor++;
        return record->cursor;
    }
    return 0;
}
