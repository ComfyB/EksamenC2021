	.arch armv8-a
	.file	"source.c"
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Server"
	.align	3
.LC1:
	.string	"andre if"
	.align	3
.LC2:
	.string	"Content-Type"
	.align	3
.LC3:
	.string	"Content-Length"
	.text
	.align	2
	.global	ProcessHttpHeader
	.type	ProcessHttpHeader, %function
ProcessHttpHeader:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	x0, [sp, 24]
	mov	x0, 48
	bl	malloc
	str	x0, [sp, 40]
	ldr	x0, [sp, 40]
	cmp	x0, 0
	bne	.L2
	mov	x0, 0
	b	.L3
.L2:
	mov	x2, 48
	mov	w1, 0
	ldr	x0, [sp, 40]
	bl	memset
	ldr	x0, [sp, 24]
	add	x0, x0, 8
	bl	atoi
	mov	w1, w0
	ldr	x0, [sp, 40]
	str	w1, [x0]
	ldr	x0, [sp, 40]
	mov	w1, 200
	str	w1, [x0]
	ldr	x0, [sp, 40]
	mov	w1, 1
	strb	w1, [x0, 8]
	adrp	x0, .LC0
	add	x1, x0, :lo12:.LC0
	ldr	x0, [sp, 24]
	bl	strstr
	str	x0, [sp, 32]
	ldr	x0, [sp, 32]
	cmp	x0, 0
	beq	.L4
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
	ldr	x0, [sp, 32]
	add	x0, x0, 6
	str	x0, [sp, 32]
	b	.L5
.L6:
	ldr	x0, [sp, 32]
	add	x0, x0, 1
	str	x0, [sp, 32]
.L5:
	bl	__ctype_b_loc
	ldr	x1, [x0]
	ldr	x0, [sp, 32]
	ldrb	w0, [x0]
	and	x0, x0, 255
	lsl	x0, x0, 1
	add	x0, x1, x0
	ldrh	w0, [x0]
	and	w0, w0, 1024
	cmp	w0, 0
	beq	.L6
	mov	w1, 10
	ldr	x0, [sp, 32]
	bl	strchr
	strb	wzr, [x0]
	ldr	x0, [sp, 40]
	add	x0, x0, 9
	ldr	x1, [sp, 32]
	bl	strcpy
.L4:
	adrp	x0, .LC2
	add	x1, x0, :lo12:.LC2
	ldr	x0, [sp, 24]
	bl	strstr
	str	x0, [sp, 32]
	ldr	x0, [sp, 32]
	cmp	x0, 0
	beq	.L7
	ldr	x0, [sp, 32]
	add	x0, x0, 12
	str	x0, [sp, 32]
	b	.L8
.L9:
	ldr	x0, [sp, 32]
	add	x0, x0, 1
	str	x0, [sp, 32]
.L8:
	bl	__ctype_b_loc
	ldr	x1, [x0]
	ldr	x0, [sp, 32]
	ldrb	w0, [x0]
	and	x0, x0, 255
	lsl	x0, x0, 1
	add	x0, x1, x0
	ldrh	w0, [x0]
	and	w0, w0, 1024
	cmp	w0, 0
	beq	.L9
	mov	w1, 10
	ldr	x0, [sp, 32]
	bl	strchr
	strb	wzr, [x0]
	ldr	x0, [sp, 40]
	add	x0, x0, 25
	mov	x2, 15
	ldr	x1, [sp, 32]
	bl	strncpy
	ldr	x0, [sp, 40]
	add	x0, x0, 25
	bl	strlen
	mov	x1, x0
	ldr	x0, [sp, 32]
	add	x0, x0, x1
	mov	w1, 10
	strb	w1, [x0]
.L7:
	adrp	x0, .LC3
	add	x1, x0, :lo12:.LC3
	ldr	x0, [sp, 24]
	bl	strstr
	str	x0, [sp, 32]
	ldr	x0, [sp, 32]
	cmp	x0, 0
	beq	.L10
	ldr	x0, [sp, 32]
	add	x0, x0, 14
	str	x0, [sp, 32]
	b	.L11
.L12:
	ldr	x0, [sp, 32]
	add	x0, x0, 1
	str	x0, [sp, 32]
.L11:
	bl	__ctype_b_loc
	ldr	x1, [x0]
	ldr	x0, [sp, 32]
	ldrb	w0, [x0]
	and	x0, x0, 255
	lsl	x0, x0, 1
	add	x0, x1, x0
	ldrh	w0, [x0]
	and	w0, w0, 2048
	cmp	w0, 0
	beq	.L12
	ldr	x0, [sp, 24]
	bl	atoi
	mov	w1, w0
	ldr	x0, [sp, 40]
	str	w1, [x0, 4]
.L10:
	ldr	x0, [sp, 40]
.L3:
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	ProcessHttpHeader, .-ProcessHttpHeader
	.section	.rodata
	.align	3
.LC4:
	.string	"GET /pg3401/test.html HTTP/1.1\r\nHost: eastwillsecurity.com\r\nContent-type: text/html\r\ncontent-length: 420 \r\n\r\n\r\n"
	.align	3
.LC5:
	.string	"content-length: %d\n"
	.align	3
.LC6:
	.string	"http - code: %d\n"
	.align	3
.LC7:
	.string	"Is success?: %d\n"
	.align	3
.LC8:
	.string	"Content type: %s\n"
	.align	3
.LC9:
	.string	"Server: %s\n"
	.align	3
.LC10:
	.string	"Last-modified: %d"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	ProcessHttpHeader
	str	x0, [sp, 24]
	ldr	x0, [sp, 24]
	ldr	w0, [x0, 4]
	mov	w1, w0
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	ldr	x0, [sp, 24]
	ldr	w0, [x0]
	mov	w1, w0
	adrp	x0, .LC6
	add	x0, x0, :lo12:.LC6
	bl	printf
	ldr	x0, [sp, 24]
	ldrb	w0, [x0, 8]
	mov	w1, w0
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	printf
	ldr	x0, [sp, 24]
	add	x0, x0, 25
	mov	x1, x0
	adrp	x0, .LC8
	add	x0, x0, :lo12:.LC8
	bl	printf
	ldr	x0, [sp, 24]
	add	x0, x0, 9
	mov	x1, x0
	adrp	x0, .LC9
	add	x0, x0, :lo12:.LC9
	bl	printf
	ldr	x0, [sp, 24]
	ldr	w0, [x0, 44]
	mov	w1, w0
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
	bl	printf
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
