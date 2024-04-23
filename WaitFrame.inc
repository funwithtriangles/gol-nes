.macro WAIT_FRAME
  lda IsDrawComplete
    WaitVBlank:
        cmp IsDrawComplete
        beq WaitVBlank
    
    lda #0
    sta IsDrawComplete
.endmacro