ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL DET
HERE: SJMP HERE
ORG 130H


DET:
MOV A, 60H
MOV B, 63H
MUL AB
MOV 64H, B
MOV 65H, A
MOV A, 61H
MOV B, 62H
MUL AB
MOV 66H, B
MOV 67H, A
MOV A, 65H
MOV B, 67H
SUBB A, B
MOV 71H, A
MOV A, 64H
MOV B, 66H
SUBB A, B
MOV 70H, A
RET

END