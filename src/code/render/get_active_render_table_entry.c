#include "types.h"

extern void *get_render_context(void) __asm__("func_800821C0");
extern s16 D_802D5A36;

s32 get_active_render_table_entry(void) __asm__("func_8008CED0");

s32 get_active_render_table_entry(void)
{
    u8 *context;
    u8 *table;
    u8 *group;
    u8 *entry;

    context = get_render_context();
    table = *(u8 **)(context + 0x570) + D_802D5A36 * 0xC;
    group = *(u8 **)(context + 0x574) + *(u16 *)(table + 2) * 4;
    entry = *(u8 **)(context + 0x578) + *(u16 *)(group + 2) * 0xC;
    return *(s32 *)(context + 0x580) + *(s32 *)(entry + 4) * 8;
}
