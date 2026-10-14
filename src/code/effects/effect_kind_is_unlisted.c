#include "types.h"

s32 effect_kind_is_unlisted(s32 kind) __asm__("func_8008ADE0");

s32 effect_kind_is_unlisted(s32 kind) {
    switch (kind) {
    case 2:
    case 4:
    case 12:
    case 13:
    case 17:
    case 24:
    case 27:
    case 29:
    case 30:
    case 34:
        return 0;
    }
    return 1;
}
