ORG 0H
LJMP MAIN
ORG 100H
MAIN:
MOV R1, #61H
CALL MODADD
CALL MODSUB
HERE: SJMP HERE
ORG 130H


MODADD:
MOV A, 70H
MOV B, R1
ADD A, 71H
DIV AB
MOV 72H, B
CLR C
RET

MODSUB:
JNC SUBTRACT
RET

SUBTRACT:
MOV A, 70H
MOV B, R1
SUBB A, 71H

MAINFUNCTION:
JC ADD_DIVISOR
DIV AB
MOV 73H, B
SETB C
JMP MODSUB

ADD_DIVISOR:
ADD A, R1
JMP MAINFUNCTION


END