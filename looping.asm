.global _start

.section .text
_start:
    MOV R0, #1          @ Initialize R0 to 1

loop_start:
    CMP R0, #6          @ Compare R0 with 6
    BEQ exit            @ If equal, exit

    ADD R1, R0, #48     @ Convert to ASCII

    MOV R7, #4          @ sys_write
    MOV R2, R1          @ Address of the character
    MOV R1, R2
    MOV R3, #1          @ Length of the character

    MOV R7, #4          @ sys_write
    LDR R1, =newline    @ Address of newline
    MOV R2, R1
    MOV R3, #1          @ Length of the newline

    ADD R0, R0, #1      @ Increment the counter
    B loop_start        @ Loop back to start

exit:
    MOV R7, #1          @ sys_exit
    SWI 0

.section .data
newline: .asciz "\n"    @ Newline character