;;=============================================================
;; CS 2110 - Spring 2021
;; Homework 6 - Bubble Sort with Compare
;;=============================================================
;; Name:
;;=============================================================

;; In this file, you must implement the 'SORT' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseLL' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; array: memory address of the first element in the array
;; len: integer value of the number of elements in the array
;; compare: memory address of the subroutine used to compare elements
;;
;; sort(array, len, function compare) {
;;     // last index of the array
;;     y = len - 1;
;;     while(y > 0) {
;;         x = 0;
;;         while(x < y) {
;;             // if compare returns 1, swap
;;             if (compare(ARRAY[x], ARRAY[x+1]) > 0) {
;;                 temp = ARRAY[x];
;;                 ARRAY[x] = ARRAY[x+1];
;;                 ARRAY[x+1] = temp;
;;             }
;;             x++;
;;         }
;;         y--;
;;     }
;; }
;;
;; HINT: compare will be passed as a parameter on the stack. It will be a
;; a pointer to one of the subroutines below. Think about which instruction
;; allows you to call a subroutine with a memory address that is stored in a register
SORT



ADD R6, R6, -4; Allocate space
STR R7, R6, 2; Save Ret Addr
STR R5, R6, 1; Save Old FP
ADD R5, R6, 0; Copy SP to FP
ADD R6, R6, -5; Room for 5 regs
STR R0, R5, -1
STR R1, R5, -2
STR R2, R5, -3
STR R3, R5, -4
STR R4, R5, -5



LDR R0, R5, 4 ; R0 = array
LDR R1, R5, 5 ; R1 = len
LDR R2, R5, 6 ; R0 = function compare

AND R3, R3, 0
ADD R3, R1, -1 ; y = len - 1
STR R3, R5, 0 ; y in local variable
LOOP1
LDR R3, R5, 0
BRnz END ; while y>0
AND R4, R4, 0 ; x = 0
    LOOP2
    STR R3, R5, 0 ; temp store y
    NOT R3, R3
    ADD R3, R3, 1
    ADD R4, R4, R3 ; x-y
    BRzp END1 ; while x<y
    LDR R3, R5, 0 ; y back
    ADD R4, R4, R3 ; x back



    ADD R6, R6, -1 ;push x+1 to stack
    ADD R1, R0, R4; index x+1
    ADD R1, R1, 1
    LDR R1, R1, 0 ; temp = array[x+1]
    STR R1, R6, 0

    ADD R6, R6, -1 ;push x to stack
    ADD R1, R0, R4; index x
    LDR R1, R1, 0 ; temp = array[x]
    STR R1, R6, 0

    LDR R2, R5, 6 ; R2 = function compare
    JSRR R2
    LDR R1, R6, 0
    ADD R6, R6, 3
    ADD R1, R1, 0
    BRnz ENDIF
    ADD R3, R0, R4; index x
    LDR R1, R3, 0 ; temp = array[x]
    ADD R3, R3, 1 ; x+1
    LDR R2, R3, 0 ; array[x+1]
    STR R2, R3, -1 ; array[x] = array[x-1]
    STR R1, R3, 0 ; array[x+1] = temp

    LDR R3, R5, 0 ; y back
    ENDIF
    ADD R4, R4, 1 ; x++
    BRnzp LOOP2



END1
LDR R3, R5, 0 ; y back
ADD R3, R3, -1 ; y-1
STR R3, R5, 0 ; y temp store
BRnzp LOOP1


END



LDR R0, R5, 0 ; Ret val = answer
STR R0, R5, 3
LDR R4, R5, -5; Restore R4
LDR R3, R5, -4; Restore R3
LDR R2, R5, -3; Restore R2
LDR R1, R5, -2; Restore R0
LDR R0, R5, -1; Restore R1
ADD R6, R5, 0; Restore SP
LDR R5, R6, 1; Restore FP
LDR R7, R6, 2; Restore RA
ADD R6, R6, 3; Pop ra,fp,lv1
RET

;; used by the autograder
STACK .fill xF000
.end

;; USE FOR DEBUGGING IN COMPLEX
;; load array at x4000 and put the length as 7
;; you can use the memory addresses of the subroutines below for the last parameter

;; ARRAY
.orig x4000
    .fill 4
    .fill -9
    .fill 0
    .fill -2
    .fill 9
    .fill 3
    .fill -10
.end

;; The following subroutines are possible functions that may be passed
;; as the function address parameter into the sorting function.
;; DO NOT edit the code below; it will be used by the autograder.
.orig x5000
;; returns a positive number if a>b
;; compare(a,b) for ascending sort
CMPGT
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x6384
    .fill   x927F
    .fill   x1261
    .fill   x1201
    .fill   x0C03
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end

.orig x5100
;; returns a positive number if b>a
;; compare(a,b) for descending sort
CMPLT
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x6384
    .fill   x927F
    .fill   x1261
    .fill   x1201
    .fill   x0603
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end

.orig x5200
;; returns a positive number if |a| > |b|
;; compare(a,b) for ascending sort on magnitudes (absolute value)
CMPABS
    .fill   x1DBD
    .fill   x7180
    .fill   x7381
    .fill   x6183
    .fill   x0602
    .fill   x903F
    .fill   x1021
    .fill   x6384
    .fill   x0C02
    .fill   x927F
    .fill   x1261
    .fill   x1240
    .fill   x0C03
    .fill   x5020
    .fill   x1021
    .fill   x0E01
    .fill   x5020
    .fill   x7182
    .fill   x6180
    .fill   x6381
    .fill   x1DA2
    .fill   xC1C0
.end
