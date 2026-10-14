#include "types.h"

typedef struct RenderRecordHalfwords {
    u8 pad00[0x16];
    u16 previous;
    u16 current;
    u8 pad1A[0x12];
    u16 source;
} RenderRecordHalfwords;

extern RenderRecordHalfwords *func_8007F060(void);

void reset_render_record_halfwords(void) __asm__("func_800A9C20");

void reset_render_record_halfwords(void)
{
    RenderRecordHalfwords *record = func_8007F060();
    record->previous = record->source;
    record->current = 0;
}
