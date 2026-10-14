#include "types.h"

typedef struct LinkedTeamOwner {
    u8 pad000[0x1AA];
    s16 linkedId;
} LinkedTeamOwner;

typedef struct LinkedTeamUnit {
    u8 pad00[0x4];
    u8 entityIndex;
} LinkedTeamUnit;

typedef struct LinkedTeamEntity {
    u8 pad000[0x1AE];
    u8 team;
} LinkedTeamEntity;

typedef struct LinkedTeamContext {
    u8 pad00[0x4];
    LinkedTeamOwner *owner;
    u8 pad08[0x14];
    u8 team;
} LinkedTeamContext;

extern LinkedTeamUnit *get_unit(s16 id) __asm__("func_800A03B8");
extern LinkedTeamEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern f32 gLinkedTeamDiffersWeight __asm__("D_8007482C");

f32 ai_parameter_linked_entity_team_differs(LinkedTeamContext *context) __asm__("func_800E8F1C");

f32 ai_parameter_linked_entity_team_differs(LinkedTeamContext *context)
{
    f32 weight;

    if (context->owner->linkedId == 0xFF) {
        goto none;
    }
    {
        u8 team = get_entity_record(get_unit(context->owner->linkedId)->entityIndex)->team;

        weight = gLinkedTeamDiffersWeight;
        if (team == context->team) {
        none:
            weight = 0.0f;
        }
    }
    return weight;
}
