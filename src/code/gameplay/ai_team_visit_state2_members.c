#include "types.h"

typedef struct AiTeam {
    u8 pad00[0x8];
    s16 memberIds[15];
    u16 memberCount;
    u8 pad28[0x28];
    u8 active;
    u8 pad51;
} AiTeam;

typedef struct AiTeamUnit {
    u8 pad000;
    u8 active;
    u8 pad002[0x34E];
    u8 state;
} AiTeamUnit;

extern AiTeam D_8033A980[];

extern AiTeamUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern void func_800EA828(AiTeam *team, AiTeamUnit *unit, u16 teamIndex, s16 unitId);

void ai_team_visit_state2_members(u16 teamIndex) __asm__("func_800E493C");

void ai_team_visit_state2_members(u16 teamIndex) {
    AiTeam *team = &D_8033A980[teamIndex];
    u16 i;
    s16 unitId;
    AiTeamUnit *unit;

    if (team->active != 0) {
        for (i = 0; i < team->memberCount; i++) {
            unitId = team->memberIds[i];
            unit = get_unit(unitId);
            if (unit->active != 0 && unit->state == 2) {
                func_800EA828(team, unit, teamIndex, unitId);
            }
        }
    }
}
