.macro ResetBgPtr
    lda #$C8
    sta BgPtr
    lda #$20
    sta BgPtr+1
.endmacro