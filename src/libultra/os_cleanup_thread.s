.set noreorder
.set noat
.text

.globl __osCleanupThread
.ent __osCleanupThread
__osCleanupThread:
    .word   0x0C0447E8
     or     $a0, $zero, $zero
    nop
    nop
.end __osCleanupThread
