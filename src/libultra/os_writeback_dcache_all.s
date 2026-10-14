.set noreorder
.set noat
.text

.globl osWritebackDCacheAll
.ent osWritebackDCacheAll
osWritebackDCacheAll:
    lui     $t0, 0x8000
    addiu   $t2, $zero, 0x2000
    addu    $t1, $t0, $t2
    addiu   $t1, $t1, -0x10
1:
    cache   0x01, 0($t0)
    sltu    $at, $t0, $t1
    bnez    $at, 1b
     addiu  $t0, $t0, 0x10
    jr      $ra
     nop
    .word   0
    .word   0
.end osWritebackDCacheAll
