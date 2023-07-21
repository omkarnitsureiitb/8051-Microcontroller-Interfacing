ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL SEARCH
HERE: SJMP HERE
ORG 130H

SEARCH:
MOV A, 30H
MOV R0, A
MOV A, 31H
MOV R2, A
MOV A, 32H
MOV R4, A

LOOP:
MOV A, R2
CLR C
SUBB A, #01H
JZ ONE
MOV A, R2
CLR C
SUBB A, #00H
JZ ZERO
MOV B, #02H
DIV AB
MOV R6, A
MOV A, B
JNZ ODD
JZ EVEN_N

ODD:
MOV A, R6
MOV B, R0
ADD A, B
MOV R1, A
MOV A, @R1
CLR C
SUBB A, R4
JZ FUNC3
JC FUNC1
JNC FUNC2

EVEN_N:
DEC R6
MOV A, R6
MOV B, R0
ADD A, B
MOV R1, A
MOV A, @R1
CLR C
SUBB A, R4
JZ FUNC3
JC FUNC4
JNC FUNC2

FUNC1:
INC R1
MOV A, R1
MOV R0, A
MOV A, R6
MOV R2, A
JMP LOOP


FUNC2:
INC R6
MOV A, R6
MOV R2, A
JMP LOOP

FUNC3:
MOV 33H, R1
RET

FUNC4:
INC R1
MOV A, R1
MOV R0, A
INC R6
MOV A, R6
MOV R2, A
JMP LOOP

ONE:
MOV A, @R0
MOV B, R4
CJNE A, B, ZERO
JMP FUNC5

ZERO:
MOV 33H, #0EH
RET

FUNC5:
MOV 33H, R0
RET

END