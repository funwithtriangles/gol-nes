.macro UpdateFrameOffset
    lda Frame
    and #%00000011
    bne :++
        lda FrameOffset
        clc
        adc #$10
        cmp #$80
        bne :+
            lda #0
        :

        sta FrameOffset
    :
.endmacro