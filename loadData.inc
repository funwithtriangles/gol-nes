.proc LoadAttributes
    PPUSetAddr $23C0        ; Load nametable attributes
    ldy #0                   ; Y = 0
:   lda AttributeData,y      ; Lookup byte in ROM
    sta PPU_DATA             ; Set value to send to PPU_DATA
    iny                      ; Y++
    cpy #64                  ; Is Y equal to 64?
    bne :-                   ; Not yet, keep looping
    rts                      ; Return from subroutine
.endproc

.proc LoadPalette
    PPUSetAddr $3F00
    ldy #0                   ; Y = 0
:   lda PaletteData,y        ; Lookup byte in ROM
    sta PPU_DATA             ; Set value to send to PPU_DATA
    iny                      ; Y++
    cpy #32                  ; Is Y equal to 32?
    bne :-                   ; Not yet, keep looping
    rts                      ; Return from subroutine
.endproc

