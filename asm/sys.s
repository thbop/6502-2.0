.segment "CODE"

dat = $10


interrupt_handle: ; 5 bytes
    pha
    lda #$45
    pla
    rti

ss:
    jsr ee
    lda dat
    jmp ss

ee:
    inc dat
    inc dat
    brk
    rts



.segment "VECTORS"
.word $0000  ; nonmaskable interrupt handler 
.word $8005  ; reset location                
.word $8000  ; BRK / interrupt handler         