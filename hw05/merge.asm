;;=============================================================
;; CS 2110 - Spring 2020
;; Homework 5 - Array Merge
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; x = 0;
;; y = 0;
;; z = 0;
;; while (x < LENGTH_X && y < LENGTH_Y) {
;;   if (ARR_X[x] <= ARR_Y[y]) {
;;     ARR_RES[z] = ARR_X[x];
;;     z++;
;;     x++;
;;   } else {
;;     ARR_RES[z] = ARR_Y[y];
;;     z++;
;;     y++;
;;   }
;; }
;; while(x < ARRX.length) {
;;   ARR_RES[z] = ARR_X[x];
;;   z++;
;;   x++;
;; }
;; while (y < ARRY.length) {
;;   ARR_RES[z] = ARR_Y[y];
;;   z++;
;;   y++;
;; }



.orig x3000

AND R1, R1, #0 ; R1 = x = 0
AND R2, R2, #0 ; R2 = y = 0
AND R3, R3, #0 ; R3 = z = 0

LOOP ; while 1
    LD R0, LENGTH_X ; R0 = length of x
    NOT R0, R0
    ADD R0, R0, #1 ; R0 = -len_x
    ADD R0, R1, R0 ; R0 = x - len_x
    BRzp ENDLOOP ; if x >= LENGTH_X, end while
    LD R0, LENGTH_Y ; R0 = length of y
    NOT R0, R0
    ADD R0, R0, #1 ; R0 = -len_y
    ADD R0, R2, R0 ; R0 = y - len_y
    BRzp ENDLOOP ; if y >= LENGTH_y, end while

    LD R4, ARR_X
    ADD R4, R4, R1
    LDR R4, R4, 0
    LD R5, ARR_Y
    ADD R5, R5, R2
    LDR R5, R5, 0
    AND R6, R6, #0
    NOT R6, R5
    ADD R6, R6, #1
    ADD R6, R4, R6
    BRp ELSE
    LD R0, ARR_RES
    ADD R0, R0, R3
    STR R4, R0, 0
    ADD R3, R3, #1
    ADD R1, R1, #1
    BR END
    ELSE
    LD R0, ARR_RES
    ADD R0, R0, R3
    STR R5, R0, 0
    ADD R3, R3, #1
    ADD R2, R2, #1
    END
    BR LOOP

ENDLOOP

LOOP1 ; while 2
    LD R0, LENGTH_X ; R0 = length of x
    NOT R0, R0
    ADD R0, R0, #1 ; R0 = -len_x
    ADD R0, R1, R0 ; R0 = x - len_x
    BRzp ENDLOOP1 ; if x >= LENGTH_X, end while

    LD R4, ARR_X
    ADD R4, R4, R1
    LDR R4, R4, 0
    LD R0, ARR_RES
    ADD R0, R0, R3
    STR R4, R0, 0
    ADD R3, R3, #1
    ADD R1, R1, #1
    BR LOOP1

    ENDLOOP1

LOOP2 ; while 3
    LD R0, LENGTH_Y ; R0 = length of y
    NOT R0, R0
    ADD R0, R0, #1 ; R0 = -len_y
    ADD R0, R2, R0 ; R0 = y - len_y
    BRzp ENDLOOP2 ; if y >= LENGTH_y, end while
    LD R4, ARR_Y
    ADD R4, R4, R2
    LDR R4, R4, 0
    LD R0, ARR_RES
    ADD R0, R0, R3
    STR R4, R0, 0
    ADD R3, R3, #1
    ADD R2, R2, #1
    BR LOOP2

ENDLOOP2

HALT

ARR_X      .fill x4000
ARR_Y      .fill x4100
ARR_RES    .fill x4200

LENGTH_X   .fill 5
LENGTH_Y   .fill 7
LENGTH_RES .fill 12

.end

.orig x4000
.fill 1
.fill 5
.fill 10
.fill 11
.fill 12
.end

.orig x4100
.fill 3
.fill 4
.fill 6
.fill 9
.fill 15
.fill 16
.fill 17
.end
