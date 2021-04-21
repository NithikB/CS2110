;;=============================================================
;; CS 2110 - Fall 2021
;; Homework 5 - Studly Caps!
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation)
;;
;; string = "TWENTY 1 ten";
;; i = 0;
;; while (string[i] != 0) {
;;   if (i % 2 == 0) {
;;   // should be lowercase
;;     if ('A' <= string[i] <= 'Z') {
;;       string[i] = string[i] | 32;
;;     }
;;   } else {
;;   // should be uppercase
;;     if ('a' <= string[i] <= 'z') {
;;       string[i] = string[i] & ~32;
;;     }
;;   }
;;   i++;
;; }

.orig x3000

LD R1, STRING ; string start index
AND R2, R2, 0 ; i = 0

LOOP1 ; while 2
    AND R0, R0, #0
    ADD R0, R1, R2 ; i
    LDR R0, R0, 0 ; string[i]
    BRz ENDLOOP1 ; if i >= length

    AND R3, R2, 1 ; if i%2
    BRnp ELSE

    LD R3, UPPERA
    LD R4, UPPERZ
    NOT R5, R0
    ADD R5, R5, 1
    ADD R5, R3, R5
    BRp SKIP
    NOT R5, R4
    ADD R5, R5, 1
    ADD R5, R0, R5
    BRp SKIP

    AND R3, R3, 0
    ADD R3, R3, 15
    ADD R3, R3, 15
    ADD R3, R3, 2
    NOT R3, R3
    NOT R0, R0
    AND R0, R0, R3
    NOT R0, R0
    ADD R6, R1, R2 ; i
    STR R0, R6, 0


    SKIP

    BR END

    ELSE

    LD R3, LOWERA
    LD R4, LOWERZ
    NOT R5, R0
    ADD R5, R5, 1
    ADD R5, R3, R5
    BRp SKIP1
    NOT R5, R4
    ADD R5, R5, 1
    ADD R5, R0, R5
    BRp SKIP1

    AND R3, R3, 0
    ADD R3, R3, 15
    ADD R3, R3, 15
    ADD R3, R3, 2
    NOT R3, R3
    AND R0, R0, R3
    ADD R6, R1, R2 ; i
    STR R0, R6, 0

    SKIP1

    END

    ADD R2, R2, #1
    BR LOOP1
ENDLOOP1

HALT

UPPERA .fill x41    ;; A in ASCII
UPPERZ .fill x5A	;; Z in ASCII
LOWERA .fill x61	;; a in ASCII
LOWERZ .fill x7A	;; z in ASCII

STRING .fill x4000
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end
