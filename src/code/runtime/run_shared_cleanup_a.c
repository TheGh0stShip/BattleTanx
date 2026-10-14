#include "types.h"

extern void func_8008B89C(void);

void run_shared_cleanup_a(void) __asm__("func_8010DD94");

void run_shared_cleanup_a(void)
{
    func_8008B89C();
}
