.include "consts.inc"
.include "header.inc"
.include "utils.inc"
.include "InitNes.inc"
.include "ResetBgPtr.inc"
.include "InitBoard.inc"
.include "SwapBoards.inc"
.include "LifeLoop.inc"
.include "UpdateFrameOffset.inc"

.segment "ZEROPAGE"
Frame:              .res 1 
FrameOffset:        .res 1  
IsDrawComplete:     .res 1
BgPtr:              .res 2           
ZReg:               .res 1
CurrCellDraw:       .res 1
CurrBoardRd:        .res 1
BoardPtrRd:         .res 2
BoardPtrWr:         .res 2
CurrCellIsAliveA:   .res 1
CurrCellIsAliveB:   .res 1
BoardBCellCount:    .res 1

.segment "RAM"   
Board0:     .res 256
Board1:     .res 256

.segment "CODE"
.include "DrawBoard.inc"
.include "loadData.inc"
.include "WaitFrame.inc"

Reset:
    InitNes                 

InitVariables:
    lda #0
    sta Frame              
    sta FrameOffset
    sta CurrCellDraw
    sta CurrBoardRd

    ResetBgPtr
    SetPtr BoardPtrWr,Board1
    SetPtr BoardPtrRd,Board0

Main:   
    jsr LoadPalette    
    jsr LoadAttributes  
    InitBoard

EnablePPURendering:
    lda #%10000000           ; Enable NMI and set background to use the 2nd pattern table (at $1000)
    sta PPU_CTRL
    lda #%00011110
    sta PPU_MASK             ; Set PPU_MASK bits to render the background

GameLoop:
    WaitFrames 5             ; Only process every board every 5 frames
    LifeLoop
    SwapBoards
    jmp GameLoop

NMI:
    PushRegs
    
    inc Frame               
    UpdateFrameOffset
    jsr DrawBoard  

    lda #0
    sta PPU_SCROLL           ; Disable scroll in X
    sta PPU_SCROLL           ; Disable scroll in Y

    PullRegs
    rti

IRQ:
    rti                      ; Return from interrupt


.include "data.inc"
.segment "CHARS"
.incbin "gol.chr"

.segment "VECTORS"
.word NMI                    ; Address (2 bytes) of the NMI handler
.word Reset                  ; Address (2 bytes) of the Reset handler
.word IRQ                    ; Address (2 bytes) of the IRQ handler
