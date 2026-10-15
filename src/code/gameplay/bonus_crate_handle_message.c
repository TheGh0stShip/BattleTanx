#include "types.h"

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

typedef struct Player {
    u8 pad000[0x1AE];
    u8 team;
    u8 pad1AF[0x10];
    u8 effectSlot;
} Player;

typedef struct Sender {
    u8 pad00[0xC];
    u16 value0C;
    u8 pad0E[2];
    s32 damage;
    s32 area;
} Sender;

typedef struct Crate {
    u8 pad00[0xC];
    u8 flags;
    u8 team;
    u8 pad0E[2];
    s32 owner;
    u32 kind;
    u16 model;
    u8 pad1A[2];
    f32 z;
    f32 x;
    u8 pad24[8];
    u16 health;
    u8 pad2E[6];
    s32 claimTime;
    u16 claimValue;
} Crate;

typedef struct MessageHeader {
    u8 pad00[8];
    s32 type;
} MessageHeader;

extern void func_800ED8C0(Vec3f *pos, s32 mode);
extern Player *func_800A6688(u16 index);
extern void func_8008EF1C(Vec3f *pos, Vec3f *velocity, s32 arg2, s32 model, s32 arg4, f32 scale, s32 effect, s32 arg7, f32 size, s32 slot);
extern void func_800A59E8(Player *player, s32 score);
extern const Vec3f D_80072CCC;
extern s32 D_80125FB0[];
extern f32 D_80126038[];
extern s32 gGameTicks __asm__("D_801B4AA8");

void bonus_crate_handle_message(Crate *crate, MessageHeader *message, Sender *sender, s32 *result) __asm__("func_800A27D0");

void bonus_crate_handle_message(Crate *crate, MessageHeader *message, Sender *sender, s32 *result) {
    Player *player;

    switch (message->type) {
    case 2:
    case 12:
    case 22:
    case 34:
    case 44:
        *result = 0;
        crate->health -= sender->damage;
        if ((s16)crate->health <= 0 && !(crate->flags & 1)) {
            Vec3f pos;
            Vec3f velocity = D_80072CCC;

            pos.x = crate->x;
            pos.y = 0.0f;
            pos.z = crate->z;
            func_800ED8C0(&pos, 5);
            func_8008EF1C(&pos, &velocity, 0, crate->model, 0, 1.5f, D_80125FB0[crate->kind], 1,
                          D_80126038[crate->kind], func_800A6688(crate->owner)->effectSlot);
            crate->flags |= 1;
            player = func_800A6688(sender->area);
            if (player->team != crate->team) {
                switch (crate->kind) {
                case 0:
                    func_800A59E8(player, 100);
                    break;
                case 1:
                    func_800A59E8(player, 500);
                    break;
                case 2:
                    func_800A59E8(player, 1000);
                    break;
                case 3:
                    func_800A59E8(player, 2500);
                    break;
                }
            }
        } else {
            switch (message->type) {
            case 2:
            case 12:
            case 34:
                if (sender->area != crate->owner && crate->claimTime == -1) {
                    crate->claimTime = gGameTicks;
                    crate->claimValue = sender->value0C + 0x8000;
                }
                break;
            }
        }
        break;
    case 6:
    case 37:
        *result = 1;
        break;
    default:
        *result = 0;
        break;
    }
}
