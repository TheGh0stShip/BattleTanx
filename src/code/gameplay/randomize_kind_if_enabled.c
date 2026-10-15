#include "types.h"

extern u32 random_u32(void) __asm__("func_800F38F4");
extern u8 D_80134E68;

s32 randomize_kind_if_enabled(s32 kind) __asm__("func_80088590");
s32 randomize_kind_if_enabled(s32 kind) {
    if (D_80134E68 != 0) {
        switch (kind) {
            case 5:
            case 6:
            case 7:
            case 9:
            case 10:
            case 13:
            case 14:
            case 16:
                switch (random_u32() % 11) {
                    case 0:
                    case 1:
                    case 2:
                        return 0;
                    case 3:
                    case 4:
                        return 3;
                    case 5:
                    case 6:
                        return 2;
                    case 7:
                        return 4;
                    case 8:
                        return 8;
                    case 9:
                        return 12;
                    case 10:
                        return 15;
                }
                break;
        }
    }
    return kind;
}
