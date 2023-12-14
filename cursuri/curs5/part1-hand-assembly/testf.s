
.global f1
f1:
	sub	r1, r1, #1
	mul	r0, r1, r0
	bx	lr



.global f2
f2:
	add	r0, r0, r1
	add	r0, r0, r2
	add	r0, r0, r3
	ldr r5, [sp]
	add r0, r0, r5
	ldr r5, =752
	mul r0, r5, r0 
	bx	lr
.global f3
f3:
	add r0, r0, r1
	add r0, r0, r2
	add r0, r0, r3
	ldr r4, [sp]
	add r0, r0, r4
	ldr r5, [sp, #4]
	add r0, r0, r5
	ldr r5, =752
	mul r0, r5
	bx lr

.global f4
f4:
	sub sp, sp, #4
	str lr, [sp]
	add r0, r0, r1
	add r0, r0, r2
	add r0, r0, r3
	ldr r4, [sp,#4]
	add r0, r0, r4
	ldr r5, [sp, #8]
	add r0, r0, r5
	ldr r1, =752
	bl f1
	ldr lr, [sp]
	add sp, sp, #4
	bx lr

.global f5
f5:
	sub sp, sp, #4
	str lr, [sp]
//do nothing for r0,r1
	add r2, r0, #5
	add r3, r1, #5

	add r12, r0, #7
	sub sp,sp, #4
	str r12, [sp]

	add r12, r1, #7
	sub sp,sp, #4
	str r12, [sp]
	bl f1
	//pop stack of callee ?
	add sp,sp, #8

	ldr lr, [sp]
	add sp, sp, #4
	bx lr



