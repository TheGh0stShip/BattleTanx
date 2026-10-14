#include "types.h"

extern void func_8008B89C(void);

void run_shared_cleanup_b(void) __asm__("func_8010DDB4");

void run_shared_cleanup_b(void)
{
    func_8008B89C();
}
