#include "types.h"


typedef struct PlayerInput {
    s8 stickX;
    s8 stickY;
    u8 pad02[0x2];
    u32 held;
    u32 pressed;
    u32 released;
} PlayerInput;

typedef struct SquadUnit {
    u8 pad000[0x14];
    u16 flags;
    u8 pad016[0x3FC - 0x16];
    f32 value3FC;
    f32 value400;
    u8 pad404[0x100];
    s32 value504;
} SquadUnit;

typedef struct Squad {
    u8 pad000[0x1D0];
    u32 selectMask;
    u8 pad1D4[0x30];
    u8 locked;
} Squad;

typedef struct AreaObject {
    u8 pad00[8];
    s32 kind;
} AreaObject;

typedef struct SegmentHit {
    AreaObject *object;
    f32 x;
    f32 pad08;
    f32 z;
    u8 pad10[8];
} SegmentHit;

typedef struct AreaResponse {
    s32 passable;
    s32 value04;
    s32 value08;
    s32 value0C;
} AreaResponse;

typedef struct AreaContact {
    f32 x;
    s32 y;
    f32 z;
    u16 angle;
    u8 pad0E[2];
    s32 value10;
    s32 player;
    u8 pad18[8];
} AreaContact;

typedef struct SelectCursor {
    u8 pad00[0xC];
    u8 state;
    u8 pad0D;
    u16 angle;
    f32 position[2];
    u8 player;
    u8 pad19[3];
    s32 startTick;
} SelectCursor;

typedef void (*AreaHandler)(AreaObject *object, void *source, s32 arg2, AreaContact *contact, AreaResponse *response);

typedef struct AreaHandlerEntry {
    s32 value00;
    AreaHandler handler;
    s32 value08;
} AreaHandlerEntry;
extern PlayerInput *read_player_controller(s32 player) __asm__("func_80096784");
extern Squad *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern SquadUnit *select_active_squad_unit(Squad *squad) __asm__("func_800A4500");
extern SquadUnit *select_squad_unit_for_mode(Squad *squad, u8 mode) __asm__("func_800A4374");
extern void func_800A4E40(Squad *squad, s32 value);
extern s32 func_80085D84(f32 x, f32 z);
extern s32 find_segment_hit(f32 *start, f32 *end, s32 mode, SegmentHit *hit, s32 arg4) __asm__("func_8010874C");
extern f32 sinf_u16(u16 angle) __asm__("func_800F3AE0");
extern f32 cosf_u16(u16 angle) __asm__("func_800F3B40");
extern AreaHandlerEntry D_802C3800[];
extern AreaResponse D_80071074;
extern s32 gGameMode __asm__("D_8012578C");
extern f32 gClockFrameScale __asm__("D_801257B0");
extern s32 gGameTicks __asm__("D_801B4AA8");
void update_select_cursor(SelectCursor *cursor, s32 *state) __asm__("func_800788EC");

void update_select_cursor(SelectCursor *cursor, s32 *state)
{
    f32 next[2];
    SegmentHit hit;
    AreaContact contact;
    AreaResponse response;
    PlayerInput *input;
    Squad *squad;
    SquadUnit *unit;
    s32 blocked;
    f32 speed;
    f32 step;
    switch (cursor->state) {
    case 0:
        if (gGameMode != 7) {
            cursor->angle += 0x200;
        }
        break;
    case 3:
        do {
            unit = (SquadUnit *)read_player_controller(cursor->player);
            squad = get_entity_record(cursor->player);
            if (((PlayerInput *)unit)->pressed & squad->selectMask) {
                if (get_game_mode()[0] == 2) {
                    unit = select_active_squad_unit(get_entity_record(cursor->player));
                } else {
                    unit = select_squad_unit_for_mode(get_entity_record(cursor->player), 2);
                }
                if (unit != 0) {
                    goto selected;
                }
            }
            if (!(cursor->startTick + 30 < gGameTicks)) {
                break;
            }
            if (get_game_mode()[0] == 2) {
                unit = select_active_squad_unit(get_entity_record(cursor->player));
            } else {
                unit = select_squad_unit_for_mode(get_entity_record(cursor->player), 0);
            }
            if (unit == 0) {
                break;
            }
        selected:
            if (squad->locked == 0 && !(unit->flags & 4)) {
                unit->value3FC = unit->value400;
            }
            func_800A4E40(get_entity_record(cursor->player), unit->value504);
            *state = 2;
        } while (0);
        break;
    case 2:
        blocked = 0;
        input = read_player_controller(cursor->player);
        cursor->angle -= (u16)(input->stickX * 10 * gClockFrameScale);
        speed = input->stickY * 0.6f * gClockFrameScale;
        next[1] = cursor->position[1] + speed * sinf_u16(cursor->angle);
        next[0] = cursor->position[0] + speed * cosf_u16(cursor->angle);
        if (!func_80085D84(next[1], next[0])) {
            break;
        }
        if (find_segment_hit(cursor->position, next, 1, &hit, -1)) {
            if ((u32)hit.object < 4) {
                blocked = 1;
            } else {
                response = D_80071074;
                contact.x = hit.x;
                contact.y = 0;
                contact.z = hit.z;
                contact.angle = cursor->angle;
                contact.value10 = 0;
                contact.player = cursor->player;
                if (D_802C3800[hit.object->kind].handler != 0) {
                    D_802C3800[hit.object->kind].handler(hit.object, cursor, 0, &contact, &response);
                }
                if (response.passable == 0) {
                    blocked = 1;
                }
            }
        }
        if (blocked) {
            step = sinf_u16(cursor->angle);
            cursor->position[1] = hit.x + (speed > 0.0f ? (step = -step) : step);
            step = cosf_u16(cursor->angle);
            cursor->position[0] = hit.z + (speed > 0.0f ? (step = -step) : step);
        } else {
            cursor->position[1] = next[1];
            cursor->position[0] = next[0];
        }
        break;
    }
}
