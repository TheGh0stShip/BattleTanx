#include "types.h"

typedef struct ContactSource {
    u8 pad00[0xC];
    void *object;
} ContactSource;

typedef struct PositionWords {
    s32 x;
    s32 y;
    s32 z;
} PositionWords;

void copy_contact_position(void *source, void *position) __asm__("func_8009F5BC");

void copy_contact_position(void *source, void *position)
{
    void *object;

    object = *(void **)((s8 *)source + 0xC);
    *(PositionWords *)position = *(PositionWords *)((s8 *)object + 0x24);
}
