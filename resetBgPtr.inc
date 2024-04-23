.macro RESET_BG_PTR
    lda #$C8
    sta BgPtr
    lda #$20
    sta BgPtr+1
.endmacro