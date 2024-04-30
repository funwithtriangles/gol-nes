.macro SwapBoards
lda CurrBoardRd
beq RdBoard1
RdBoard0:
    SetPtr BoardPtrWr,Board1
    SetPtr BoardPtrRd,Board0
    lda #0
    sta CurrBoardRd
    jmp :+
RdBoard1:
    SetPtr BoardPtrWr,Board0
    SetPtr BoardPtrRd,Board1
    lda #1
    sta CurrBoardRd
:
.endmacro