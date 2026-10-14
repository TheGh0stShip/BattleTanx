#include "types.h"

typedef struct DebugMemoryRegion {
    u32 limit;
    u32 flags;
} DebugMemoryRegion;

#define DEBUG_PORT_BUFFER 0xB1FE0000
#define DEBUG_PORT_ADDRESS 0xB1FFFFF4
#define DEBUG_PORT_SIZE 0xB1FFFFF8

#define DEBUG_REGION_DIRECT 4
#define DEBUG_REGION_BYTES 8

/* Ascending region limits; flags bit 0/1 permit each transfer direction. */
extern DebugMemoryRegion D_80125550[];
extern u8 D_8F147050[];

extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern void func_80076164(u32 source, u32 dest, u32 length);
extern void debug_pi_read_bytes(u32 source, u32 dest, u32 length) __asm__("func_8007627C");
extern void func_80076408(u32 dest, u32 source, u32 length);
extern void func_800764F4(u32 dest, u32 value, u32 length);
extern void func_800765C0(u32 dest, u32 source, u32 length);

void debug_transfer_memory(s32 direction) __asm__("func_80076634");

void debug_transfer_memory(s32 direction)
{
    u32 address;
    u32 size;
    u32 port;
    u32 chunk;
    u32 flags;
    s32 i;

    port = DEBUG_PORT_BUFFER;
    address = debug_pi_read_word(DEBUG_PORT_ADDRESS);
    size = debug_pi_read_word(DEBUG_PORT_SIZE);
    if (address > 0xEFFFFFFF) {
        address += (u32)D_8F147050;
    }
    while (size != 0) {
        i = 0;
        while (D_80125550[i].limit < address) {
            i++;
        }
        chunk = (D_80125550[i].limit + 1) - address;
        if (size < chunk) {
            chunk = size;
        }
        flags = D_80125550[i].flags;
        if (!(flags & direction)) {
            if (direction == 1) {
                func_800764F4(port, 0, chunk);
            }
        } else if (flags & DEBUG_REGION_DIRECT) {
            if (direction == 1) {
                func_800765C0(port, address, chunk);
            } else {
                func_800765C0(address, port, chunk);
            }
        } else if (direction == 1) {
            func_80076408(port, address, chunk);
        } else if (flags & DEBUG_REGION_BYTES) {
            debug_pi_read_bytes(port, address, chunk);
        } else {
            func_80076164(port, address, chunk);
        }
        port += chunk;
        size -= chunk;
        address += chunk;
    }
}
