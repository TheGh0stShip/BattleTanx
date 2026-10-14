#include "types.h"

typedef struct {
    u8 pad000[0x34];
    s32 value034;
    u8 pad038[0x2];
    u16 value03A;
    u8 pad03C[0x1A6 - 0x3C];
    u8 value1A6;
    u8 pad1A7[0x218 - 0x1A7];
    s32 noticeKind;
    s32 noticeExpireTick;
    char noticeLine0[0x20];
    char noticeLine1[0x20];
} EntityProgress;

extern s32 *get_game_mode(void) __asm__("func_8007AAF4");
extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern const char gStringFormat[] __asm__("D_80072DE8");
extern const char gKillCountFormat[] __asm__("D_80072E08");
extern const char gPointsFormat[] __asm__("D_80072E14");
extern s32 gFrameCounter __asm__("D_801B4AA8");

static inline void set_notice_lines(EntityProgress *entity, char *text0, char *text1, s32 ticks) {
    if (entity->value1A6 == 0) {
        entity->noticeKind = 0x27;
        entity->noticeExpireTick = gFrameCounter + ticks;
        format_string(entity->noticeLine0, gStringFormat, text0);
        format_string(entity->noticeLine1, gStringFormat, text1);
    }
}

void handle_entity_progress_threshold(EntityProgress *entity, s32 threshold) __asm__("func_800A5DD8");

void handle_entity_progress_threshold(EntityProgress *entity, s32 threshold) {
    char killText[0x20];
    char pointsText[0x20];

    if (entity->value1A6 != 0) {
        return;
    }
    entity->value034++;
    if (*get_game_mode() != 7) {
        entity->value03A++;
    }
    if (threshold == 0) {
        return;
    }
    /* "%d KILL%c" and "%d POINTS" are passed fewer arguments than they consume. */
    format_string(killText, gKillCountFormat, threshold);
    format_string(pointsText, gPointsFormat);
    set_notice_lines(entity, killText, pointsText, 90);
}
