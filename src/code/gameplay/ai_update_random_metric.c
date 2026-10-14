#include "ai_play_stack.h"

typedef struct MetricSettings {
    u8 pad000[0x214];
    u8 value214;
    u8 value215;
    u8 value216;
} MetricSettings;

typedef struct MarkerEffect {
    u8 pad00[0x4];
    s32 value04;
} MarkerEffect;

typedef struct MetricMember {
    u8 pad000[0x4];
    u8 teamIndex;
    u8 pad005[0x1F];
    f32 x;
    u8 pad028[0x4];
    f32 z;
    u8 pad030[0x444];
    u32 lastMetric;
    u8 pad478[0x8];
    u16 metrics[0x3E];
    MarkerEffect *marker;
    s32 markerValue;
    s32 value504;
} MetricMember;

extern f32 D_800746E0;
extern f32 D_800746E4;

extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern MetricSettings *get_current_game_state(void) __asm__("func_8007AAF4");
extern f32 random_float_range(f32 range) __asm__("func_800F3880");
extern MarkerEffect *spawn_effect_kind_17(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) __asm__("func_800F2044");

void ai_update_random_metric(AiActionContext *context, u32 metric) __asm__("func_800E7168");

void ai_update_random_metric(AiActionContext *context, u32 metric) {
    f32 chance;
    s32 value;
    MetricMember *member;

    if (get_difficulty_level() >= 2) {
        return;
    }
    switch (context->paramCount) {
    case 0:
        switch (metric) {
        case 8:
            value = get_current_game_state()->value214;
            break;
        case 3:
            value = get_current_game_state()->value215;
            break;
        case 2:
            value = get_current_game_state()->value216;
            break;
        default:
            value = 0;
            break;
        }
        chance = value / D_800746E0;
        break;
    case 1:
        chance = context->params[0];
        break;
    default:
        chance = 0.0f;
        break;
    }
    if (random_float_range(D_800746E4) < chance) {
        if (metric != 8) {
            ((MetricMember *)context->member)->metrics[metric] += 4;
            ((MetricMember *)context->member)->lastMetric = metric;
        } else {
            member = context->member;
            if (member->marker == 0) {
                ((MetricMember *)context->member)->marker =
                    spawn_effect_kind_17(member->x, member->z, member->teamIndex, 100, member->value504);
                if (((MetricMember *)context->member)->marker != 0) {
                    ((MetricMember *)context->member)->markerValue =
                        ((MetricMember *)context->member)->marker->value04;
                }
            }
        }
    }
}
