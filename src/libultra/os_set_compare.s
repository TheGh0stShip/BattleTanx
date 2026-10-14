/* libultra 2.0I os/setcompare.s (decompals/ultralib e24c836): __osSetCompare. */
.set noreorder
.set noat
.text

.globl __osSetCompare
.ent __osSetCompare
__osSetCompare:
    mtc0    $a0, $11
    jr      $ra
    nop
.end __osSetCompare
