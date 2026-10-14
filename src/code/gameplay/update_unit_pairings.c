#include "types.h"

typedef struct UnitPairing {
    u8 first;
    u8 second;
    u8 value02;
    u8 value03;
    u8 value04;
    u8 value05;
    u8 value06;
    u8 value07;
    s32 value08;
} UnitPairing;

typedef struct PairedUnit {
    u8 pad000;
    u8 value001;
    u8 pad002[0x12];
    u16 value014;
    u8 pad016[0x334];
    u8 value34A;
    u8 pad34B[0x19];
    s32 value364;
} PairedUnit;

extern PairedUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 entity_state_is_one(PairedUnit *unit) __asm__("func_800E3470");
extern void func_800E56B0(UnitPairing *pairing);
extern void func_800E986C(PairedUnit *unit, s32 event, f32 value);
extern s32 get_frame_time(void) __asm__("func_8007B1DC");
extern UnitPairing D_8033AAE8[];
extern u16 D_8033B448;

void update_unit_pairings(s32 arg0, s32 arg1) __asm__("func_800E5BA0");

static inline void clear_unit_pairing(UnitPairing *p) {
    p->value04 = 0;
    p->value05 = 0;
    p->value06 = 0;
    p->value07 = 0;
    p->value08 = 0;
    p->value03 = 0;
}

static inline void restart_paired_unit(PairedUnit *unit) {
    func_800E986C(unit, 0x1002, 1.0f);
    unit->value364 = get_frame_time();
}

void update_unit_pairings(s32 arg0, s32 arg1) {
    s16 i;
    u16 j;

    if (arg0 != 0) {
        i = 0;
        do {
            PairedUnit *unit = get_unit(i);
            if (unit->value001 != 0) {
                unit->value34A = 1;
            }
            i++;
        } while (i < 20);
    }
    if (arg1 != 0) {
        i = 0;
        do {
            func_800E986C(get_unit(i), 0x1002, 0);
            i++;
        } while (i < 20);
    }
    j = 0;
    if (D_8033B448 != 0) {
        do {
            UnitPairing *p = &D_8033AAE8[j];
            if (p->value02 != 0) {
                if (arg0 != 0) {
                    func_800E56B0(p);
                }
            } else if (arg1 != 0) {
                PairedUnit *a = get_unit(p->first);
                PairedUnit *b = get_unit(p->second);
                if (a->value001 == 0) {
                    clear_unit_pairing(p);
                } else if (((a->value014 & 4) && (b->value014 & 4)) ||
                           (entity_state_is_one(a) != 0 && entity_state_is_one(b) != 0)) {
                    clear_unit_pairing(p);
                    p->value04 = 1;
                    p->value07 = 1;
                } else {
                    func_800E56B0(p);
                    if (p->value05 != 0) {
                        restart_paired_unit(a);
                        restart_paired_unit(b);
                    }
                }
            }
            j++;
        } while (j < D_8033B448);
    }
}
