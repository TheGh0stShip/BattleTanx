.set noreorder
.text

.globl __osSetFpcCsr
.ent __osSetFpcCsr
__osSetFpcCsr:
    cfc1    $v0, $31
    ctc1    $a0, $31
    jr      $ra
     nop
.end __osSetFpcCsr
