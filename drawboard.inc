.proc DrawBoard

ldy #0
ldx #16
lda #4
sta ZReg

PPUSetAddrPtr BgPtr          

:
    ldy CurrCellDraw
    lda (BoardPtrRd),y
    clc
    adc FrameOffset
    sta PPU_DATA  
    inc CurrCellDraw
    beq Reset             
    dex          
    bne :-                  
        ldx #16
        AddFixed BgPtr, #32
        PPUSetAddrPtr BgPtr    
        dec ZReg     
    bne :-
        rts
    Reset:
        lda #0
        sta CurrCellDraw
        inc IsDrawComplete
        ResetBgPtr
        rts
.endproc