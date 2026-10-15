.set noreorder
.text

.globl read_status_register
.globl func_800771F4
.ent read_status_register
read_status_register:
func_800771F4:
    mfc0    $2, $12
    jr      $31
     nop
.end read_status_register

.globl write_status_register
.globl func_80077200
.ent write_status_register
write_status_register:
func_80077200:
    mtc0    $4, $12
    jr      $31
     nop
.end write_status_register
