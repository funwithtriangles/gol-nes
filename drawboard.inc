.proc DrawBoard
    lda #$A8
    sta BgPtr
    lda #$20
    sta BgPtr+1

    ldx #0
    ldy #16
    lda #16
    sta ZCounter

    PPU_SETADDR_PTR BgPtr          

:

    lda InitialBoard,x 
    sta PPU_DATA   
    inx            
    dec ZCounter                   
    bne :-                  
        lda #16
        sta ZCounter
        ADD_FIXED BgPtr, #32
        PPU_SETADDR_PTR BgPtr    
        dey
    bne :-
        rts
.endproc