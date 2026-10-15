.set noreorder
.set noat
.text

.globl osInvalICache
.ent osInvalICache
osInvalICache:
    blez    $5, 2f
     nop
    addiu   $11, $0, 0x4000
    sltu    $1, $5, $11
    beqz    $1, 3f
     nop
    or      $8, $4, $0
    addu    $9, $4, $5
    sltu    $1, $8, $9
    beqz    $1, 2f
     nop
    andi    $10, $8, 0x1F
    addiu   $9, $9, -0x20
    subu    $8, $8, $10
1:
    cache   0x10, 0($8)
    sltu    $1, $8, $9
    bnez    $1, 1b
     addiu  $8, $8, 0x20
2:
    jr      $31
     nop
3:
    lui     $8, 0x8000
    addu    $9, $8, $11
    addiu   $9, $9, -0x20
4:
    cache   0x00, 0($8)
    sltu    $1, $8, $9
    bnez    $1, 4b
     addiu  $8, $8, 0x20
    jr      $31
     nop
.end osInvalICache
