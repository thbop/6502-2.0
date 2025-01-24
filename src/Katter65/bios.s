.segment "BIOS"


; Control: $0200 - $0300
;  db $00 - State
;    v00 = NULL/success
;    v01 = Read drive

;  dw $01 - Holds the LBA address of the sector to start loading from (max $0B40, too lazy for CHS)
;  dw $03 - Number of sectors to read
;  dw $05 - Destination buffer

;  

; Text pages (row width 64 characters)
; $0300 - $0500


ctrl       = $0200
bootloader = $9000


load_bootloader:
    lda #$90
    sta ctrl+06        ; Set high byte of destination buffer to $90
    lda #01
    sta ctrl+03        ; Load 1 sector
    sta ctrl+00        ; Start load operation
    lda #00
    jmp bootloader

handle_interrupt:


    rti



.segment "VECTORS"
.word $8012        ; nonmaskable interrupt handler 
.word $8000        ; reset location                
.word $8012        ; BRK / interrupt handler         