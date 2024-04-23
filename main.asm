.include "consts.inc"
.include "header.inc"
.include "reset.inc"
.include "utils.inc"
.include "resetBgPtr.inc"
.include "initboard.inc"
.include "setboardptr.inc"
.include "SwapBoards.inc"

.segment "ZEROPAGE"
Frame:          .res 1           ; Counts frames
BgPtr:          .res 2           ; Pointer to background address - 16bits (lo,hi)
IsDrawComplete: .res 1
ZReg:           .res 1
CurrCellDraw:   .res 1
CurrBoardRd:    .res 1
BoardPtrRd:     .res 2
BoardPtrWr:     .res 2



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


; CELL IS DEAD, UNLESS...
; 3 = ALIVE
; Alive?, 2 = ALIVE
GameLoop:
    ldy #0
    Loop:
        ; lda (BoardPtrRd),y
        dey 
        lda (BoardPtrRd),y
        beq Continue
        Alive:
            lda #$1
        Continue:
            iny
            sta (BoardPtrWr),y
            iny
            bne Loop

    SwapBoards

    ; TODO: Probably nicer way to pause
    jsr WaitFrame
    jsr WaitFrame
    jsr WaitFrame
    jsr WaitFrame
    jsr WaitFrame
    jsr WaitFrame
    
    jmp GameLoop



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; NMI interrupt handler
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
NMI:
    pha         ; back up registers (important)
    txa
    pha
    tya
    pha

    inc Frame                ; Frame++
    jsr DrawBoard  

    lda #0
    sta PPU_SCROLL           ; Disable scroll in X
    sta PPU_SCROLL           ; Disable scroll in Y

SetDrawComplete:
    lda #1
    sta IsDrawComplete

    pla            ; restore regs and exit
    tay
    pla
    tax
    pla
    rti


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; IRQ interrupt handler
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
IRQ:
    rti                      ; Return from interrupt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Hardcoded list of color values in ROM to be loaded by the PPU
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PaletteData:
.byte $00,$00,$10,$0F, $1D,$10,$20,$2D, $1D,$10,$20,$2D, $1D,$10,$20,$2D ; Background palette
.byte $00,$1D,$19,$29, $0F,$08,$18,$38, $0F,$0C,$1C,$3C, $0F,$2D,$10,$30 ; Sprite palette

AttributeData:
.byte %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111
.byte %11111111, %11111111, %00001111, %00001111, %00001111, %00001111, %11111111, %11111111
.byte %11111111, %11111111, %00000000, %00000000, %00000000, %00000000, %11111111, %11111111
.byte %11111111, %11111111, %00000000, %00000000, %00000000, %00000000, %11111111, %11111111
.byte %11111111, %11111111, %00000000, %00000000, %00000000, %00000000, %11111111, %11111111
.byte %11111111, %11111111, %11110000, %11110000, %11110000, %11110000, %11111111, %11111111
.byte %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111
.byte %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111, %11111111

InitialBoard:
.byte $1,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0
.byte $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Here we add the CHR-ROM data, included from an external .CHR file
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.segment "CHARS"
.incbin "battle.chr"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Vectors with the addresses of the handlers that we always add at $FFFA
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.segment "VECTORS"
.word NMI                    ; Address (2 bytes) of the NMI handler
.word Reset                  ; Address (2 bytes) of the Reset handler
.word IRQ                    ; Address (2 bytes) of the IRQ handler
