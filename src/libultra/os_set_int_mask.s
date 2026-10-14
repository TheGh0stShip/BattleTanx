.set noreorder
.set noat
.text

.globl osSetIntMask
.ent osSetIntMask
osSetIntMask:
    mfc0    $t4, $12
    andi    $v0, $t4, 0xFF01
    lui     $t0, 0x8014
    addiu   $t0, $t0, 0x5DB0
    lw      $t3, 0($t0)
    addiu   $at, $zero, -1
    xor     $t0, $t3, $at
    andi    $t0, $t0, 0xFF00
    or      $v0, $v0, $t0
    lui     $t2, 0xA430
    lw      $t2, 0xC($t2)
    beqz    $t2, 1f
     srl    $t1, $t3, 16
    addiu   $at, $zero, -1
    xor     $t1, $t1, $at
    andi    $t1, $t1, 0x3F
    or      $t2, $t2, $t1
1:
    sll     $t2, $t2, 16
    or      $v0, $v0, $t2
    lui     $at, 0x003F
    and     $t0, $a0, $at
    and     $t0, $t0, $t3
    srl     $t0, $t0, 15
    lui     $t2, 0x8007
    addu    $t2, $t2, $t0
    lhu     $t2, 0x5C90($t2)
    lui     $at, 0xA430
    sw      $t2, 0xC($at)
    andi    $t0, $a0, 0xFF01
    andi    $t1, $t3, 0xFF00
    and     $t0, $t0, $t1
    lui     $at, 0xFFFF
    ori     $at, $at, 0x00FF
    and     $t4, $t4, $at
    or      $t4, $t4, $t0
    mtc0    $t4, $12
    nop
    nop
    jr      $ra
     nop
.end osSetIntMask
