
; Bit 01 is Board A, Bit 10 is board B. 
; This Macro checks both boards and increments x and BoardBCellCount
.macro CheckCell
lda (BoardPtrRd),y
beq :++
    pha
    and #%01
    beq :+
        inx ; Inc BoardACellCount
    :

    pla
    and #%10
    beq :+
        inc BoardBCellCount
    :
.endmacro

.macro CurrCellCheck
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
.endmacro

.macro AliveCheckA val
    cpx #val
    beq AliveA
.endmacro

.macro AliveCheckB val
    cpx #val
    beq AliveB
.endmacro

.macro CountNeighbors
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
.endmacro

.macro LifeLoop
ldy #0                     ; y is current cell being processed
Loop:
    ldx #0                 ; x is BoardACellCount
    stx BoardBCellCount
    stx CurrCellIsAliveA
    stx CurrCellIsAliveB

    CurrCellCheck
    CountNeighbors

    AliveCheckA 3
    
    ; Board A follows GOL original rules (B3/S23)
    lda CurrCellIsAliveA
    beq DeadA
        AliveCheckA 2

    DeadA:
        lda #$0
        jmp ContinueA

    AliveA:
        lda #%01
        
    ContinueA:
        sta (BoardPtrWr),y

    
    ldx BoardBCellCount

    ; Board B follows "LowDeath rule" (B368/S238)
    ; https://conwaylife.com/wiki/List_of_Life-like_rules
    AliveCheckB 3
    AliveCheckB 8

    lda CurrCellIsAliveB
    beq DeadCheckB
        AliveCheckB 2
        jmp DeadB

    DeadCheckB:
        AliveCheckB 6

    DeadB:
        lda #$0
        jmp ContinueB

    AliveB:
        lda #%10
        
    ContinueB:
    ; Combine both boards into one
        ora (BoardPtrWr),y
        sta (BoardPtrWr),y
    
    ; Keep looping until y wraps to 0 (all 256 cells processed)
        iny
        beq :+
            jmp Loop
        : 
.endmacro