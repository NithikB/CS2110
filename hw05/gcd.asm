;;=============================================================
;; CS 2110 - Spring 2021
;; Homework 5 - Iterative GCD
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; a = (argument 1);
;; b = (argument 2);
;; ANSWER = 0;
;;
;; while (a != b) {
;;   if (a > b) {
;;     a = a - b;
;;   } else {
;;     b = b - a;
;;   }
;; }
;; ANSWER = a;

.orig x3000

;; put your code here
LD R1, A ; R1 = A
LD R2, B ; R2 = B
LD R3, ANSWER ; R3 = ANSWER

LOOP ; while start
    AND R4, R4, #0 ; clear R4
    AND R5, R4, #0 ; clear R5
    NOT R4, R2
    ADD R4, R4, 1 ; R4 = -R2
    ADD R5, R1, R4 ; R5 = A-B
    BRz ENDLOOP ; if a != b, end while

    BRn ELSE
    ADD R1, R5, #0 ; A = A-B
    BR END
    ELSE
    AND R6, R6, #0 ; clear R6
    NOT R6, R1
    ADD R6, R6, 1 ; R6 = -A
    ADD R2, R2, R6 ; B = B-A
    END
    BR LOOP

ENDLOOP
ST R1, ANSWER ; ANSWER = A
;;

HALT

A .fill 20
B .fill 19

ANSWER .blkw 1

.end
