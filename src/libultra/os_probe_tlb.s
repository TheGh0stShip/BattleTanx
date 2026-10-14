.set noreorder
.set noat
.text

.globl __osProbeTLB
.ent __osProbeTLB
__osProbeTLB:
    mfc0    $t0, $10
    andi    $t1, $t0, 0xFF
    addiu   $at, $zero, -0x2000
    and     $t2, $a0, $at
    or      $t1, $t1, $t2
    mtc0    $t1, $10
    nop
    nop
    nop
    tlbp
    nop
    nop
    mfc0    $t3, $0
    lui     $at, 0x8000
    and     $t3, $t3, $at
    bnez    $t3, 3f
     nop
    tlbr
    nop
    nop
    nop
    mfc0    $t3, $5
    addi    $t3, $t3, 0x2000
    srl     $t3, $t3, 1
    and     $t4, $t3, $a0
    bnez    $t4, 1f
     addi   $t3, $t3, -1
    mfc0    $v0, $2
    b       2f
     nop
1:
    mfc0    $v0, $3
2:
    andi    $t5, $v0, 2
    beqz    $t5, 3f
     nop
    lui     $at, 0x3FFF
    ori     $at, $at, 0xFFC0
    and     $v0, $v0, $at
    sll     $v0, $v0, 6
    and     $t5, $a0, $t3
    add     $v0, $v0, $t5
    b       4f
     nop
3:
    addiu   $v0, $zero, -1
4:
    mtc0    $t0, $10
    jr      $ra
     nop
.end __osProbeTLB
