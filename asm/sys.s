.segment "CODE"




.segment "VECTORS"
.word
    $0000,              ; nonmaskable interrupt handler
    $8000,              ; reset location
    $0000               ; BRK / interrupt handler