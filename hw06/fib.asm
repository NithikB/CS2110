;;=======================================
;; CS 2110 - Spring 2020
;; HW6 - Recursive Fibonacci Sequence
;;=======================================
;; Name:
;;=======================================

;; In this file, you must implement the 'fib' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff: don't run
;; this directly by pressing 'RUN' in complx, since there is nothing put at
;; address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'reverseLL' label.

.orig x3000
HALT

;; Pseudocode (see PDF for explanation):
;;
;; Arguments of Fibonacci number: integer n
;;
;; Pseudocode:
;; fib(int n) {
;;     if (n == 0) {
;;         return 0;
;;     } else if (n == 1) {
;;         return 1;
;;     } else {
;;         return fib(n - 1) + fib(n - 2);
;;     }
;; }
fib

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



LDR R0, R5, 4 ; R0 stores n
BRnp ELSEIF1
AND R0, R0, 0
STR R0, R5, 0
BRnzp END
ELSEIF1
ADD R0, R0, -1
BRnp ELSE
ADD R0, R0, 1
STR R0, R5, 0
BRnzp END
ELSE
LDR R0, R5, 4
ADD R0, R0, -1
AND R1, R1, 0
ADD R1, R0, -1
ADD R6, R6, -1
STR R0, R6, 0
JSR fib
LDR R0, R6, 0
ADD R6, R6, 2
ADD R6, R6, -1
STR R1, R6, 0
JSR fib
LDR R1, R6, 0
ADD R6, R6, 2
ADD R0, R0, R1
STR R0, R5, 0


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
