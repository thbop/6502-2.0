.segment "BOOTLOADER"

halt:
    brk
    jmp halt

.align 512