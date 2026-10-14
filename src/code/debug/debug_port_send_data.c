#include "types.h"

extern s32 disable_interrupt_bit0(void) __asm__("func_80076000");
extern void set_status_register_bits(s32 bits) __asm__("func_80076038");
extern void func_80076408(u32 dest, u32 source, u32 length);
extern u32 func_80076BF0(s32 command, s32 arg0, u32 length, s32 arg2);

s32 debug_port_send_data(s32 port, u32 source, u32 length) __asm__("func_80076F60");

s32 debug_port_send_data(s32 port, u32 source, u32 length) {
    s32 total;
    s32 savedStatus;
    u32 request;
    u32 sent;

    savedStatus = disable_interrupt_bit0();
    total = 0;
    while (length != 0) {
        request = length;
        if (request > 0x8000) {
            request = 0x8000;
        }
        func_80076408(0xB1FF0000, source, request);
        sent = func_80076BF0(0x606, port, request, 0);
        if (sent == 0) {
            set_status_register_bits(savedStatus);
            return total;
        }
        source += sent;
        length -= sent;
        total += sent;
    }
    set_status_register_bits(savedStatus);
    return total;
}
