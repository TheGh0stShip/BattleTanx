#include "types.h"

typedef struct DisplayCommand {
    u32 w0;
    u32 w1;
} DisplayCommand;

extern DisplayCommand D_80125860[15];
extern DisplayCommand D_801258D8[15];

void rewrite_display_list_commands(DisplayCommand *commands, s32 count) __asm__("func_80085330");

void rewrite_display_list_commands(DisplayCommand *commands, s32 count)
{
    s32 *var_a1;
    s32 *var_a2;
    s32 temp_t1;
    s32 var_t0;
    DisplayCommand *var_a0;
    DisplayCommand *var_a3;
    DisplayCommand *baseSource;
    DisplayCommand *baseReplacement;
    s32 magic;
    s32 replacement0;
    s32 replacement1;

    var_a0 = commands;
    if (count > 0) {
        magic = (u32)0xB8 << 24;
        baseSource = D_80125860;
        baseReplacement = D_801258D8;
        temp_t1 = (count << 3) + (u32)var_a0;
loop:
        if (var_a0->w0 != magic) {
            var_t0 = 0;
            var_a3 = var_a0;
            var_a2 = (s32 *)baseReplacement;
            var_a1 = (s32 *)baseSource;
            do {
                if (((DisplayCommand *)var_a1)->w0 == var_a3->w0 &&
                    ((DisplayCommand *)var_a1)->w1 == var_a3->w1) {
                    replacement0 = ((DisplayCommand *)var_a2)->w0;
                    replacement1 = ((DisplayCommand *)var_a2)->w1;
                    var_a3->w0 = replacement0;
                    var_a3->w1 = replacement1;
                }
                var_a2 = (s32 *)((DisplayCommand *)var_a2 + 1);
                var_t0++;
                var_a1 = (s32 *)((DisplayCommand *)var_a1 + 1);
            } while (var_t0 < 15);
            var_a0++;
            if ((s32)var_a0 < temp_t1) {
                goto loop;
            }
        }
    }
}
