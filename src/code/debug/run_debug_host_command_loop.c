#include "types.h"

extern u32 debug_pi_read_word(u32 address) __asm__("func_800760A0");
extern void debug_pi_write_word(u32 address, u32 value) __asm__("func_80076068");
extern void debug_delay(s32 count) __asm__("func_800760DC");
extern u32 read_status_register(void) __asm__("func_800771F4");
extern void write_status_register(u32 value) __asm__("func_80077200");
extern void func_80076634(s32 mode);
extern void func_800767E4(void);
extern u32 D_801471C8;
extern u8 D_80147370;
extern u8 D_80147372;

void run_debug_host_command_loop(void) __asm__("func_800769B0");

void run_debug_host_command_loop(void) {
    u32 command;
    s32 keep;

    do {
        keep = 1;
        for (;;) {
            command = debug_pi_read_word(0xB1FFFFF0);
            if (command != 0) {
                break;
            }
            debug_delay(1000);
        }
        if (command == 2) {
            debug_pi_write_word(0xB1FFFFFC, 0);
            debug_delay(1000);
        } else {
            debug_pi_write_word(0xB1FFFFFC, 0x101);
            while (debug_pi_read_word(0xB1FFFFF0) == command) {
                debug_delay(500);
            }
            if (debug_pi_read_word(0xB1FFFFF0) == 2) {
                debug_pi_write_word(0xB1FFFFFC, 0);
            } else {
                switch (command) {
                case 16:
                    break;
                case 17:
                    keep = 0;
                    break;
                case 18:
                    D_80147370 = 0;
                    D_80147372 = 0;
                    D_801471C8 &= ~1;
                    write_status_register(read_status_register() & ~1);
                    break;
                case 19:
                    D_80147372 = 0;
                    D_80147370 = 0;
                    break;
                case 20:
                    D_80147372 = 0xFF;
                    break;
                case 21:
                    D_80147372 = 0;
                    break;
                case 22:
                    debug_pi_write_word(0xB1FE0000, (D_80147372 << 24) | (D_80147370 << 16));
                    break;
                case 23:
                    func_80076634(2);
                    break;
                case 24:
                    func_80076634(1);
                    break;
                case 25:
                    func_800767E4();
                    break;
                }
                debug_pi_write_word(0xB1FFFFFC, 0);
                while (debug_pi_read_word(0xB1FFFFF0) == 1) {
                    debug_delay(500);
                }
            }
        }
    } while (keep || D_80147372 == 0);
}
