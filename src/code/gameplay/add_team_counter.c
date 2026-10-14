#include "types.h"

typedef struct {
    u8 pad000[0x10];
    s32 state;
    u8 pad014[0x2];
    u16 id;
    u8 pad018[0x10];
    s32 counter;
    u8 pad02C[0x17A];
    u8 value1A6;
    u8 pad1A7[0x7];
    u8 team;
    u8 pad1AF[0x69];
    s32 messageColor;
    s32 messageExpireTick;
    char messageLine0[0x20];
    char messageLine1[0x20];
} CounterEntity;

extern CounterEntity *get_entity_record(u16 index) __asm__("func_800A6688");
extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 get_entity_capacity(void) __asm__("func_8007AAB0");
extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern s32 gGameTicks __asm__("D_801B4AA8");
extern char D_80072DFC[];
extern const char gStringFormat[] __asm__("D_80072DE8");

void add_team_counter(u16 index, s32 delta) __asm__("func_800A5B6C");

static inline void show_entity_message(CounterEntity *entity, char *text0, char *text1) {
    if (entity->value1A6 == 0) {
        entity->messageColor = 0x27;
        entity->messageExpireTick = gGameTicks + 0x5A;
        format_string(entity->messageLine0, gStringFormat, text0);
        format_string(entity->messageLine1, gStringFormat, text1);
    }
}

void add_team_counter(u16 index, s32 delta) {
    char line0[0x20];
    char line1[0x20];
    CounterEntity *entity;
    CounterEntity *other;
    s32 i;
    s32 count;

    entity = get_entity_record(index);
    entity->counter += delta;
    if (entity->counter < 0) {
        entity->counter = 0;
    }
    if (*get_game_mode() != 9) {
        return;
    }
    for (i = 0; i < get_entity_capacity(); i++) {
        if (i == entity->id) {
            continue;
        }
        other = get_entity_record(i);
        if (other->team != entity->team) {
            continue;
        }
        other->counter += delta;
        if (other->counter < 0) {
            other->counter = 0;
        }
        if (other->counter >= 7) {
            other->state = 2;
        }
    }
    count = entity->counter;
    if (count >= 7) {
        entity->state = 2;
        return;
    }
    format_string(line0, D_80072DFC, count, (count != 1) ? 'S' : ' ');
    line1[0] = 0;
    show_entity_message(entity, line0, line1);
}
