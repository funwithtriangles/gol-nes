.macro RESET_BG_PTR
    lda #$A8
    sta BgPtr
    lda #$20
    sta BgPtr+1
.endmacro