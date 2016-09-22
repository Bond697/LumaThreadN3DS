.cpu arm946e-s
.arch armv5te

@------------------------------------------------------------------------------
@ ARM functions
@------------------------------------------------------------------------------   
.text
.arm
.align 2
.global cp15_operations
.type cp15_operations STT_FUNC
cp15_operations:
    PUSH    {R4-R11, LR}
    LDR     R4, =0x10000037
    LDR     R8, =0x33333333
    LDR     R9, =0x66666666
    MCR     p15, 0, R4,c6,c3, 0
    MCR     p15, 0, R8,c5,c0, 2
    MCR     p15, 0, R9,c5,c0, 3
    POP     {R4-R11, PC}
.pool


.text
.arm
.align 2
.global call_cp15
.type call_cp15 STT_FUNC
call_cp15:
	ldr r0, =cp15_operations
	svc 0x7B
	bx lr
.pool