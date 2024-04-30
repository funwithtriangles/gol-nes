.proc WaitFrame
  lda IsDrawComplete
    WaitVBlank:
        cmp IsDrawComplete
        beq WaitVBlank
    
    lda #0
    sta IsDrawComplete
    rts
.endproc

.macro WaitFrames num
  ldx #num
    :
        jsr WaitFrame
        dex
        bne :-
.endmacro