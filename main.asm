.include "consts.inc"
.include "header.inc"
.include "reset.inc"
.include "utils.inc"
.include "resetBgPtr.inc"
.include "initboard.inc"
.include "setboardptr.inc"
.include "SwapBoards.inc"
.include "LifeLoop.inc"

.segment "ZEROPAGE"
IsDrawComplete: .res 1
Frame:          .res 1           ; Counts frames
BgPtr:          .res 2           ; Pointer to background address - 16bits (lo,hi)
ZReg:           .res 1
CurrCellDraw:   .res 1
CurrBoardRd:    .res 1
BoardPtrRd:     .res 2
BoardPtrWr:     .res 2
CurrCellIsAlive:.res 1

.segment "RAM"   
Board0:     .res 256
Board1:     .res 256

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; PRG-ROM code located at $8000
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.segment "CODE"
.include "drawboard.inc"
.include "loadbackground.inc"
.include "WaitFrame.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Reset handler (called when the NES resets or powers on)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Reset:
    INIT_NES                 ; Macro to initialize the NES to a known state

InitVariables:
    lda #0
    sta Frame                ; Frame = 0
    sta CurrCellDraw
    sta CurrBoardRd
    sta CurrCellIsAlive

    RESET_BG_PTR
    SET_PTR BoardPtrWr,Board1
    SET_PTR BoardPtrRd,Board0

Main:       
    jsr LoadPalette    
    jsr LoadAttributes  
    INIT_BOARD

EnablePPURendering:
    lda #%10010000           ; Enable NMI and set background to use the 2nd pattern table (at $1000)
    sta PPU_CTRL
    lda #%00011110
    sta PPU_MASK             ; Set PPU_MASK bits to render the background

GameLoop:
    LifeLoop

    SwapBoards
    jmp GameLoop

NMI:
    PushRegs

    inc Frame                ; Frame++
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
.incbin "battle.chr"

.segment "VECTORS"
.word NMI                    ; Address (2 bytes) of the NMI handler
.word Reset                  ; Address (2 bytes) of the Reset handler
.word IRQ                    ; Address (2 bytes) of the IRQ handler
