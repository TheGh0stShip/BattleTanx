/* libultra 2.0I os/writebackdcache.s (decompals/ultralib e24c836): osWritebackDCache. */
.set noreorder
.set noat
.text

.globl osWritebackDCache
.ent osWritebackDCache
osWritebackDCache:
    blez    $a1, .Lreturn
    nop
    addiu   $t3, $zero, 0x2000
    sltu    $at, $a1, $t3
    beqz    $at, .Lall
    nop
    or      $t0, $a0, $zero
    addu    $t1, $a0, $a1
    sltu    $at, $t0, $t1
    beqz    $at, .Lreturn
    nop
    andi    $t2, $t0, 0xF
    addiu   $t1, $t1, -0x10
    subu    $t0, $t0, $t2
.Lline:
    cache   0x19, 0($t0)
    sltu    $at, $t0, $t1
    bnez    $at, .Lline
    addiu   $t0, $t0, 0x10
.Lreturn:
    jr      $ra
    nop
.Lall:
    lui     $t0, 0x8000
    addu    $t1, $t0, $t3
    addiu   $t1, $t1, -0x10
.Lindex:
    cache   0x1, 0($t0)
    sltu    $at, $t0, $t1
    bnez    $at, .Lindex
    addiu   $t0, $t0, 0x10
    jr      $ra
    nop
.end osWritebackDCache
