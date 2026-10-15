#include "types.h"

/* Initialized rodata at 0x80071A6C..0x80071A70 (ROM 0x1A6C..0x1A70). */
typedef struct Rodata80071A6C {
    u32 word0;
} Rodata80071A6C;

const Rodata80071A6C D_80071A6C = {
    0x00080649,
};
