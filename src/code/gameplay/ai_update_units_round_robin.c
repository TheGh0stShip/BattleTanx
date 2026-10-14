#include "types.h"

typedef struct AiMember {
    u8 pad00;
    u8 value01;
    u8 pad02[0x22];
    f32 value24;
    u8 pad28[4];
    f32 value2C;
    u8 pad30[0x6C];
    u32 value9C;
    u8 padA0[0x14];
    s32 valueB4;
    u8 padB8[0x2B4];
    s32 value36C;
} AiMember;

extern s32 get_elapsed_game_ticks(void) __asm__("func_8007B1DC");
extern s32 seconds_to_game_ticks(f32 seconds) __asm__("func_8007B1EC");
extern AiMember *get_unit(s16 id) __asm__("func_800A03B8");
extern s32 ai_member_status_is_1(AiMember *member) __asm__("func_800E3470");
extern void ai_award_self_kill_credit(AiMember *unit) __asm__("func_800E4494");
extern void func_800E5DE4(s16 id);
extern void func_800E5FA8(AiMember *member, void *state, f32 *pos, s32 *budget, s32 a, s32 b);
extern s32 ai_get_indexed_float_address(AiMember *store, s32 index) __asm__("func_800E9880");
extern f32 D_800746B0;
extern s16 gAiRoundRobinUnit __asm__("D_801358B0");

void ai_update_units_round_robin(s32 arg0, s32 arg1, s32 *budget) __asm__("func_800E63F4");

void ai_update_units_round_robin(s32 arg0, s32 arg1, s32 *budget) {
    f32 pos[2];
    s16 i;
    AiMember *m;

    for (i = 0; i < 20; i++) {
        m = get_unit(i);
        if (m->value01 == 0 || ai_member_status_is_1(m) != 0) {
            if (i == gAiRoundRobinUnit) {
                gAiRoundRobinUnit = (i + 1) % 20;
            }
            continue;
        }
        if (i == gAiRoundRobinUnit && *budget != 0) {
            pos[1] = m->value24;
            pos[0] = m->value2C;
            func_800E5FA8(m, &m->value9C, pos, budget, ai_get_indexed_float_address(m, 0x1004), ai_get_indexed_float_address(m, 0x1005));
            func_800E5FA8(m, &m->valueB4, pos, 0, ai_get_indexed_float_address(m, 0x1006), ai_get_indexed_float_address(m, 0x1007));
            gAiRoundRobinUnit = (gAiRoundRobinUnit + 1) % 20;
            if (m->value9C >= 10) {
                m->value36C = 0;
            } else if (m->value9C < 8) {
                m->value36C = 0;
            } else if (m->valueB4 != 0) {
                m->value36C = 0;
            } else if (m->value36C == 0) {
                m->value36C = get_elapsed_game_ticks() + seconds_to_game_ticks(D_800746B0);
            } else if (m->value36C < get_elapsed_game_ticks()) {
                ai_award_self_kill_credit(m);
            }
        } else {
            pos[1] = m->value24;
            pos[0] = m->value2C;
            func_800E5FA8(m, &m->value9C, pos, 0, ai_get_indexed_float_address(m, 0x1004), ai_get_indexed_float_address(m, 0x1005));
            func_800E5FA8(m, &m->valueB4, pos, 0, ai_get_indexed_float_address(m, 0x1006), ai_get_indexed_float_address(m, 0x1007));
        }
        func_800E5DE4(i);
    }
}
