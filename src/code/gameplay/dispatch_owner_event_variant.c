#include "types.h"

typedef struct EventOwner {
    u8 pad00[3];
    u8 enabled;
} EventOwner;

extern void apply_owner_event(EventOwner *owner, u32 event, s32 flags) __asm__("func_80099D90");
extern u32 next_random_u32(void) __asm__("func_800F38F4");
extern s32 gElapsedGameTicks __asm__("D_801B4AA8");

void dispatch_owner_event_variant(EventOwner *owner, u32 event) __asm__("func_8009A22C");

void dispatch_owner_event_variant(EventOwner *owner, u32 event) {
    switch (event) {
    case 23:
        break;
    case 22:
        switch (next_random_u32() & 0x1F) {
        case 0:
            apply_owner_event(owner, 1, 0);
            break;
        case 1: case 2: case 3: case 4: case 5: case 6:
            apply_owner_event(owner, 2, 0);
            break;
        case 7: case 8: case 9: case 10: case 11: case 12:
            apply_owner_event(owner, 3, 0);
            break;
        case 13: case 14:
            apply_owner_event(owner, 4, 0);
            break;
        case 15: case 16: case 17: case 18: case 19:
            apply_owner_event(owner, 7, 0);
            break;
        case 20: case 21:
            apply_owner_event(owner, 9, 0);
            break;
        case 22: case 23:
            apply_owner_event(owner, 15, 0);
            break;
        case 24: case 25:
            apply_owner_event(owner, 12, 0);
            break;
        case 26: case 27: case 28: case 29:
            apply_owner_event(owner, 18, 0);
            break;
        case 30: case 31:
            apply_owner_event(owner, 19, 0);
            break;
        }
        break;
    case 1:
        if (owner->enabled != 0 && gElapsedGameTicks <= 0) {
            apply_owner_event(owner, 1, 0);
        }
        break;
    default:
        apply_owner_event(owner, event, 0);
        break;
    }
}
