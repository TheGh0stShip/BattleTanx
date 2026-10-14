#include "types.h"
#include "ai_play_stack.h"

typedef struct AiRefreshMember {
    u8 pad000;
    u8 active;
    u8 pad002[0x98 - 0x002];
    s32 value098;
    u8 pad09C[0xCC - 0x09C];
    s32 value0CC;
    u8 pad0D0[0xD4 - 0x0D0];
    s32 value0D4;
    u8 pad0D8[0x350 - 0x0D8];
    u8 value350;
} AiRefreshMember;

typedef struct AiRefreshTeam {
    u8 pad00[0x08];
    s16 members[15];
    u16 memberCount;
    u8 pad28[0x50 - 0x28];
    u8 enabled;
    u8 pad51;
} AiRefreshTeam;

extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s16 *get_linked_entity_ids(u16 id) __asm__("func_800A6688");
extern AiRefreshMember *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 ai_member_status_is_1(AiRefreshMember *member) __asm__("func_800E3470");
extern void ai_init_action_context(AiActionContext *context, s16 memberId) __asm__("func_800E9894");
extern void ai_play_stack_unwind(AiActionContext *context, u32 depth) __asm__("func_800EA1FC");
extern void ai_play_stack_push(AiPlayStack *stack, s32 play) __asm__("func_800EA1B8");
extern void ai_update_member_plays(AiRefreshTeam *team, AiRefreshMember *member, u16 teamIndex, s16 memberId) __asm__("func_800EA828");
extern void func_800EA89C(u16 slot) __asm__("func_800EA89C");
extern u16 D_80135894;
extern s16 D_80135896;
extern AiRefreshTeam D_8033A980[];
extern s32 gEntitySlotActive[] __asm__("D_8033AAC8");

void ai_refresh_member_plays(void) __asm__("func_800E4AA4");

void ai_refresh_member_plays(void) {
    AiActionContext context;
    u16 i;
    u16 j;
    u16 slot;
    u16 t;
    u16 k;
    s16 memberId;
    AiRefreshMember *unit;
    s16 *ids;
    s16 id;
    AiRefreshMember *member;
    AiRefreshTeam *team;

    if (D_80135896 <= 0) {
        for (slot = 0; slot < get_entity_capacity(); slot++) {
            gEntitySlotActive[slot] = 1;
        }
        D_80135896 = 100;
    } else {
        D_80135896 = D_80135896 - 1;
    }

    for (i = 0; i < get_entity_capacity(); i++) {
        ids = get_linked_entity_ids(i);
        for (j = 0; j < 5; j++) {
            id = ids[j];
            member = get_unit(id);
            if (member->active == 0 || ai_member_status_is_1(member) != 0) {
                continue;
            }
            if (member->value098 == 0) {
                if (member->value0CC != 0 && member->value0D4 == 16) {
                    ai_init_action_context(&context, id);
                    ai_play_stack_unwind(&context, 0);
                }
            } else if (member->value0CC != 0 && member->value0D4 != 16) {
                ai_init_action_context(&context, id);
                ai_play_stack_unwind(&context, 0);
                ai_play_stack_push(context.stack, 16);
            }
        }
        if (gEntitySlotActive[i] != 0) {
            gEntitySlotActive[i] = 0;
            func_800EA89C(i);
        }
    }

    for (t = 0; t < D_80135894; t++) {
        team = &D_8033A980[t];
        if (team->enabled != 0) {
            for (k = 0; k < team->memberCount; k++) {
                memberId = team->members[k];
                unit = get_unit(memberId);
                if (unit->active != 0 && unit->value350 == 2) {
                    ai_update_member_plays(team, unit, t, memberId);
                }
            }
        }
    }
}
