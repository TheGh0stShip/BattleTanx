#include "types.h"

/* Layout of libultra's OSPfsState. */
typedef struct PakFileState {
    u32 fileSize;
    u32 gameCode;
    u16 companyCode;
    u8 extName[4];
    u8 gameName[16];
} PakFileState;

typedef struct PakFilesystem {
    u8 bytes[0x68];
} PakFilesystem;

#define PAK_FILE_SLOTS 16
#define PAK_SAVE_SIZE 0x100
#define PAK_READ 0
#define PAK_WRITE 1
#define PAK_ERR_INVALID 5
#define PAK_ERR_DEVICE 10
#define PAK_STATUS_RUMBLE 1
#define PAK_STATUS_NEW_PACK 2
#define PAK_ERR_CHECKSUM (-0x45)
#define PAK_ERR_VERIFY (-0x63)

extern s32 gControllerCount __asm__("D_80126714");
extern s32 gControllerPakChannels[] __asm__("D_802DF550");
extern s32 gPakDefaultStatus __asm__("D_80126710");
extern u8 gPakSaveName[16] __asm__("D_80126718");
extern u8 gPakToAscii[] __asm__("D_80126724");
extern u8 gPakExtName[4] __asm__("D_80126728");
extern u16 gPakCompanyCode __asm__("D_8012672C");
extern u32 gPakGameCode __asm__("D_80126730");
extern u8 gSerialQueue[] __asm__("D_802DF360");
extern PakFilesystem gPakFilesystems[4] __asm__("D_802DF3A0");
extern u8 gPakLockQueue[] __asm__("D_802DF5B0");
extern void *gPakLockMessage __asm__("D_802E17A0");

extern s32 osRecvMesg(void *queue, void **message, s32 flags) __asm__("func_80119240");
extern s32 osSendMesg(void *queue, void *message, s32 flags) __asm__("func_801193E0");
extern s32 osPfsInitPak(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80116C70");
extern s32 osMotorInit(void *queue, PakFilesystem *pfs, s32 channel) __asm__("func_80113C40");
extern s32 osPfsFileState(PakFilesystem *pfs, s32 fileNo, PakFileState *state) __asm__("func_80116720");
extern s32 osPfsAllocateFile(PakFilesystem *pfs, u16 companyCode, u32 gameCode, u8 *gameName, u8 *extName,
                             s32 length, s32 *fileNo) __asm__("func_80114C00");
extern s32 osPfsDeleteFile(PakFilesystem *pfs, u16 companyCode, u32 gameCode, u8 *gameName, u8 *extName)
    __asm__("func_80116110");
extern s32 osPfsReadWriteFile(PakFilesystem *pfs, s32 fileNo, u8 flag, s32 offset, s32 size, u32 *buffer)
    __asm__("func_80117DAC");
extern s32 osPfsRepairId(PakFilesystem *pfs) __asm__("func_801181B0");
extern u32 compute_pak_save_checksum(u32 *buffer) __asm__("func_800A9B44");

s32 find_first_controller_pak(void) __asm__("func_800A942C");
s32 init_controller_pak(s32 channel) __asm__("func_800A9484");
void pak_name_to_ascii(u8 *dest, u8 *source) __asm__("func_800A9564");
s32 read_controller_pak_files(s32 channel, PakFileState *states, s32 *count) __asm__("func_800A95C0");
s32 allocate_controller_pak_save(s32 channel, s32 *fileNo) __asm__("func_800A96CC");
s32 delete_controller_pak_file(s32 channel, PakFileState *state) __asm__("func_800A979C");
s32 read_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer) __asm__("func_800A9850");
s32 write_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer) __asm__("func_800A9920");
s32 repair_controller_pak(s32 channel) __asm__("func_800A9AB0");

s32 find_first_controller_pak(void)
{
    s32 found;
    s32 i;

    found = 0;
    for (i = 0; i < gControllerCount; i++) {
        if (gControllerPakChannels[i] != -1) {
            found = gControllerPakChannels[i] + 1;
            break;
        }
    }
    return found;
}

s32 init_controller_pak(s32 channel)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsInitPak(gSerialQueue, &gPakFilesystems[channel], channel);
    if (status == PAK_ERR_DEVICE && osMotorInit(gSerialQueue, &gPakFilesystems[channel], channel) == 0) {
        status = PAK_STATUS_RUMBLE;
    }
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    if (status == PAK_STATUS_NEW_PACK) {
        gPakDefaultStatus = status;
    }
    return status;
}

void pak_name_to_ascii(u8 *dest, u8 *source)
{
    u8 c;
    u8 out;

    c = *source;
    while (c != 0) {
        source++;
        out = ' ';
        if (c >= 0x42 && c <= 0x94) {
            out = '*';
        } else if (c >= 0x10 && c <= 0x42) {
            out = gPakToAscii[c];
        }
        *dest = out;
        c = *source;
        dest++;
    }
    *dest = 0;
}

s32 read_controller_pak_files(s32 channel, PakFileState *states, s32 *count)
{
    s32 status;
    s32 i;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    *count = 0;
    for (i = 0; i < PAK_FILE_SLOTS; i++) {
        status = osPfsFileState(&gPakFilesystems[channel], i, &states[i]);
        if (status == 0) {
            (*count)++;
        } else if (status == PAK_ERR_INVALID) {
            status = 0;
            states[i].fileSize = 0;
            states[i].gameName[0] = 0;
        } else {
            break;
        }
    }
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}

s32 allocate_controller_pak_save(s32 channel, s32 *fileNo)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsAllocateFile(&gPakFilesystems[channel], gPakCompanyCode, gPakGameCode, gPakSaveName,
                               gPakExtName, PAK_SAVE_SIZE, fileNo);
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}

s32 delete_controller_pak_file(s32 channel, PakFileState *state)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsDeleteFile(&gPakFilesystems[channel], state->companyCode, state->gameCode, state->gameName,
                             state->extName);
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}

inline s32 read_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsReadWriteFile(&gPakFilesystems[channel], fileNo, PAK_READ, 0, PAK_SAVE_SIZE, buffer);
    if (status == 0 && compute_pak_save_checksum(buffer) != *buffer) {
        status = PAK_ERR_CHECKSUM;
    }
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}

s32 write_controller_pak_save(s32 channel, s32 fileNo, u32 *buffer)
{
    s32 status;
    u32 checksum;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    checksum = compute_pak_save_checksum(buffer);
    *buffer = checksum;
    status = osPfsReadWriteFile(&gPakFilesystems[channel - 1], fileNo, PAK_WRITE, 0, PAK_SAVE_SIZE, buffer);
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    if (status == 0) {
        status = read_controller_pak_save(channel, fileNo, buffer);
        if (status == 0 && compute_pak_save_checksum(buffer) != checksum) {
            status = PAK_ERR_VERIFY;
        }
    }
    return status;
}

s32 repair_controller_pak(s32 channel)
{
    s32 status;

    osRecvMesg(gPakLockQueue, &gPakLockMessage, 1);
    channel--;
    status = osPfsRepairId(&gPakFilesystems[channel]);
    osSendMesg(gPakLockQueue, &gPakLockMessage, 0);
    return status;
}
