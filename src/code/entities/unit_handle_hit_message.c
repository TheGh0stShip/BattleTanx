#include "types.h"

typedef struct HitUnit HitUnit;

typedef struct HitHandlerEntry {
    void (*handle)(HitUnit *handler, void *message, s32 arg2, void *info, s32 *result);
    u8 pad04[8];
} HitHandlerEntry;

struct HitUnit {
    u8 pad000[4];
    u8 entityId;
    u8 pad005[3];
    s32 handlerIndex;
    u8 pad00C[8];
    u16 flags;
    u8 pad016[2];
    s32 value18;
    s32 health;
    u8 pad020[0x3E0 - 0x20];
    f32 value3E0;
    f32 value3E4;
    u8 pad3E8[0x4FC - 0x3E8];
    HitUnit *handler;
};

typedef struct HitMessage {
    u8 pad00[8];
    u32 kind;
    HitUnit *sender;
    u8 pad10[0x18];
    u8 sourceId;
    u8 pad29[3];
    HitUnit *value2C;
    u8 pad30[4];
    HitUnit *value34;
} HitMessage;

typedef struct HitInfo {
    u8 pad00[0x10];
    s32 amount;
    s32 value14;
    u8 value18;
} HitInfo;

typedef struct HitContext {
    u8 pad00[0xC];
    HitUnit *unit;
} HitContext;

extern void func_800983E0(HitUnit *unit, s32 amount, s32 sourceId, s32 arg3);
extern void spawn_effect_kind_26(void *position, s32 variant) __asm__("func_800ED8C0");
extern void func_80097DD0(HitUnit *unit, s32 attacker, s32 destroyed);
extern HitHandlerEntry D_802C3804[];

void unit_handle_hit_message(HitContext *context, HitMessage *message, HitInfo *info, s32 *result)
    __asm__("func_8009EEC0");

void unit_handle_hit_message(HitContext *context, HitMessage *message, HitInfo *info, s32 *result) {
    HitUnit *unit = context->unit;
    s32 value14 = info->value14;
    HitUnit *handler;
    HitUnit *sender;
    u16 flags;
    s32 state;

    switch (message->kind) {
    case 12:
        *result = 0;
        func_800983E0(unit, info->amount, message->sourceId, info->value18);
        if (unit->health == 0) {
            spawn_effect_kind_26(info, 0x13);
        }
        break;
    case 2:
    case 22:
    case 34:
        handler = unit->handler;
        if (handler != 0) {
            if (message->kind == 2 && message->value34 == handler) {
                break;
            }
            if (message->kind == 0x22 && message->value2C == handler) {
                break;
            }
            if (D_802C3804[handler->handlerIndex].handle != 0) {
                D_802C3804[handler->handlerIndex].handle(unit->handler, message, 0, info, result);
            }
        } else {
            *result = 0;
            func_800983E0(unit, info->amount, value14, info->value18);
            unit->value3E0 += info->amount / 4;
            unit->value3E4 += info->amount / 4;
            if (unit->health <= 0) {
                *result = 6;
            }
        }
        break;
    case 6:
    case 37:
        *result = 1;
        break;
    case 0:
        flags = unit->flags;
        sender = message->sender;
        if (flags & 0x10) {
            *result = 5;
            break;
        }
        state = unit->value18;
        if (state == 1 && sender->value18 == 2) {
            unit->flags = flags | 0x10;
            unit->health = 0;
            func_80097DD0(unit, sender->entityId, 1);
            *result = state;
        } else {
            *result = 0;
        }
        break;
    case 15:
        func_800983E0(unit, info->amount, message->sourceId, info->value18);
        unit->value3E0 += 5.0f;
        unit->value3E4 += 5.0f;
        *result = 1;
        break;
    case 44:
        break;
    default:
        *result = 0;
        break;
    }
}
