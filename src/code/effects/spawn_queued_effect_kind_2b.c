#include "types.h"

typedef struct EffectVec3 {
    f32 x;
    f32 y;
    f32 z;
} EffectVec3;

typedef struct QueuedEffect {
    u8 pad00[0xC];
    f32 value0C;
    f32 value10;
    EffectVec3 position;
    s32 value20;
    void *effect;
    struct QueuedEffect *next;
} QueuedEffect;

typedef struct EffectKind2BParams {
    s32 value00;
    EffectVec3 position;
    f32 value10;
    f32 value14;
    s32 value18;
    s32 lifetime;
    u16 value20;
    u16 value22;
    u16 value24;
    u16 value26;
    u16 value28;
} EffectKind2BParams;

extern QueuedEffect *allocate_effect(s32 group, s32 kind, s32 size) __asm__("func_8008AD10");
extern void func_8008B89C(QueuedEffect *effect);
extern void *spawn_effect_kind_2b(EffectKind2BParams *params) __asm__("func_8010BDA0");
extern QueuedEffect *gQueuedEffectHead __asm__("D_80125D40");
extern QueuedEffect *gQueuedEffectTail __asm__("D_80125D44");
extern s16 gQueuedEffectCount __asm__("D_80125D48");

void spawn_queued_effect_kind_2b(EffectVec3 *position, f32 a, f32 b, s32 value, s32 param)
    __asm__("func_80093D50");

/* Spawns a kind 0x2B effect and appends its record to a queue capped at ten entries. */
void spawn_queued_effect_kind_2b(EffectVec3 *position, f32 a, f32 b, s32 value, s32 param)
{
    EffectKind2BParams params;
    QueuedEffect *entry = allocate_effect(0, 4, 0x2C);

    if (entry != 0) {
        entry->position = *position;
        entry->next = 0;
        entry->value20 = value;
        entry->value0C = -a;
        entry->value10 = -b;
        params.value00 = 0;
        params.position = *position;
        params.lifetime = -1;
        params.value22 = 100;
        params.value20 = 100;
        params.value24 = 30;
        params.value26 = 150;
        params.value10 = -a;
        params.value14 = -b;
        params.value18 = param;
        params.value28 = 60;
        entry->effect = spawn_effect_kind_2b(&params);
        if (gQueuedEffectCount == 0) {
            gQueuedEffectTail = entry;
            gQueuedEffectHead = entry;
            gQueuedEffectCount = 1;
        } else {
            gQueuedEffectTail->next = entry;
            gQueuedEffectTail = entry;
            gQueuedEffectCount++;
        }
        if (gQueuedEffectCount > 10) {
            func_8008B89C(gQueuedEffectHead);
            gQueuedEffectCount--;
            gQueuedEffectHead = gQueuedEffectHead->next;
        }
    }
}
