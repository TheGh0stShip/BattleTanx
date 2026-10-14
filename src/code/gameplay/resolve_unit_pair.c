#include "types.h"

typedef struct PairUnit {
    u8 pad000[0x9C];
    s32 state;
    s32 value0A0;
    u8 pad0A4[0xB0 - 0xA4];
    struct PairUnit *partner;
    u8 pad0B4[0x344 - 0xB4];
    u16 value344;
    u8 pad346[0x34A - 0x346];
    u8 value34A;
} PairUnit;

extern PairUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_800E349C(PairUnit *unit) __asm__("func_800E349C");
extern void ai_award_self_kill_credit(PairUnit *unit) __asm__("func_800E4494");
extern void func_800E36FC(s32 *state, s16 a, s16 b) __asm__("func_800E36FC");
extern f32 D_800744EC;
extern f32 D_800744F0;
extern f32 D_800744F4;

void resolve_unit_pair(s16 firstId, s16 secondId, f32 amount) __asm__("func_800E1F14");

void resolve_unit_pair(s16 firstId, s16 secondId, f32 amount) {
    PairUnit *first = get_unit(firstId);
    PairUnit *second = get_unit(secondId);

    if (second->state == 9) {
        func_800E349C(second);
    } else if (second->state == 8) {
        if (amount < D_800744EC) {
            func_800E349C(first);
        }
    } else if (first->state == 8) {
        if (amount < D_800744F0) {
            if (first->partner != second) {
                ai_award_self_kill_credit(first);
            } else {
                second->value0A0 = 0;
                second->value34A = 0;
            }
        }
    } else if (D_800744F4 < amount) {
        first->value0A0 = 0;
        first->value34A = 0;
    } else if (second->value344 != 0) {
        func_800E36FC(&first->state, firstId, secondId);
        second->value0A0 = 0;
        second->value34A = 0;
    }
}
