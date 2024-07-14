.segment "CODE"

lda #3
pha
lda #1
pha
lda #7
pha

pla
pla
pla

.segment "VECTORS"
.word $0000, $8000, $0000