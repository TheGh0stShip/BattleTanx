#include "types.h"

typedef struct PlayTeam {
    s16 unitIds[5];
} PlayTeam;

typedef struct PlayUnit {
    u8 pad00;
    u8 active;
    u8 pad02[0x96];
    s32 value98;
} PlayUnit;

typedef struct PlayContext {
    u8 pad00[0x1A];
    u16 teamIndex;
} PlayContext;

extern f32 D_800747C4;
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern PlayTeam *get_entity_record(u16 index) __asm__("func_800A6688");
extern PlayUnit *get_unit(s16 id) __asm__("func_800A03B8");

f32 ai_score_team_has_active_value98(PlayContext *context) __asm__("func_800E87A0");

f32 ai_score_team_has_active_value98(PlayContext *context) {
    u16 index = context->teamIndex;
    f32 result = 0.0f;
    PlayTeam *team;
    u16 i;
    PlayUnit *unit;

    if (index >= get_entity_capacity()) {
        return result;
    }
    team = get_entity_record(index);
    for (i = 0; i < 5; i++) {
        unit = get_unit(team->unitIds[i]);
        if (unit->active && unit->value98 != 0) {
            result = D_800747C4;
            break;
        }
    }
    return result;
}
