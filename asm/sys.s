.segment "CODE"

start:
    lda $0101
    jmp start

.segment "VECTORS"
.word $0000, $8000, $0000