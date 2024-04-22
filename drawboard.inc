.proc DrawBoard
lda #$A8
sta BgPtr
lda #$20
sta BgPtr+1

ldx #0
ldy #16
lda #16
sta ZReg

PPU_SETADDR_PTR BgPtr          

:
    lda InitialBoard,x 
    sta PPU_DATA   
    inx            
    dey          
    bne :-                  
        ldy #16
        ADD_FIXED BgPtr, #32
        PPU_SETADDR_PTR BgPtr    
        dec ZReg     
    bne :-
        rts
.endproc