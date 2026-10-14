.set noreorder
.set noat
.text

.globl osWritebackDCache
.ent osWritebackDCache
osWritebackDCache:
    blez    $a1, 2f
     nop
    addiu   $t3, $zero, 0x2000
    sltu    $at, $a1, $t3
    beqz    $at, 3f
     nop
    or      $t0, $a0, $zero
    addu    $t1, $a0, $a1
    sltu    $at, $t0, $t1
    beqz    $at, 2f
     nop
    andi    $t2, $t0, 0xF
    beqz    $t2, 1f
     addiu  $t1, $t1, -0x10
    subu    $t0, $t0, $t2
    cache   0x15, 0($t0)
    sltu    $at, $t0, $t1
    beqz    $at, 2f
     nop
    addiu   $t0, $t0, 0x10
1:
    andi    $t2, $t1, 0xF
    beqz    $t2, 4f
     nop
    subu    $t1, $t1, $t2
    cache   0x15, 0x10($t1)
    sltu    $at, $t1, $t0
    bnez    $at, 2f
     nop
4:
    cache   0x11, 0($t0)
    sltu    $at, $t0, $t1
    bnez    $at, 4b
     addiu  $t0, $t0, 0x10
2:
    jr      $ra
     nop
3:
    lui     $t0, 0x8000
    addu    $t1, $t0, $t3
    addiu   $t1, $t1, -0x10
5:
    cache   0x01, 0($t0)
    sltu    $at, $t0, $t1
    bnez    $at, 5b
     addiu  $t0, $t0, 0x10
    jr      $ra
     nop
.end osWritebackDCache
