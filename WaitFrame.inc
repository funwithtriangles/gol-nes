.proc WaitFrame
  lda IsDrawComplete
    WaitVBlank:
        cmp IsDrawComplete
        beq WaitVBlank
    
    lda #0
    sta IsDrawComplete
    rts
.endproc