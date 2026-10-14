.set noreorder
.set noat
.text

.globl __osEnqueueThread
.ent __osEnqueueThread
__osEnqueueThread:
    lw      $t8, 0($a0)
    lw      $t7, 4($a1)
    or      $t9, $a0, $zero
    lw      $t6, 4($t8)
    slt     $at, $t6, $t7
    bnez    $at, 2f
     nop
1:
    or      $t9, $t8, $zero
    lw      $t8, 0($t8)
    lw      $t6, 4($t8)
    slt     $at, $t6, $t7
    beqz    $at, 1b
     nop
2:
    lw      $t8, 0($t9)
    sw      $t8, 0($a1)
    sw      $a1, 0($t9)
    jr      $ra
     sw     $a0, 8($a1)
.end __osEnqueueThread

.globl __osPopThread
.ent __osPopThread
__osPopThread:
    lw      $v0, 0($a0)
    lw      $t9, 0($v0)
    jr      $ra
     sw     $t9, 0($a0)
.end __osPopThread
