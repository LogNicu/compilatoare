	.file	"ex1.c"
	.option pic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	f1
	.type	f1, @function
f1:
.LFB0:
	.cfi_startproc
	li	a0,45
	ret
	.cfi_endproc
.LFE0:
	.size	f1, .-f1
	.align	1
	.globl	f2
	.type	f2, @function
f2:
.LFB1:
	.cfi_startproc
	addiw	a0,a0,2
	ret
	.cfi_endproc
.LFE1:
	.size	f2, .-f2
	.align	1
	.globl	f3
	.type	f3, @function
f3:
.LFB2:
	.cfi_startproc
	li	a5,2
	subw	a0,a5,a0
	ret
	.cfi_endproc
.LFE2:
	.size	f3, .-f3
	.align	1
	.globl	f4
	.type	f4, @function
f4:
.LFB3:
	.cfi_startproc
	li	a5,1375
	mulw	a0,a5,a0
	ret
	.cfi_endproc
.LFE3:
	.size	f4, .-f4
	.align	1
	.globl	f5
	.type	f5, @function
f5:
.LFB4:
	.cfi_startproc
	li	a5,6
	divw	a0,a5,a0
	ret
	.cfi_endproc
.LFE4:
	.size	f5, .-f5
	.align	1
	.globl	f6
	.type	f6, @function
f6:
.LFB5:
	.cfi_startproc
	negw	a0,a0
	ret
	.cfi_endproc
.LFE5:
	.size	f6, .-f6
	.ident	"GCC: (Ubuntu 13.2.0-4ubuntu3) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
