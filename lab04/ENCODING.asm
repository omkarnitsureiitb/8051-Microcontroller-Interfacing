ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H


DELAY_5S:
MOV R5, #20

L1:
MOV R4, #255
DJNZ R5, L2
RET

L2:
DJNZ R4, LF
JMP L1

LF:
CALL DELAY_1MS
JMP L2

DELAY_10S:
MOV R5, #39

L_1:
MOV R4, #255
DJNZ R5, L_2
RET

L_2:
DJNZ R4, L_F
JMP L_1

L_F:
CALL DELAY_1MS
JMP L_2

DELAY_1MS:
PUSH 00H
MOV R0, #4
H2: ACALL DELAY_250US
DJNZ R0, H2
POP 00H
RET

DELAY_250US:
PUSH 00H
MOV R0, #244
H1: DJNZ R0, H1
POP 00H
RET

TAKE_INP:
MOV P1, #80H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV A, P1
ANL A, #0FH
SWAP A


MOV P1, #40H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV B, P1
ANL B, #0FH
ADD A, B
MOV 60H, A


MOV P1, #0C0H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV A, P1
ANL A, #0FH
SWAP A


MOV P1, #20H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV B, P1
ANL B, #0FH
ADD A, B
MOV 61H, A


MOV P1, #0A0H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV A, P1
ANL A, #0FH
SWAP A


MOV P1, #60H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV B, P1
ANL B, #0FH
ADD A, B
MOV 62H, A


MOV P1, #0E0H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV A, P1
ANL A, #0FH
SWAP A


MOV P1, #10H
SETB P1.3
SETB P1.2
SETB P1.1
SETB P1.0
CALL DELAY_10S
MOV B, P1
ANL B, #0FH
ADD A, B
MOV 63H, A
RET


QUANT_ENC:
JNC INITIALIZE
RET

INITIALIZE:
MOV R2, #05H
MOV R0, #60H
MOV R1, #64H

QUANT_LOOP:
DJNZ R2, QUANT1
MOV R0, #70H
MOV R1, #64H
MOV R2, #05H

ENCODE_LOOP:
DJNZ R2, ENCODE1
SETB C
JMP QUANT_ENC

QUANT1:
MOV A, @R0
SUBB A, #0AH
MOV R3, #05H
JC STORE_QUANT

QUANT2:
MOV A, @R0
SUBB A, #14H
MOV R3, #0FH
JC STORE_QUANT

QUANT3:
MOV A, @R0
SUBB A, #1EH
MOV R3, #19H
JC STORE_QUANT

QUANT4:
MOV R3, #23H
JMP STORE_QUANT

STORE_QUANT:
CLR C
MOV A, R3
MOV @R1, A
INC R0
INC R1
JMP QUANT_LOOP

ENCODE1:
MOV A, @R1
SUBB A, #05H
MOV R3, #80H
JZ STORE_ENC

ENCODE2:
MOV A, @R1
SUBB A, #0FH
MOV R3, #40H
JZ STORE_ENC

ENCODE3:
MOV A, @R1
SUBB A, #19H
MOV R3, #20H
JZ STORE_ENC

ENCODE4:
MOV A, @R1
SUBB A, #23H
MOV R3, #10H
JZ STORE_ENC

STORE_ENC:
MOV A, R3
MOV @R0, A
INC R0
INC R1
JMP ENCODE_LOOP


LED_DISP:
MOV R2, #01H
MOV R0, #70H
MOV R1, #05H
CJNE R2, #00H, DISP_LOOP

DISP_LOOP:
DJNZ R1, DISP
JMP LED_DISP

DISP:
MOV P1, @R0
INC R0
CALL DELAY_5S
JMP DISP_LOOP

RET
END