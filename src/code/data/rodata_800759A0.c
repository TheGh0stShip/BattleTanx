#include "types.h"

/* Initialized rodata at 0x800759A0..0x800759F0 (ROM 0x59A0..0x59F0). */
typedef struct Rodata800759A0 {
    u32 word0;
    u32 word4;
    char text8[9];
    u8 pad11[3];
    u32 word14;
    u32 word18;
    u32 word1C;
    u32 word20;
    u32 word24;
    u32 word28;
    u32 word2C;
    u32 word30;
    u32 word34;
    u32 word38;
    u32 word3C;
    u32 word40;
    u32 word44;
    u32 word48;
    u32 word4C;
} Rodata800759A0;

const Rodata800759A0 D_800759A0 = {
    0x00141818,
    0x1C1C1C1C,
    "        \000",
    { 0x04, 0x08, 0x08 },
    0x0C0C0C0C,
    0x10101010,
    0x10101010,
    0x80111B58,
    0x80111B20,
    0x80111B00,
    0x80111964,
    0x80111910,
    0x80111AA4,
    0x801118D8,
    0x801118E4,
    0x801118F0,
    0x00000000,
    0x00000000,
    0x00000000,
};
