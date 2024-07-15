.segment "CODE"

lda #$55
pha
plp
php
pla

.segment "VECTORS"
.word $0000, $8000, $0000