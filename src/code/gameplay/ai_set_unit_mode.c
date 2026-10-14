#include "ai_play_stack.h"

typedef struct ModeUnit {
    u8 pad000[0x4];
    u8 teamIndex;
    u8 pad005[0xF];
    u16 flags;
    u8 pad016[0x33A];
    u8 mode;
    u8 pad351[0xB9];
    u8 value40A;
} ModeUnit;

extern ModeUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void ai_init_action_context(AiActionContext *context, s16 memberId) __asm__("func_800E9894");
extern void ai_play_stack_unwind(AiActionContext *context, u32 depth) __asm__("func_800EA1FC");
extern void ai_play_stack_push(AiPlayStack *stack, s32 play) __asm__("func_800EA1B8");

void ai_set_unit_mode(ModeUnit *unit, u8 mode) __asm__("func_800E26DC");

static inline s16 find_unit_member_id(ModeUnit *unit) {
    s16 i;

    s32 base;

    base = unit->teamIndex * 5;
    for (i = base; i < base + 5; i++) {
        if (unit == get_unit(i)) {
            return i;
        }
    }
    return 0xFF;
}

void ai_set_unit_mode(ModeUnit *unit, u8 mode) {
    AiActionContext context;
    s32 previous;

    previous = unit->mode;
    unit->mode = mode;
    if (mode == 2) {
        unit->value40A = 0x80;
        if (previous == 1 && !(unit->flags & 4)) {
            ai_init_action_context(&context, find_unit_member_id(unit));
            ai_play_stack_unwind(&context, 0);
            ai_play_stack_push(context.stack, 0xB);
        }
    } else {
        unit->value40A = 0x10;
    }
}
