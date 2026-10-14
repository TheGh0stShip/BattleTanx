#include "types.h"

typedef struct ScriptedEffect {
    u8 pad00[0xC];
    u8 script;
    u8 pad0D;
    u16 startTime;
    s16 now;
    s16 elapsed;
    u8 step;
} ScriptedEffect;

typedef struct EffectScriptStep {
    s32 (*handler)(ScriptedEffect *effect, s32 a, s32 b);
    s32 a;
    s32 b;
} EffectScriptStep;

extern u64 func_8007B268(void) __asm__("func_8007B268");
extern EffectScriptStep *gEffectScriptTable[] __asm__("D_80138F3C");

void run_effect_script(ScriptedEffect *effect, s32 *status) __asm__("func_800ED994");

static inline s32 script_has_step(EffectScriptStep *script, s32 step) {
    EffectScriptStep *entry = &script[step];

    return entry->handler != 0;
}

void run_effect_script(ScriptedEffect *effect, s32 *status) {
    EffectScriptStep *script = gEffectScriptTable[effect->script];
    s32 step;
    s32 next;
    u32 now;
    EffectScriptStep *cur;

    now = (u32)func_8007B268() >> 16;
    step = effect->step;
    effect->now = now;
    effect->elapsed = now - effect->startTime;
    if (script_has_step(script, step)) {
        do {
            cur = &script[(u8)step];
            if (cur->handler(effect, cur->a, cur->b) == 0) {
                break;
            }
            next = effect->step + 1;
            effect->step = next;
            step = next;
        } while (script_has_step(script, (u8)next));
        if (script_has_step(script, effect->step)) {
            return;
        }
    }
    *status = 2;
}
