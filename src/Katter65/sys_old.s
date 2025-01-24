.macro set addr, value
    lda value
    sta addr
.endmacro

.macro set16 addr, value ; Sets a 16 bit value
    set addr,   value>>8
    set addr+1, value & $FF
.endmacro

.macro add addr0, addr1, result_addr
    clc
    lda addr0
    adc addr1
    sta result_addr
.endmacro

.macro cpystr str, dest
    ldx #0
    .local cpystr_l
    cpystr_l:
        set {dest,x}, {str,x}
        inx
        lda str,x
        bne cpystr_l
.endmacro

; Sets a page-sized buffer (thus size must be a byte) with a single value
.macro memset start, value, size
    ldx #0
    lda value
    .local memset_l
    memset_l:
        sta start,x
        cpx size
        bne memset_l
.endmacro

; TEST_CODE or a sample program that is loaded into memory by the kernel
; start = $4000 end = $8000
.segment "CODE"


mem_start = $0500
q         = mem_start
w         = mem_start+1
e         = mem_start+2

code_start:
    ; Init fib
    set q, #1
    sta w

code_fib:
    ldx q
    stx e
    add e, w, e
    set q, w
    set w, e

    bcc code_fib

    rts

.segment "KERNEL"  ; ROM kernel code


interrupt:         ; 3 bytes
    jmp interrupt_handle

start:
    ; jsr $4000  ; jump to program

halt:
    jmp halt

; String literals
text_prompt: .byte "> ", $00


interrupt_handle:
    memset $0300, #0, #$ff
    cpystr $0200, $0300
    rti



.segment "VECTORS"
.word $0000        ; nonmaskable interrupt handler 
.word $8003        ; reset location                
.word $8000        ; BRK / interrupt handler         