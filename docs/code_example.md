; Use ";" for comments.
; Computes (4 + 2) + 1 and prints the result.
; Values are represented in balanced ternary with trits in LSB-first order.
;
; 4  = 1 1  => (1 * 3^0) + (1 * 3^1)
; 2  = -1 1 => (-1 * 3^0) + (1 * 3^1)
; 1  = 1
;
; Execution:
;   PUSH 4
;   PUSH 2
;   ADD      ; pushes 6
;   PUSH 1
;   ADD      ; pushes 7
;   POP      ; prints 7 in ternary
;   HALT

PUSH 2 1 1      ; Push 4 (1 1 in ternary)
PUSH 2 -1 1     ; Push 2 (-1 1 in ternary)
ADD             ; Add top two values (4 + 2 = 6)
PUSH 1 1        ; Push 1 (1 in ternary)
ADD             ; Add top two values (6 + 1 = 7)
POP             ; Pop and print the result (7 in ternary)
HALT            ; End of program
