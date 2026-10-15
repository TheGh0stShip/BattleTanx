#include "types.h"

extern s32 disable_interrupt_bit0(void) __asm__("func_80076000");
extern void set_status_register_bits(s32 bits) __asm__("func_80076038");
extern void debug_pi_read_to_buffer(u32 source, u32 destination, u32 length)
    __asm__("func_80076164");
extern u32 debug_port_send_command(u32 command, u32 address, u32 length, u32 value)
    __asm__("func_80076BF0");

u32 debug_port_receive_data(s32 address, u32 destination, u32 length)
    __asm__("func_80076E9C");

u32 debug_port_receive_data(s32 address, u32 destination, u32 length)
{
    s32 total;
    s32 status;
    u32 request;
    u32 received;

    status = disable_interrupt_bit0();
    total = 0;
    while (length != 0) {
        request = length;
        if (request > 0x8000) {
            request = 0x8000;
        }
        received = debug_port_send_command(0x505, address, request, 0);
        if (received == 0) {
            break;
        }
        debug_pi_read_to_buffer(0xB1FF0000, destination, received);
        total += received;
        destination += received;
        length -= received;
    }
    set_status_register_bits(status);
    return total;
}
