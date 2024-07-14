.segment "CODE"

lda #$12
ldx #$54
ldy #$65

sta $00
sta $00,x
sta $5000
sta $5000,x
sta $5000,y

ldx $5000,y


.segment "VECTORS"
.word
    $0000,              ; nonmaskable interrupt handler
    $8000,              ; reset location
    $0000               ; BRK / interrupt handler