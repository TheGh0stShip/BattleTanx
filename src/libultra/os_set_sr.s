.set noreorder
.text

.globl __osSetSR
.ent __osSetSR
__osSetSR:
    mtc0    $a0, $12
    nop
    jr      $ra
     nop
.end __osSetSR
