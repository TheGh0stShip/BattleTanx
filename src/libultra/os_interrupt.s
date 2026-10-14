.set noreorder
.set noat
.text

.globl __osGetSR
.ent __osGetSR
__osGetSR:
    mfc0    $v0, $12
    jr      $ra
     nop
.end __osGetSR

    .word   0

.globl __osDisableInt
.ent __osDisableInt
__osDisableInt:
    mfc0    $t0, $12
    addiu   $at, $zero, -2
    and     $t1, $t0, $at
    mtc0    $t1, $12
    andi    $v0, $t0, 1
    nop
    jr      $ra
     nop
.end __osDisableInt
