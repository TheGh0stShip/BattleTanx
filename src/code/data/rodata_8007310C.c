#include "types.h"

/* Initialized rodata at 0x8007310C..0x80073110 (ROM 0x310C..0x3110). */
typedef struct Rodata8007310C {
    u32 word0;
} Rodata8007310C;

const Rodata8007310C D_8007310C = {
    0x000A0645,
};
