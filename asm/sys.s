.segment "CODE"

dat = $10

.macro set addr, value ; little test macro
    pha
    lda value
    sta addr
    pla
.endmacro

set dat, 0
loop:
    inc dat
    inx
    iny
    lda dat
    jmp loop

.segment "VECTORS"
.word $0000, $8000, $0000