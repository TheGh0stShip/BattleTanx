#include "types.h"

typedef struct EffectRampDef {
    u8 pad00[0x4];
    u16 duration;
    u8 pad06[0x2];
    s16 start;
    s16 end;
    u16 flags;
} EffectRampDef;

typedef struct EffectRamp {
    u8 pad00[0xC];
    u8 defIndex;
    u8 pad0D[0x3];
    u16 startTime;
    u16 now;
    u16 elapsed;
    u8 pad16[0x2];
    s32 value18;
    u8 pad1C[0xC];
    u16 value28;
    u16 value2A;
} EffectRamp;

extern EffectRampDef *D_80137940[];
extern u64 func_8007B268(void) __asm__("func_8007B268");
extern void func_8008C6F0(s32 value, s32 start);

void update_effect_value_ramp(EffectRamp *e, s32 *state) __asm__("func_800EE164");

void update_effect_value_ramp(EffectRamp *e, s32 *state)
{
    EffectRampDef *def = D_80137940[e->defIndex];
    u16 now;
    u16 elapsed;
    u32 duration;
    s32 start;
    s32 end;
    f32 ratio;

    now = (u32)func_8007B268() >> 16;
    e->now = now;
    elapsed = now - e->startTime;
    e->elapsed = elapsed;
    duration = def->duration;
    if (duration >= elapsed) {
        end = def->end;
        start = def->start;
        ratio = (f32)(end - start) / (f32)duration;
        e->value18 = start + elapsed * ratio;
        e->value28 += e->value2A;
        if (D_80137940[e->defIndex]->flags & 0x10) {
            func_8008C6F0(e->value18, start);
        }
    } else {
        *state = 2;
    }
}
