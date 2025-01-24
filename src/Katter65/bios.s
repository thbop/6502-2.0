.segment "BIOS"

rti


.segment "VECTORS"
.word $8000        ; nonmaskable interrupt handler 
.word $9000        ; reset location                
.word $8000        ; BRK / interrupt handler         