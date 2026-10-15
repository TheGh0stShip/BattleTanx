.set noreorder
.set noat
.text
.globl install_exception_vectors
.ent install_exception_vectors
install_exception_vectors:
    addi    $29, $29, -8
    sw      $31, 0($29)
    lui     $8, 0x8007
    addiu   $8, $8, 0x70A0
    lui     $9, 0x8007
    addiu   $9, $9, 0x70B4
    lui     $10, 0x8000
    ori     $10, $10, 0x0180
    lui     $11, 0x8007
    addiu   $11, $11, 0x70B4
1:
    lw      $12, 0($10)
    lw      $13, 0($8)
    addiu   $8, $8, 4
    sw      $12, 0($9)
    addiu   $9, $9, 4
    sw      $13, 0($10)
    bne     $8, $11, 1b
     addiu  $10, $10, 4
    lui     $8, 0x8007
    addiu   $8, $8, 0x70D8
    lui     $9, 0x8007
    addiu   $9, $9, 0x70EC
    lui     $10, 0x8000
    lui     $11, 0x8007
    addiu   $11, $11, 0x70EC
2:
    lw      $12, 0($10)
    lw      $13, 0($8)
    addiu   $8, $8, 4
    sw      $12, 0($9)
    addiu   $9, $9, 4
    sw      $13, 0($10)
    bne     $8, $11, 2b
     addiu  $10, $10, 4
    .word   0x0C01DC6F
     nop
    .word   0x0C01DC76
     nop
    addiu   $8, $0, -0x802
    lui     $1, 0x8014
    sw      $8, 0x7388($1)
    lw      $31, 0($29)
    jr      $31
     addi   $29, $29, 8
.end install_exception_vectors
