	.arch msp430g2553
	.p2align 1,0
	.data
state:
	.word 1
	.text
jt:
	.word default
	.word Case0
	.word Case1
	.word Case2
	.word Case3

	.global toggle
toggle:
	mov &state,r12
	cmp #5,r12     		;State-5
	jhs default
	add r12,r12		;2*State
	mov jt(r12),r0

Case0:
	mov.b #0, &red_on
	mov.b #0, &green_on
	add #1, &state
	jmp end

Case1:
	mov.b #0, &red_on
	mov.b #1, &green_on
	add #1, &state
	jmp end

Case2:
	mov.b #1, &red_on
	mov.b #0, &green_on
	add #1, &state
	jmp end
	
Case3:
	mov.b #1, &red_on
	mov.b #1, &green_on
	mov.b #1, &state
	jmp end

default:
	mov.b #0, &red_on
	mov.b #0, &green_on
	mov.b #1, &state
	jmp end
	
end:

	pop r0

	
