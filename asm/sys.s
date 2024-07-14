.segment "CODE"

start:
    ldy #$13
    lda ($11),y
    jmp start

.segment "VECTORS"
.word $0000, $8000, $0000