.proc DrawBoard

ldx #0
ldy #16
lda #4
sta ZReg

PPU_SETADDR_PTR BgPtr          

:
    ldx CurrCellDraw
    lda InitialBoard,x
    sta PPU_DATA  
    inc CurrCellDraw
    beq Reset             
    dey          
    bne :-                  
        ldy #16
        ADD_FIXED BgPtr, #32
        PPU_SETADDR_PTR BgPtr    
        dec ZReg     
    bne :-
        rts
    Reset:
        lda #0
        sta CurrCellDraw
        RESET_BG_PTR
        rts
.endproc