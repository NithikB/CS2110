;;=============================================================
;; CS 2110 - Fall 2020
;; Homework 5 - Palindrome
;;=============================================================
;; Name:
;;=============================================================

;; Pseudocode (see PDF for explanation):
;;
;; string = "racecar";
;; len = 0;
;;
;; // to find the length of the string
;; while (string[len] != '\0') {
;;   len = len + 1;
;; }
;;
;; // to check whether the string is a palindrome
;; result = 1;
;; i = 0;
;; while (i < length) {
;;   if (string[i] != string[length - i - 1]) {
;;     result = 0;
;;     break;
;;   }
;;   i = i + 1;
;; }

.orig x3000

LD R1, STRING
AND R2, R2, 0 ; len = 0

LOOP ; while start
    ADD R0, R1, R2 ; len
    LDR R0, R0, 0 ; string[len]
    BRz ENDLOOP ; if char is \0, end while

    ADD R2, R2, #1
    BR LOOP

ENDLOOP

AND R3, R3, 0
ADD R3, R3, 1 ; result = 1
AND R4, R4, 0 ; i = 0

LOOP1 ; while 2
    AND R0, R0, #0
    NOT R0, R2
    ADD R0, R0, 1 ; -length
    ADD R0, R4, R0 ; i - length
    BRzp ENDLOOP1 ; if i >= length

    ADD R5, R1, R4 ; i
    LDR R5, R5, 0 ; string[i]
    ADD R6, R1, R2 ; len
    NOT R0, R4 ; i - 1
    ADD R6, R6, R0 ; len - i - 1
    LDR R6, R6, 0 ; string[len-i-1]
    NOT R6, R6
    ADD R6, R6, 1 ; -R6
    ADD R5, R5, R6
    BRz SKIP
    AND R3, R3, #0
    BR ENDLOOP1
    SKIP

    ADD R4, R4, #1
    BR LOOP1
ENDLOOP1
ST R3, ANSWER

HALT

ANSWER .blkw 1
STRING .fill x4000
.end

.orig x4000
.stringz "racecar"
.end
