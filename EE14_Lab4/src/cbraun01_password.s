	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"cbraun01_password.c"
	.text
	.align	1
	.global	UART_write_byte
	.syntax unified
	.thumb
	.thumb_func
	.type	UART_write_byte, %function
UART_write_byte:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L2:
	ldr	r3, [r0, #28]
	tst	r3, #128
	beq	.L2
	strh	r1, [r0, #40]	@ movhi
	bx	lr
	.size	UART_write_byte, .-UART_write_byte
	.align	1
	.global	host_serial_init
	.syntax unified
	.thumb
	.thumb_func
	.type	host_serial_init, %function
host_serial_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L9
	ldr	r3, [r2, #88]
	orr	r3, r3, #131072
	str	r3, [r2, #88]
	ldr	r3, [r2, #136]
	bic	r3, r3, #12
	str	r3, [r2, #136]
	ldr	r3, [r2, #136]
	orr	r3, r3, #4
	str	r3, [r2, #136]
	ldr	r3, [r2, #76]
	orr	r3, r3, #1
	str	r3, [r2, #76]
	mov	r3, #1207959552
	ldr	r1, [r3]
	bic	r1, r1, #48
	str	r1, [r3]
	ldr	r1, [r3]
	orr	r1, r1, #32
	str	r1, [r3]
	ldr	r1, [r3, #32]
	bic	r1, r1, #3840
	str	r1, [r3, #32]
	ldr	r1, [r3, #32]
	orr	r1, r1, #1792
	str	r1, [r3, #32]
	ldr	r1, [r3, #8]
	bic	r1, r1, #48
	str	r1, [r3, #8]
	ldr	r1, [r3, #12]
	bic	r1, r1, #48
	str	r1, [r3, #12]
	ldr	r1, [r2, #76]
	orr	r1, r1, #1
	str	r1, [r2, #76]
	ldr	r2, [r3]
	bic	r2, r2, #-1073741824
	str	r2, [r3]
	ldr	r2, [r3]
	orr	r2, r2, #-2147483648
	str	r2, [r3]
	ldr	r2, [r3, #36]
	bic	r2, r2, #-268435456
	str	r2, [r3, #36]
	ldr	r2, [r3, #36]
	orr	r2, r2, #805306368
	str	r2, [r3, #36]
	ldr	r2, [r3, #8]
	bic	r2, r2, #-1073741824
	str	r2, [r3, #8]
	ldr	r2, [r3, #12]
	bic	r2, r2, #-1073741824
	str	r2, [r3, #12]
	ldr	r2, [r3, #8]
	orr	r2, r2, #-1073741824
	orr	r2, r2, #48
	str	r2, [r3, #8]
	ldr	r2, [r3, #12]
	bic	r2, r2, #-1073741824
	bic	r2, r2, #48
	str	r2, [r3, #12]
	ldr	r2, [r3, #12]
	orr	r2, r2, #1073741824
	orr	r2, r2, #16
	str	r2, [r3, #12]
	ldr	r2, [r3, #4]
	bic	r2, r2, #-1073741824
	bic	r2, r2, #48
	str	r2, [r3, #4]
	ldr	r3, .L9+4
	ldr	r2, [r3]
	bic	r2, r2, #1
	str	r2, [r3]
	ldr	r2, [r3]
	bic	r2, r2, #268439552
	str	r2, [r3]
	ldr	r2, [r3, #4]
	bic	r2, r2, #12288
	str	r2, [r3, #4]
	ldr	r2, .L9+8
	ldr	r2, [r2]
	ldr	r1, .L9+12
	umull	r1, r2, r1, r2
	lsrs	r2, r2, #10
	str	r2, [r3, #12]
	ldr	r2, [r3]
	bic	r2, r2, #32768
	str	r2, [r3]
	ldr	r2, [r3]
	orr	r2, r2, #8
	str	r2, [r3]
	ldr	r2, [r3]
	orr	r2, r2, #4
	str	r2, [r3]
	ldr	r2, [r3]
	orr	r2, r2, #1
	str	r2, [r3]
	mov	r2, r3
.L5:
	ldr	r3, [r2, #28]
	tst	r3, #2097152
	beq	.L5
	ldr	r2, .L9+4
.L6:
	ldr	r3, [r2, #28]
	tst	r3, #4194304
	beq	.L6
	bx	lr
.L10:
	.align	2
.L9:
	.word	1073876992
	.word	1073759232
	.word	SystemCoreClock
	.word	458129845
	.size	host_serial_init, .-host_serial_init
	.align	1
	.global	serial_write
	.syntax unified
	.thumb
	.thumb_func
	.type	serial_write, %function
serial_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r0
	cbz	r2, .L14
	mov	r6, r2
	subs	r4, r1, #1
	add	r6, r6, r4
.L13:
	ldrb	r1, [r4, #1]!	@ zero_extendqisi2
	mov	r0, r5
	bl	UART_write_byte
	cmp	r4, r6
	bne	.L13
.L14:
	ldr	r3, [r5, #28]
	tst	r3, #64
	beq	.L14
	ldr	r3, [r5, #28]
	bic	r3, r3, #64
	str	r3, [r5, #28]
	pop	{r4, r5, r6, pc}
	.size	serial_write, .-serial_write
	.align	1
	.global	serial_read
	.syntax unified
	.thumb
	.thumb_func
	.type	serial_read, %function
serial_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
.L19:
	ldr	r3, [r0, #28]
	tst	r3, #32
	beq	.L19
	ldrh	r0, [r0, #36]
	uxtb	r0, r0
	bx	lr
	.size	serial_read, .-serial_read
	.align	1
	.global	_write
	.syntax unified
	.thumb
	.thumb_func
	.type	_write, %function
_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r2
	ldr	r0, .L23
	bl	serial_write
	mov	r0, r4
	pop	{r4, pc}
.L24:
	.align	2
.L23:
	.word	1073759232
	.size	_write, .-_write
	.align	1
	.global	serial_read_line
	.syntax unified
	.thumb
	.thumb_func
	.type	serial_read_line, %function
serial_read_line:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r8, r0
	subs	r5, r0, #1
	movs	r4, #0
	subs	r6, r1, #1
	ldr	r7, .L35
.L27:
	cmp	r6, r4
	ble	.L33
	mov	r0, r7
	bl	serial_read
	cmp	r0, #13
	beq	.L27
	cmp	r0, #10
	beq	.L34
	strb	r0, [r5, #1]!
	adds	r4, r4, #1
	b	.L27
.L34:
	movs	r3, #0
	strb	r3, [r8, r4]
	b	.L25
.L33:
	movs	r3, #0
	strb	r3, [r8, r4]
.L25:
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, pc}
.L36:
	.align	2
.L35:
	.word	1073759232
	.size	serial_read_line, .-serial_read_line
	.align	1
	.global	blink_hello
	.syntax unified
	.thumb
	.thumb_func
	.type	blink_hello, %function
blink_hello:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L38
	ldr	r3, [r2, #76]
	orr	r3, r3, #2
	str	r3, [r2, #76]
	ldr	r3, .L38+4
	ldr	r2, [r3]
	bic	r2, r2, #192
	str	r2, [r3]
	ldr	r2, [r3]
	orr	r2, r2, #64
	str	r2, [r3]
	ldr	r2, [r3, #20]
	orr	r2, r2, #8
	str	r2, [r3, #20]
	bx	lr
.L39:
	.align	2
.L38:
	.word	1073876992
	.word	1207960576
	.size	blink_hello, .-blink_hello
	.align	1
	.global	deobfuscate
	.syntax unified
	.thumb
	.thumb_func
	.type	deobfuscate, %function
deobfuscate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldrb	r3, [r0]	@ zero_extendqisi2
	cbz	r3, .L43
	subs	r2, r1, #1
.L42:
	mov	ip, r2
	subs	r3, r3, #56
	strb	r3, [r2, #1]!
	ldrb	r3, [r0, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L42
	add	ip, ip, #2
	sub	ip, ip, r1
.L41:
	movs	r3, #0
	strb	r3, [r1, ip]
	bx	lr
.L43:
	mov	ip, #0
	b	.L41
	.size	deobfuscate, .-deobfuscate
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"\210\247\255\246\233\241\246\237\213\240\241\246\241"
	.ascii	"\246\235\253\253\000"
	.align	2
.LC1:
	.ascii	"Hello, Campbell!\000"
	.align	2
.LC2:
	.ascii	"Please enter your super secret lab 4 login:\015\000"
	.align	2
.LC3:
	.ascii	"\213\254\231\252\254\244\241\246\237\213\250\241\246"
	.ascii	"\246\235\252z\231\252\252\235\254\254\235\215\246\233"
	.ascii	"\247\245\232\235\234\000"
	.align	2
.LC4:
	.ascii	"Success!  Your key is\015\000"
	.align	2
.LC5:
	.ascii	"\015\000"
	.align	2
.LC6:
	.ascii	"Password incorrect, please try again.\015\000"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{lr}
	sub	sp, sp, #204
	bl	blink_hello
	bl	host_serial_init
	mov	r1, sp
	ldr	r0, .L51
	bl	deobfuscate
	ldr	r6, .L51+4
	ldr	r5, .L51+8
	movs	r4, #100
.L48:
	mov	r0, r6
	bl	printf
	mov	r0, r5
	bl	puts
	mov	r1, r4
	add	r0, sp, #100
	bl	serial_read_line
	add	r0, sp, #100
	bl	printf
	mov	r2, r4
	add	r1, sp, #100
	mov	r0, sp
	bl	strncmp
	cbz	r0, .L50
	ldr	r0, .L51+12
	bl	puts
	b	.L48
.L50:
	mov	r1, sp
	ldr	r0, .L51+16
	bl	deobfuscate
	ldr	r0, .L51+20
	bl	puts
	mov	r0, sp
	bl	printf
	ldr	r0, .L51+24
	bl	puts
.L47:
	b	.L47
.L52:
	.align	2
.L51:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.word	.LC6
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.size	main, .-main
	.ident	"GCC: (15:13.2.rel1-2) 13.2.1 20231009"
