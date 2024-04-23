.macro INIT_BOARD
ldx #0
:
    lda InitialBoard,x
    sta Board1,x
    inx
    bne :-
.endmacro
