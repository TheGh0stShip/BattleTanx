#include "types.h"

typedef struct RoundEntity {
    u8 pad00[0x48];
    u8 motion[0x20];
} RoundEntity;

extern s32 D_8012578C;

extern void reset_motion_accumulator(void *motion) __asm__("func_80078814");
extern void func_80085E18();
extern s32 func_800EC390();
extern RoundEntity *get_entity_record(u16 index) __asm__("func_800A6688");

void begin_player_round_mode_8(void) __asm__("func_8007C678");

void begin_player_round_mode_8(void)
{
    D_8012578C = 8;
    func_80085E18();
    if (func_800EC390() != 0) {
        reset_motion_accumulator(get_entity_record(0)->motion);
    }
}
