#include "types.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void copy_relocated_vertex_texcoords(s32 *commands, s32 relocatedBase)
    __asm__("func_80091814");

void copy_relocated_vertex_texcoords(s32 *commands, s32 relocatedBase)
{
    s32 *command;
    s32 i;
    u16 value;
    u32 count;
    void *source;
    void *destination;

    if (*commands != 0xB8000000) {
        command = commands;
        do {
            if (FIELD(command, u8, 0) == 4) {
                source = FIELD(command, void *, 4);
                i = 0;
                count = FIELD(command, u16, 2) >> 10;
                if (count != 0) {
                    destination = (void *)(relocatedBase +
                        ((s32)source - (s32)commands));
                    do {
                        FIELD(destination, u16, 8) = FIELD(source, u16, 8);
                        value = FIELD(source, u16, 10);
                        i++;
                        source += 0x10;
                        FIELD(destination, u16, 10) = value;
                        destination += 0x10;
                    } while (i < (s32)count);
                }
            }
            command += 2;
        } while (*command != 0xB8000000);
    }
}
