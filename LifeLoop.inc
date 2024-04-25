
.macro CheckCell
lda (BoardPtrRd),y
beq :++
    pha
    and #%01
    beq :+
        inx
    :

    pla
    and #%10
    beq :+
        inc BoardBCellCount
    :
.endmacro

.macro LifeLoop
ldy #0
Loop:
    ldx #0                 ; x is BoardACellCount
    stx BoardBCellCount
    stx CurrCellIsAliveA
    stx CurrCellIsAliveB

    ; Check curr cell
    lda (BoardPtrRd),y

    pha
    and #%01
    beq :+
        inc CurrCellIsAliveA
    :

    pla
    and #%10
    beq :+
        inc CurrCellIsAliveB
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
    beq AliveA
    
    lda CurrCellIsAliveA
    beq DeadA
        cpx #2
        beq AliveA

    DeadA:
        lda #$0
        jmp ContinueA

    AliveA:
        lda #%01
        
    ContinueA:
        sta (BoardPtrWr),y

    ldx BoardBCellCount
    cpx #3
    beq AliveB
    
    lda CurrCellIsAliveB
    beq DeadB
        cpx #2
        beq AliveB

    DeadB:
        lda #$0
        jmp ContinueB

    AliveB:
        lda #%10
        
    ContinueB:
    ; Combine both boards into one
        ora (BoardPtrWr),y
        sta (BoardPtrWr),y
    
    ; Keep looping
        iny
        beq :+
            jmp Loop
        : 
.endmacro