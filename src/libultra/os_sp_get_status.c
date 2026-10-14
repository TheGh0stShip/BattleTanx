#include "types.h"

u32 __osSpGetStatus(void) {
    return *(volatile u32*)0xA4040010;
}
