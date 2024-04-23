.macro SET_BOARD_PTR addr   
    lda #<addr
    sta BoardPtr
    lda #>addr
    sta BoardPtr+1
.endmacro