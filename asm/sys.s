.segment "CODE"


ss:
    jmp ss



.segment "VECTORS"
.word $0000  ; nonmaskable interrupt handler 
.word $8000  ; reset location                
.word $0000  ; BRK / interrupt handler         