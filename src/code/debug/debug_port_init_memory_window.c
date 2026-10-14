#include "types.h"

extern s32 disable_interrupt_bit0(void) __asm__("func_80076000");
extern void set_status_register_bits(s32 bits) __asm__("func_80076038");
extern void func_80077110(void);
extern void func_80076068(u32 addr, s32 value);
extern u32 D_80000318;
extern u32 D_80125558;
extern u32 D_80125568;
extern u8 D_80147370;
extern u8 D_80147372;

void debug_port_init_memory_window(void) __asm__("func_800768E4");

void debug_port_init_memory_window(void) {
    s32 saved;
    u32 size;

    saved = disable_interrupt_bit0();
    func_80077110();
    func_80076068(0xB1FFFFF0, 0);
    func_80076068(0xB1FFFFFC, 0);
    size = D_80000318;
    D_80147370 = 1;
    D_80147372 = 0xFF;
    if (size > 0x3FFFFF) {
        if (!(size & 0x1FFFF) & (size <= 0x02000000)) {
            size--;
            D_80125558 = size - 0x80000000;
            D_80125568 = size + 0xA0000000;
        }
    }
    set_status_register_bits(saved);
}
