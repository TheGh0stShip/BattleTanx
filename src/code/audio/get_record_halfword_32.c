#include "types.h"

s32 get_record_halfword_32(void *record) __asm__("func_80119B50");

s32 get_record_halfword_32(void *record)
{
    return *(s16 *)((u8 *)record + 0x32);
}
