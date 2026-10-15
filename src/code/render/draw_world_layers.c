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
    f32 m[4][4];
    s32 flag;
} PlayerView;

typedef struct ViewOwner {
    u8 pad00[0x48];
    f32 m[4][4];
} ViewOwner;

typedef struct ViewEntity {
    u8 pad000[0xFC];
    u16 perspNorm;
    u8 pad0FE[2];
    f32 m[4][4];
} ViewEntity;

extern DrawGroup *D_801C0840[][32];
extern PlayerView gPlayerViews[4] __asm__("D_801C8F40");
extern u16 gPlayerPerspNorms[4] __asm__("D_801C9050");
extern s32 get_player_count(void) __asm__("func_8007AAA0");
extern void append_display_list_call_0(void *displayList) __asm__("func_8007EEF8");
extern void func_8007E8EC(PlayerView *view, u16 perspNorm);
extern void load_matrix_list_a(u32 address, s32 params) __asm__("func_8007EB64");
extern void append_display_commands(s32 count, void *src) __asm__("func_8007EF64");
extern void *func_800A42A4(void *entity);
extern ViewOwner *func_800A424C(ViewEntity *entity);
extern void matrix_multiply(f32 first[4][4], f32 second[4][4], f32 output[4][4]) __asm__("func_800A7F3C");
extern void *get_entity_record(u16 index) __asm__("func_800A6688");

static inline void draw_layer_groups_per_player(s32 layer, PlayerView *views, u16 *perspNorms)
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
    playerCount = get_player_count();
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

void draw_world_layers(void) __asm__("func_80080EEC");

void draw_world_layers(void)
{
    s32 count = get_player_count();
    ViewEntity *entity;
    s32 i;

    for (i = 0; i < count; i++) {
        entity = get_entity_record(i);
        matrix_multiply(func_800A424C(entity)->m, entity->m, gPlayerViews[i].m);
        gPlayerViews[i].flag = 0;
        gPlayerPerspNorms[i] = entity->perspNorm;
    }
    draw_layer_groups_per_player(0, gPlayerViews, gPlayerPerspNorms);
    draw_layer_groups_per_player(6, gPlayerViews, gPlayerPerspNorms);
    draw_layer_groups_per_player(5, gPlayerViews, gPlayerPerspNorms);
    draw_layer_groups_per_player(1, gPlayerViews, gPlayerPerspNorms);
    draw_layer_groups_per_player(2, gPlayerViews, gPlayerPerspNorms);
    draw_layer_groups_per_player(3, gPlayerViews, gPlayerPerspNorms);
}
