#include "types.h"

typedef struct PakNote {
    u32 size;
    u8 pad04[0x6];
    u8 extension[0x4];
    u8 name[0x12];
} PakNote;

extern PakNote D_80327F50[16];
extern s32 D_80328150;
extern s32 D_8032815C;
extern s32 D_80328160;
extern s32 D_80328164;
extern s32 D_80328168;
extern s32 D_8032816C;
extern s32 D_80328170;
extern u8 D_80328180[];
extern u32 D_80134E70;
extern u8 D_80134E74;
extern s32 D_80126710;

extern s32 read_menu_buttons(s32 arg0, s32 arg1) __asm__("func_80096920");
extern s32 func_800A942C(void);
extern s32 func_800A9484(s32 pak);
extern s32 func_800A95C0(s32 pak, PakNote *notes, s32 *count);
extern s32 func_800A9B70(s32 pak, s32 *freeBytes);
extern void func_800A9AB0(s32 pak);
extern void scroll_pak_note_list(u8 buttons) __asm__("func_800D0CB4");
extern s32 func_800A979C(s32 pak, PakNote *note);
extern s32 func_800A96CC(s32 pak, s32 *note);
extern s32 func_800A9920(s32 pak, s32 note, u8 *buffer);
extern void func_800A90E0(void);
extern void func_800D0690(void);

static inline void refresh_pak_core(void)
{
    D_8032815C = func_800A942C();
    if (D_8032815C != 0) {
        D_80328160 = func_800A9484(D_8032815C);
        if (D_80328160 == 2 || D_80328160 == 0) {
            D_80328160 = func_800A95C0(D_8032815C, D_80327F50, &D_80328168);
            if (D_80328160 == 0) {
                D_80328160 = func_800A9B70(D_8032815C, &D_80328164);
            }
        }
    } else {
        D_80328160 = 0;
    }
}

static inline void refresh_pak_status(void)
{
    refresh_pak_core();
    if (D_80328160 == 0) {
        D_80328160 = D_80126710;
    }
}

s32 poll_controller_pak_screen(void) __asm__("func_800CF4C0");

s32 poll_controller_pak_screen(void)
{
    s32 result = 0;
    s32 buttons;

    buttons = read_menu_buttons(0, 0);
    if ((u8)buttons != 0) {
        D_80134E70 = 1;
    }
    switch (D_80328170) {
    case 8:
        if (buttons & 0x20) {
            result = 4;
        } else if (buttons & 0x10) {
            refresh_pak_status();
            result = 5;
        }
        break;
    case 9:
        if (buttons & 0x20) {
            D_80134E74 = 0;
            result = 4;
        } else if (buttons & 0x10) {
            func_800A9AB0(D_8032815C);
            refresh_pak_status();
            result = 5;
        }
        break;
    case 10:
        scroll_pak_note_list(buttons);
        if (buttons & 0x20) {
            result = 4;
            D_80134E74 = 0;
        } else if (buttons & 0x10) {
            refresh_pak_status();
            D_80126710 = 0;
            result = 5;
        }
        break;
    case 11:
        if (buttons & 0x20) {
            result = 4;
        } else if (buttons & 0x10) {
            refresh_pak_status();
            result = 5;
        }
        break;
    case 0:
        scroll_pak_note_list(buttons);
        if (buttons & 0x20) {
            result = 4;
        } else if (buttons & 0x10) {
            if (D_80327F50[D_80328150].size != 0 && D_80327F50[D_80328150].name[0] != 0) {
                D_80328170 = 4;
            }
        }
        break;
    case 4:
        if (buttons & 0x20) {
            D_80328170 = 0;
        } else if (buttons & 0x10) {
            D_80328160 = func_800A979C(D_8032815C, &D_80327F50[D_80328150]);
            if (D_80328160 != 0) {
                result = 5;
            } else {
                D_80328170 = 0;
                refresh_pak_status();
            }
        }
        break;
    case 1:
        scroll_pak_note_list(buttons);
        if (buttons & 0x20) {
            D_80134E74 = 0;
            result = 4;
        } else if (buttons & 0x10) {
            if (D_80327F50[D_80328150].size != 0 && D_80327F50[D_80328150].name[0] != 0) {
                D_80328170 = 5;
            }
        }
        break;
    case 5:
        if (buttons & 0x20) {
            D_80328170 = 1;
        } else if (buttons & 0x10) {
            D_80328160 = func_800A979C(D_8032815C, &D_80327F50[D_80328150]);
            if (D_80328160 != 0) {
                result = 5;
            } else {
                refresh_pak_status();
                result = 5;
            }
        }
        break;
    case 6:
        scroll_pak_note_list(buttons);
        if (buttons & 0x20) {
            D_80134E74 = 0;
            result = 4;
        } else if (buttons & 0x10) {
            D_80328160 = func_800A96CC(D_8032815C, &D_8032816C);
            if (D_80328160 == 0) {
                D_80328160 = func_800A9920(D_8032815C, D_8032816C, D_80328180);
                if (D_80328160 == 0) {
                    result = 2;
                    refresh_pak_status();
                    if (D_80328160 == 0) {
                        break;
                    }
                }
            }
            D_80134E74 = 0;
            result = 5;
        }
        break;
    case 3:
        if (buttons & 0x10) {
            func_800A90E0();
            refresh_pak_status();
            if (D_8032815C != 0) {
                D_80134E74 = 1;
                result = 5;
            }
        } else if (buttons & 0x20) {
            D_80134E74 = 0;
            result = 4;
        }
        break;
    case 7:
        if (buttons & 0x10) {
            result = 5;
            func_800D0690();
            if (D_80328160 == 0) {
                result = 3;
            }
        }
        if (buttons & 0x20) {
            result = 3;
        }
        break;
    case 2:
        if (buttons & 0x10) {
            func_800A90E0();
            refresh_pak_status();
            if (D_8032815C != 0) {
                D_80134E74 = 1;
                result = 5;
            }
        } else if (buttons & 0x20) {
            result = 4;
            D_80134E74 = 0;
        }
        break;
    }
    return result;
}
