#include "types.h"

typedef struct RenderByteRecord {
    u8 pad00[0x1E];
    u8 bytes[4];
} RenderByteRecord;

typedef struct UnalignedWord {
    u32 value;
} __attribute__((packed)) UnalignedWord;

extern RenderByteRecord *func_8007F060(void);

void copy_render_record_bytes(const u8 *source) __asm__("func_800A9F48");

void copy_render_record_bytes(const u8 *source)
{
    RenderByteRecord *record = func_8007F060();
    *(UnalignedWord *)record->bytes = *(const UnalignedWord *)source;
}
