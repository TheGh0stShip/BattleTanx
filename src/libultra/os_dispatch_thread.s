.set noreorder
.set noat
.text
.globl __osDispatchThread
.ent __osDispatchThread
__osDispatchThread:
    lui     $4, %hi(D_801460F8)
    jal     __osPopThread
     addiu  $4, $4, %lo(D_801460F8)
    lui     $1, %hi(D_80146100)
    sw      $2, %lo(D_80146100)($1)
    addiu   $8, $0, 4
    sh      $8, 0x10($2)
    or      $26, $2, $0
    lui     $8, %hi(D_80145DB0)
    lw      $27, 0x118($26)
    addiu   $8, $8, %lo(D_80145DB0)
    lw      $8, 0($8)
    lui     $1, 0xFFFF
    andi    $9, $27, 0xFF00
    ori     $1, $1, 0x00FF
    andi    $8, $8, 0xFF00
    and     $9, $9, $8
    and     $27, $27, $1
    or      $27, $27, $9
    mtc0    $27, $12
    ld      $27, 0x108($26)
    ld      $1, 0x20($26)
    ld      $2, 0x28($26)
    mtlo    $27
    ld      $27, 0x110($26)
    ld      $3, 0x30($26)
    ld      $4, 0x38($26)
    ld      $5, 0x40($26)
    ld      $6, 0x48($26)
    ld      $7, 0x50($26)
    ld      $8, 0x58($26)
    ld      $9, 0x60($26)
    ld      $10, 0x68($26)
    ld      $11, 0x70($26)
    ld      $12, 0x78($26)
    ld      $13, 0x80($26)
    ld      $14, 0x88($26)
    ld      $15, 0x90($26)
    ld      $16, 0x98($26)
    ld      $17, 0xA0($26)
    ld      $18, 0xA8($26)
    ld      $19, 0xB0($26)
    ld      $20, 0xB8($26)
    ld      $21, 0xC0($26)
    ld      $22, 0xC8($26)
    ld      $23, 0xD0($26)
    ld      $24, 0xD8($26)
    ld      $25, 0xE0($26)
    ld      $28, 0xE8($26)
    mthi    $27
    ld      $29, 0xF0($26)
    ld      $30, 0xF8($26)
    ld      $31, 0x100($26)
    lw      $27, 0x11C($26)
    mtc0    $27, $14
    lw      $27, 0x18($26)
    beqz    $27, 1f
     nop
    lw      $27, 0x12C($26)
    ctc1    $27, $31
    ldc1    $f0, 0x130($26)
    ldc1    $f2, 0x138($26)
    ldc1    $f4, 0x140($26)
    ldc1    $f6, 0x148($26)
    ldc1    $f8, 0x150($26)
    ldc1    $f10, 0x158($26)
    ldc1    $f12, 0x160($26)
    ldc1    $f14, 0x168($26)
    ldc1    $f16, 0x170($26)
    ldc1    $f18, 0x178($26)
    ldc1    $f20, 0x180($26)
    ldc1    $f22, 0x188($26)
    ldc1    $f24, 0x190($26)
    ldc1    $f26, 0x198($26)
    ldc1    $f28, 0x1A0($26)
    ldc1    $f30, 0x1A8($26)
1:
    lw      $27, 0x128($26)
    lui     $26, %hi(D_80145DB0)
    addiu   $26, $26, %lo(D_80145DB0)
    lw      $26, 0($26)
    srl     $26, $26, 16
    and     $27, $27, $26
    sll     $27, $27, 1
    lui     $26, %hi(D_80075C90)
    addiu   $26, $26, %lo(D_80075C90)
    addu    $27, $27, $26
    lhu     $27, 0($27)
    lui     $26, 0xA430
    addiu   $26, $26, 0x000C
    sw      $27, 0($26)
    nop
    nop
    nop
    nop
    eret
.end __osDispatchThread
