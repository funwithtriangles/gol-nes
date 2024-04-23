.macro SwapBoards
lda CurrBoardRd
beq RdBoard1
RdBoard0:
    SET_PTR BoardPtrWr,Board1
    SET_PTR BoardPtrRd,Board0
    lda #0
    sta CurrBoardRd
    jmp :+
RdBoard1:
    SET_PTR BoardPtrWr,Board0
    SET_PTR BoardPtrRd,Board1
    lda #1
    sta CurrBoardRd
:
.endmacro