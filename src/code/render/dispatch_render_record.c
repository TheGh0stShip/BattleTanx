#include "types.h"

typedef struct RenderRecord {
    u8 pad00[0xC];
    u8 kind;
    u8 pad0D;
    u16 flags;
    s32 value10;
    s32 value14;
} RenderRecord;

typedef struct RenderSource {
    u8 pad00[4];
    s32 value04;
} RenderSource;

extern void prepare_render_target(void *target) __asm__("func_800A7650");
extern void submit_render_record(void *target, s32 value14, s32 zero, s32 value10, u16 flags)
    __asm__("func_800A7744");
extern void dispatch_render_source(void *target, s32 value) __asm__("func_800EC7A8");

void dispatch_render_record(RenderRecord *record, s32 unused, RenderSource *source, void *target)
    __asm__("func_80078CF8");

void dispatch_render_record(RenderRecord *record, s32 unused, RenderSource *source, void *target)
{
    switch (record->kind) {
    case 0:
    case 2:
    case 3:
        prepare_render_target(target);
        submit_render_record(target, record->value14, 0, record->value10, record->flags);
        break;
    case 1:
        dispatch_render_source(target, source->value04);
        break;
    }
}
