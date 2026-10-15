.set noreorder
.set noat
.text
.globl __cmpdi2
.ent __cmpdi2
__cmpdi2:
    slt     $2, $4, $6
    beqz    $2, 1f
     slt    $2, $6, $4
    jr      $31
     addu   $2, $0, $0
1:
    beqz    $2, 2f
     sltu   $2, $5, $7
    jr      $31
     addiu  $2, $0, 2
2:
    bnez    $2, 3f
     addu   $2, $0, $0
    sltu    $3, $7, $5
    bnez    $3, 3f
     addiu  $2, $0, 2
    jr      $31
     addiu  $2, $0, 1
3:
    jr      $31
     nop
.end __cmpdi2
