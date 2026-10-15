#include "types.h"

typedef struct TeamTuning {
    u8 pad000[0x310];
    f32 offense;
    f32 defense;
    f32 gunResurrection;
    f32 aiSpeedFactor;
    f32 aiFireRate;
    f32 railFireRate;
    f32 offRailFireRate;
    f32 railSpeedFactor;
    f32 aggressiveness;
    f32 intelligence;
    s16 gunDamage[4];
    s16 gunFireRate[4];
} TeamTuning;

typedef struct GameStateRecord {
    u8 pad000[0x4];
    u32 level;
    u8 pad008[0x1C8];
    s32 teamCount;
} GameStateRecord;

extern s32 debug_port_command_202(char *path, s32 mode) __asm__("func_80076D14");
extern s32 debug_port_command_303(char *path, s32 mode, s32 flags) __asm__("func_80076DA4");
extern s32 debug_port_command_404(s32 handle) __asm__("func_80076E34");
extern s32 debug_port_command_707(s32 handle, s32 offset, s32 whence) __asm__("func_80077028");
extern s32 debug_port_send_data(s32 handle, char *source, s32 length) __asm__("func_80076F60");
extern const char *get_level_name(u32 level) __asm__("func_800863F4");
extern s32 format_string(char *out, const char *format, ...) __asm__("func_8011CC84");
extern s32 string_length(const char *s) __asm__("func_8011D3DC");
extern TeamTuning *get_entity_record(u16 index) __asm__("func_800A6688");
extern GameStateRecord *gCurrentGameState __asm__("D_801B4ABC");
extern s32 gControllerSlotCount __asm__("D_80134E58");
extern s32 D_80134E5C;

#define WRITE_LINE(handle, buffer) debug_port_send_data(handle, buffer, string_length(buffer))

s32 write_team_tuning_report(char *path, s32 append) __asm__("func_8007C864");

s32 write_team_tuning_report(char *path, s32 append) {
    char buffer[0x100];
    GameStateRecord *state = gCurrentGameState;
    TeamTuning *team;
    s32 handle;
    s32 i;
    s32 j;

    if (append) {
        handle = debug_port_command_303(path, 1, 0);
        debug_port_command_707(handle, 0, 2);
    } else {
        handle = debug_port_command_202(path, 1);
    }
    if (handle <= 0) {
        return 0;
    }
    format_string(buffer, "Level %s\r\n", get_level_name(state->level));
    WRITE_LINE(handle, buffer);
    if (gControllerSlotCount == 1 && D_80134E5C == 0) {
        format_string(buffer, "Campaign\r\n");
    } else {
        format_string(buffer, "MultiPlayer\r\n");
    }
    WRITE_LINE(handle, buffer);
    for (i = 0; i < state->teamCount; i++) {
        team = get_entity_record(i);
        format_string(buffer, "\r\nTeam %d\r\n", i + 1);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "Aggressiveness = %f\r\n", team->aggressiveness);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "Intelligence = %f\r\n", team->intelligence);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "Offense = %f\r\n", team->offense);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "Defense = %f\r\n", team->defense);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "ai speed factor = %f\r\n", team->aiSpeedFactor);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "ai fire rate = %f\r\n", team->aiFireRate);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "goliath fire rate on rails = %f\r\n", team->railFireRate);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "goliath fire rate off rails = %f\r\n", team->offRailFireRate);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "goliath speed factor on rails = %f\r\n", team->railSpeedFactor);
        WRITE_LINE(handle, buffer);
        format_string(buffer, "Gun Resurrection = %f\r\n", team->gunResurrection);
        WRITE_LINE(handle, buffer);
        for (j = 0; j < 4; j++) {
            format_string(buffer, "Gun %d Fire Rate = %d\r\n", j + 1, team->gunFireRate[j]);
            WRITE_LINE(handle, buffer);
        }
        for (j = 0; j < 4; j++) {
            format_string(buffer, "Gun %d Damage = %d\r\n", j + 1, team->gunDamage[j]);
            WRITE_LINE(handle, buffer);
        }
    }
    format_string(buffer, "\r\n\r\n");
    WRITE_LINE(handle, buffer);
    debug_port_command_404(handle);
    return 1;
}
