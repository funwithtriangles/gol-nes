.macro PPU_SETADDR addr
    bit PPU_STATUS           ; Read from PPU_STATUS to reset the address latch
    lda #>addr               ; Fetch the hi-byte from 16-bit address
    sta PPU_ADDR             ; Store the hi-byte into PPU_ADDR $2006
    lda #<addr               ; Fetch the lo-byte from 16-bit address
    sta PPU_ADDR             ; Store the lo-byte into PPU_ADDR $2006
.endmacro

.macro PPU_SETADDR_PTR ptr
    bit PPU_STATUS           ; Read from PPU_STATUS to reset the address latch
    lda ptr+1              ; Fetch the hi-byte from 16-bit address
    sta PPU_ADDR             ; Store the hi-byte into PPU_ADDR $2006
    lda ptr              ; Fetch the lo-byte from 16-bit address
    sta PPU_ADDR             ; Store the lo-byte into PPU_ADDR $2006
.endmacro

.macro PPU_SETDATA val
    lda val
    sta PPU_DATA             ; Send value to PPU register at $2007
.endmacro

.macro SET_PTR ptr, addr
    lda #<addr
    sta ptr
    lda #>addr
    sta ptr+1
.endmacro

.macro ADD_FIXED fixedPoint, singleByte
    lda singleByte
    clc
    adc fixedPoint                 ; Add the velocity to the X position lo-byte
    sta fixedPoint
    lda #0
    adc fixedPoint+1               ; Add the hi-byte (using the carry of the previous add)
    sta fixedPoint+1
.endmacro

.macro ADD val
    clc
    adc val
.endmacro

.macro SUB val
    sec
    sbc val
.endmacro

.macro MIN val
    cmp val
    bcc :+
        lda val
    :
.endmacro

.macro MAX val
    cmp val
    bcs :+
        lda val
    :
.endmacro
