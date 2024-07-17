.segment "CODE"
maddness:
    jsr maddness


.segment "VECTORS"
.word $0000  ; nonmaskable interrupt handler 
.word $0100  ; reset location                
.word $0000  ; BRK / interrupt handler         