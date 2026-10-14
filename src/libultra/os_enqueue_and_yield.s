.set noreorder
.set noat
.text

.globl __osEnqueueAndYield
.ent __osEnqueueAndYield
__osEnqueueAndYield:
    lui     $a1, 0x8014
    lw      $a1, 0x6100($a1)
    mfc0    $t0, $12
    lw      $k1, 0x18($a1)
    ori     $t0, $t0, 2
    sw      $t0, 0x118($a1)
    sd      $s0, 0x98($a1)
    sd      $s1, 0xA0($a1)
    sd      $s2, 0xA8($a1)
    sd      $s3, 0xB0($a1)
    sd      $s4, 0xB8($a1)
    sd      $s5, 0xC0($a1)
    sd      $s6, 0xC8($a1)
    sd      $s7, 0xD0($a1)
    sd      $gp, 0xE8($a1)
    sd      $sp, 0xF0($a1)
    sd      $fp, 0xF8($a1)
    sd      $ra, 0x100($a1)
    beqz    $k1, 1f
     sw     $ra, 0x11C($a1)
    cfc1    $k1, $31
    sdc1    $f20, 0x180($a1)
    sdc1    $f22, 0x188($a1)
    sdc1    $f24, 0x190($a1)
    sdc1    $f26, 0x198($a1)
    sdc1    $f28, 0x1A0($a1)
    sdc1    $f30, 0x1A8($a1)
    sw      $k1, 0x12C($a1)
1:
    lw      $k1, 0x118($a1)
    andi    $t1, $k1, 0xFF00
    beqz    $t1, 2f
     nop
    lui     $t0, 0x8014
    addiu   $t0, $t0, 0x5DB0
    lw      $t0, 0($t0)
    addiu   $at, $zero, -1
    xor     $t0, $t0, $at
    lui     $at, 0xFFFF
    andi    $t0, $t0, 0xFF00
    ori     $at, $at, 0x00FF
    or      $t1, $t1, $t0
    and     $k1, $k1, $at
    or      $k1, $k1, $t1
    sw      $k1, 0x118($a1)
2:
    lui     $k1, 0xA430
    lw      $k1, 0xC($k1)
    beqz    $k1, 3f
     nop
    lui     $k0, 0x8014
    addiu   $k0, $k0, 0x5DB0
    lw      $k0, 0($k0)
    lw      $t0, 0x128($a1)
    addiu   $at, $zero, -1
    srl     $k0, $k0, 16
    xor     $k0, $k0, $at
    andi    $k0, $k0, 0x3F
    and     $k0, $k0, $t0
    or      $k1, $k1, $k0
3:
    beqz    $a0, 4f
     sw     $k1, 0x128($a1)
    .word   0x0C04476F
     nop
4:
    .word   0x08044785
     nop
.end __osEnqueueAndYield
