.macro INIT_BOARD
ldx #0
:
    lda InitialBoard,x
    sta Board0,x
    inx
    bne :-
.endmacro
