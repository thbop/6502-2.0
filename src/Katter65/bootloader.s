.segment "BOOTLOADER"

start:
    ; ldx #<msg_hello         ; X = string ptr low byte
    ; ldy #>msg_hello         ; Y = string ptr high byte
    ; lda #03                 ; Call BIOS puts function
    ; brk

    ldx #'A'
    lda #02                 ; Call BIOS putc function
    brk

halt:
    jmp halt

msg_hello: .byte "Hello World!"

.align 512