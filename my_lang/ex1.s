	.file	"ex1.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	f1
	.type	f1, @function
f1:
	li	a0,45
	ret
	.size	f1, .-f1
	.align	1
	.globl	f2
	.type	f2, @function
f2:
	addiw	a0,a0,2
	ret
	.size	f2, .-f2
	.align	1
	.globl	f3
	.type	f3, @function
f3:
	li	a5,2
	subw	a0,a5,a0
	ret
	.size	f3, .-f3
	.align	1
	.globl	f4
	.type	f4, @function
f4:
	li	a5,1375
	mulw	a0,a5,a0
	ret
	.size	f4, .-f4
	.align	1
	.globl	f5
	.type	f5, @function
f5:
	li	a5,6
	divw	a0,a5,a0
	ret
	.size	f5, .-f5
	.align	1
	.globl	f6
	.type	f6, @function
f6:
	negw	a0,a0
	ret
	.size	f6, .-f6
	.ident	"GCC: () 10.2.0"
