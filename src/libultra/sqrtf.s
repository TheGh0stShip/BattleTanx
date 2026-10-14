/* libultra 2.0I sqrtf: single-precision square root leaf routine. */
.set noreorder
.set noat
.text

.globl sqrtf
.ent sqrtf
sqrtf:
    jr      $ra
    sqrt.s  $f0, $f12
.end sqrtf
