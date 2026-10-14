.set noreorder
.set noat
.text

.globl osGetCount
.ent osGetCount
osGetCount:
    mfc0    $v0, $9
    jr      $ra
     nop
.end osGetCount
