.macro PPUSetAddr addr
    bit PPU_STATUS           ; Read from PPU_STATUS to reset the address latch
    lda #>addr               ; Fetch the hi-byte from 16-bit address
    sta PPU_ADDR             ; Store the hi-byte into PPU_ADDR $2006
    lda #<addr               ; Fetch the lo-byte from 16-bit address
    sta PPU_ADDR             ; Store the lo-byte into PPU_ADDR $2006
.endmacro

.macro PPUSetAddrPtr ptr
    bit PPU_STATUS           ; Read from PPU_STATUS to reset the address latch
    lda ptr+1              ; Fetch the hi-byte from 16-bit address
    sta PPU_ADDR             ; Store the hi-byte into PPU_ADDR $2006
    lda ptr              ; Fetch the lo-byte from 16-bit address
    sta PPU_ADDR             ; Store the lo-byte into PPU_ADDR $2006
.endmacro

.macro PPUSetData val
    lda val
    sta PPU_DATA             ; Send value to PPU register at $2007
.endmacro

.macro SetPtr ptr, addr
    lda #<addr
    sta ptr
    lda #>addr
    sta ptr+1
.endmacro

.macro AddFixed fixedPoint, singleByte
    lda singleByte
    clc
    adc fixedPoint                 ; Add the velocity to the X position lo-byte
    sta fixedPoint
    lda #0
    adc fixedPoint+1               ; Add the hi-byte (using the carry of the previous add)
    sta fixedPoint+1
.endmacro

.macro PushRegs
    pha         
    txa
    pha
    tya
    pha
    php
.endmacro

.macro PullRegs
    plp                     
    pla           
    tay
    pla
    tax
    pla
.endmacro