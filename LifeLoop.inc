
.macro CheckCell
lda (BoardPtrRd),y
beq :+
    inx
:
.endmacro

.macro LifeLoop
ldy #0
Loop:
    ldx #0
    stx CurrCellIsAlive

    ; Check curr cell
    lda (BoardPtrRd),y
    beq :+
        inc CurrCellIsAlive
    :

    ; Check prev cell
    dey 
    CheckCell

    ; Check next cell
    iny
    iny
    CheckCell

    ; Check row above, right
    tya
    sec
    sbc #16
    tay
    CheckCell

    ; Check row above, middle
    dey 
    CheckCell

    ; Check row above, left
    dey
    CheckCell

    ; Check row below, left
    tya
    clc
    adc #32
    tay
    CheckCell

    ; Check row below, middle
    iny 
    CheckCell

    ; Check row below, right
    iny
    CheckCell

    ; Reset y
    tya
    sec
    sbc #17
    tay

    cpx #3
    beq Alive
    
    lda CurrCellIsAlive
    beq Dead
        cpx #2
        beq Alive

    Dead:
        lda #$0
        jmp Continue

    Alive:
        lda #$1
        
    Continue:
        sta (BoardPtrWr),y
        iny
        bne Loop
.endmacro