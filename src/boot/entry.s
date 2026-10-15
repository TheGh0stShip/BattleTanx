.set noreorder
.set noat
.text
.globl entrypoint
.ent entrypoint
entrypoint:
    lui     $29, 0x8015
    addiu   $29, $29, -0x1F38
    lui     $8, 0x8014
    addiu   $8, $8, 0x7040
    lui     $9, 0x803D
    addiu   $9, $9, -0x7780
    beq     $8, $9, 2f
     nop
1:
    addiu   $8, $8, 4
    sltu    $1, $8, $9
    bnez    $1, 1b
     sw     $0, -4($8)
2:
    .word   0x0C01DE73
     nop
    .word   0x0001008D
.end entrypoint
