.proc LoadAttributes
    PPU_SETADDR $23C0        ; Load nametable attributes
    ldy #0                   ; Y = 0
:   lda AttributeData,y      ; Lookup byte in ROM
    sta PPU_DATA             ; Set value to send to PPU_DATA
    iny                      ; Y++
    cpy #16                  ; Is Y equal to 16?
    bne :-                   ; Not yet, keep looping
    rts                      ; Return from subroutine
.endproc

.proc LoadPalette
    PPU_SETADDR $3F00
    ldy #0                   ; Y = 0
:   lda PaletteData,y        ; Lookup byte in ROM
    sta PPU_DATA             ; Set value to send to PPU_DATA
    iny                      ; Y++
    cpy #32                  ; Is Y equal to 32?
    bne :-                   ; Not yet, keep looping
    rts                      ; Return from subroutine
.endproc

