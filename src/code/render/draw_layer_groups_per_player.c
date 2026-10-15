#include "types.h"

typedef struct DrawItem DrawItem;

struct DrawItem {
    void *displayList;
    u32 matrixAddress;
    void *commands;
    DrawItem *next;
};

typedef struct DrawGroup DrawGroup;

struct DrawGroup {
    void *displayList;
    DrawItem *perPlayer[4];
    DrawGroup *next;
};

typedef struct PlayerView {
    u8 data[0x44];
} PlayerView;

extern DrawGroup *D_801C0840[][32];
extern s32 get_difficulty_level(void) __asm__("func_8007AAA0");
extern void append_display_list_call_0(void *displayList) __asm__("func_8007EEF8");
extern void func_8007E8EC(PlayerView *view, u16 perspNorm);
extern void load_matrix_list_a(u32 address, s32 params) __asm__("func_8007EB64");
extern void append_display_commands(s32 count, void *src) __asm__("func_8007EF64");
extern void *func_800A42A4(void *entity);
extern void *get_entity_record(u16 index) __asm__("func_800A6688");

void draw_layer_groups_per_player(s32 layer, PlayerView *views, u16 *perspNorms) __asm__("func_80080AA8");

void draw_layer_groups_per_player(s32 layer, PlayerView *views, u16 *perspNorms)
{
    s32 lastPlayer;
    u32 lastMatrix;
    s32 playerCount;
    s32 bucketIndex;
    DrawGroup *group;
    DrawItem *item;
    void *lastCommands;
    s32 player;

    lastPlayer = -1;
    lastMatrix = 0;
    playerCount = get_difficulty_level();
    for (bucketIndex = 0; bucketIndex < 32; bucketIndex++) {
        for (group = D_801C0840[layer][bucketIndex]; group != 0; group = group->next) {
            lastCommands = 0;
            append_display_list_call_0(group->displayList);
            for (player = 0; player < playerCount; player++) {
                for (item = group->perPlayer[player]; item != 0; item = item->next) {
                    if (player != lastPlayer) {
                        append_display_list_call_0(func_800A42A4(get_entity_record(player)));
                        lastPlayer = player;
                        func_8007E8EC(&views[player], perspNorms[player]);
                    }
                    if (item->matrixAddress != lastMatrix) {
                        load_matrix_list_a(item->matrixAddress, 2);
                        lastMatrix = item->matrixAddress;
                    }
                    if (item->commands != lastCommands && item->commands != 0) {
                        append_display_commands(1, item->commands);
                        lastCommands = item->commands;
                    }
                    append_display_list_call_0(item->displayList);
                }
            }
        }
    }
}
