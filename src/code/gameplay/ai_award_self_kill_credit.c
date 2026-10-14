#include "types.h"

typedef struct KillCreditUnit {
    u8 pad00[0x4];
    u8 entityId;
} KillCreditUnit;

typedef struct KillCreditEntity {
    u8 pad000[0x1AC];
    u16 killCount;
} KillCreditEntity;

extern s32 func_800983E0(KillCreditUnit *unit, s32 amount, u8 entityId, s32 arg3);
extern KillCreditEntity *func_800A6688(u8 entityId);

void ai_award_self_kill_credit(KillCreditUnit *unit) __asm__("func_800E4494");

void ai_award_self_kill_credit(KillCreditUnit *unit)
{
    KillCreditEntity *entity;
    u16 count;

    func_800983E0(unit, 10000, unit->entityId, 0);
    entity = func_800A6688(unit->entityId);
    count = entity->killCount;
    if (count < 10000) {
        entity->killCount = count + 1;
    }
}
