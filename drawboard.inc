.proc DrawBoard

ldy #0
ldx #16
lda #4
sta ZReg

PPU_SETADDR_PTR BgPtr          

:
    ldy CurrCellDraw
    lda (BoardPtr),y
    sta PPU_DATA  
    inc CurrCellDraw
    beq Reset             
    dex          
    bne :-                  
        ldx #16
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