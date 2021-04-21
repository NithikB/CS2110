LD R0, HEAD ; curr = head


LOOP1 ; while
    ADD R0, R0, #0
    BRz ENDLOOP1 ; while (curr != 0)

    LDR R2, R0, #1 ; x = curr.value
    ADD R2, R2, #1 ; x = x + 1
    STR R2, R0, #1 ; curr.value = x
    LDR R1, R0, #0 ; next = curr.next
    ADD R0, R1, #0 ; curr = next
    BR LOOP1
ENDLOOP1
