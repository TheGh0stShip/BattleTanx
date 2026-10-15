#include "types.h"

/* Initialized data at 0x80140009..0x8014000C (ROM 0xD0009..0xD000C). */
typedef struct Data80140009 {
    u8 pad0[3];
} Data80140009;

Data80140009 D_80140009 = {
    { 0x0F, 0x51, 0x8D },
};
