/* LDSYM D_8012579D=0x8012579D */
/* LDSYM D_80126714=0x80126714 */
/* LDSYM D_80135034=0x80135034 */
/* LDSYM D_80327614=0x80327614 */
/* LDSYM D_80328290=0x80328290 */
/* LDSYM D_803282A0=0x803282A0 */
/* LDSYM D_803282A8=0x803282A8 */
/* LDSYM D_803283B8=0x803283B8 */
/* LDSYM func_80096768=0x80096768 */
/* LDSYM func_8009686C=0x8009686C */
/* LDSYM func_80096920=0x80096920 */
/* LDSYM func_800ABF40=0x800ABF40 */
/* LDSYM func_800D6274=0x800D6274 */
#include "types.h"

typedef struct SessionRecord {
    u32 words[17];
} SessionRecord;

typedef struct PlayerInput {
    s8 stickX;
    s8 stickY;
    u8 pad02[0x2];
    u32 held;
    u32 pressed;
    u32 released;
} PlayerInput;

extern s32 read_player_menu_directions(s32 player, s32 ignoreCButtons) __asm__("func_80096920");
extern PlayerInput *read_player_controller_raw(s32 player) __asm__("func_8009686C");
extern SessionRecord *get_entity_record_68(s32 index) __asm__("func_80096768");
extern void set_sound_38_value_19114(void) __asm__("func_800ABF40");
extern void assign_player_slot_value(s32 player, s32 n, u32 value) __asm__("func_800D6274");
extern s32 D_80327614;
extern s32 gControllerCount __asm__("D_80126714");
extern s32 D_80135034[];
extern s32 D_80328290[];
extern u8 D_803282A0[];
extern u8 D_803283B8[];
extern SessionRecord D_803282A8[];
extern u8 D_8012579D;

s32 update_player_slot_configuration(void) __asm__("func_800D64CC");

s32 update_player_slot_configuration(void) {
    s32 player;
    u32 buttons;
    u32 bits;
    s32 delta;
    u8 bit;
    u8 changed;
    u8 ready;
    SessionRecord *profile;
    s32 *row;
    u8 *selected;
    u8 *saved;

    if (D_80327614 != 0) {
        D_80327614 ^= read_player_menu_directions(0, 0) & 0x80;
        return 0;
    }
    changed = 0;
    ready = 1;
    selected = D_803282A0;
    saved = D_803283B8;
    row = D_80328290;
    profile = D_803282A8;
    for (player = 0; player < gControllerCount; player++) {
        if (*row < D_80135034[*saved]) {
            buttons = read_player_controller_raw(player)->pressed & 0xE03F;
            if (buttons != 0) {
                for (bits = buttons, bit = 1; !(bits & 1); bit++) {
                    bits >>= 1;
                }
                assign_player_slot_value(player, *row, 1 << (bit - 1));
                if (player == 0) {
                    D_8012579D = 1;
                }
            }
        }
        buttons = read_player_menu_directions(player, 1);
        changed |= buttons;
        if (*row >= 8) {
            D_80327614 ^= buttons & 0x80;
        }
        if ((buttons & 4) && *row == 9) {
            if (player == 0) {
                D_8012579D = 1;
            }
            *saved = *selected = (*selected + 1) % 4;
            *profile = *get_entity_record_68(*saved);
        }
        if ((buttons & 2) && *row == 9) {
            if (player == 0) {
                D_8012579D = 1;
            }
            *saved = *selected = (*selected + 3) % 4;
            *profile = *get_entity_record_68(*saved);
        }
        if ((buttons & 0x10) && *row == 9) {
            if (player == 0) {
                D_8012579D = 1;
            }
            {
                u8 selection = *selected;
                *saved = selection;
                *profile = *get_entity_record_68(selection);
            }
        }
        delta = 0;
        if (buttons & 1) {
            set_sound_38_value_19114();
            delta = -1;
        }
        if (buttons & 8) {
            set_sound_38_value_19114();
            delta++;
        }
        *row += delta;
        if (*row < 0) {
            *row = 0;
        }
        if (*row > 10) {
            *row = 10;
        }
        if (*row != 10) {
            ready = 0;
        }
        if (*row != 9) {
            *selected = *saved;
        }
        selected++;
        saved++;
        row++;
        profile++;
    }
    {
        s32 result = 0;
        if (ready) {
            result = (changed & 0x30) != 0;
        }
        return result;
    }
}
