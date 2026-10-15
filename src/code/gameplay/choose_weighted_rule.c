#include "types.h"

typedef struct RuleTerm {
    s32 id;
    f32 value;
} RuleTerm;

typedef struct Rule {
    s32 result;
    RuleTerm *conditions;
    RuleTerm *weights;
} Rule;

extern f32 func_800E9720(void *context, s32 id);

s32 choose_weighted_rule(void *context, Rule *rules) __asm__("func_800EA93C");

s32 choose_weighted_rule(void *context, Rule *rules)
{
    s32 eligible[5];
    u16 last = 0;
    u16 count = 0;
    u16 i;
    u16 k;
    u16 best;
    s32 found;
    RuleTerm *terms;
    RuleTerm *weights;
    f32 value;
    f32 score;
    f32 bestScore;

    for (i = 0; i < 5; i++) {
        Rule *rule = &rules[i];

        if (rule->result == 0) {
            break;
        }
        terms = rule->conditions;
        if (terms == 0) {
            eligible[i] = 1;
            count++;
            last = i;
        } else {
            for (k = 0; k < 0x58; k++) {
                RuleTerm *term = &terms[k];

                value = term->value;
                if (term->id == 0) {
                    eligible[i] = 1;
                    count++;
                    last = i;
                    break;
                }
                if (func_800E9720(context, term->id) < value) {
                    eligible[i] = 0;
                    break;
                }
            }
        }
    }
    if (count == 0) {
        return -1;
    }
    if (count == 1) {
        return rules[last].result;
    }
    best = 0;
    bestScore = 0.0f;
    found = 0;
    for (i = 0; i < last; i++) {
        if (eligible[i]) {
            Rule *rule = &rules[i];

            if (rule->result == 0) {
                break;
            }
            weights = rule->weights;
            score = 0.0f;
            if (weights == 0) {
                if (!found || bestScore < score) {
                    best = i;
                    bestScore = score;
                    found = 1;
                }
            } else {
                for (k = 0; k < 0x58; k++) {
                    RuleTerm *term = &weights[k];

                    value = term->value;
                    if (term->id == 0) {
                        if (!found || bestScore < score) {
                            best = i;
                            bestScore = score;
                            found = 1;
                        }
                        break;
                    }
                    score += func_800E9720(context, term->id) * value;
                }
            }
        }
    }
    if (found) {
        return rules[best].result;
    }
    return -1;
}
