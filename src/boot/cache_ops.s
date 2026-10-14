.set noreorder
.text

.globl osWritebackDCacheAll
.ent osWritebackDCacheAll
osWritebackDCacheAll:
    lui     $t0, 0x8000
    addiu   $t1, $t0, 0x1ff0
1:
    cache   1, 0($t0)
    bne     $t0, $t1, 1b
     addiu  $t0, $t0, 0x10
    jr      $ra
     nop
.end osWritebackDCacheAll

.globl osInvalICache
.ent osInvalICache
osInvalICache:
    lui     $t0, 0x8000
    addiu   $t1, $t0, 0x3fe0
2:
    cache   0, 0($t0)
    bne     $t0, $t1, 2b
     addiu  $t0, $t0, 0x20
    jr      $ra
     nop
.end osInvalICache
