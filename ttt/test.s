	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_getErrorStr            ## -- Begin function getErrorStr
	.p2align	4, 0x90
_getErrorStr:                           ## @getErrorStr
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	leaq	L_.str(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %edi
	subl	$1, %edi
	movl	%edi, -20(%rbp)         ## 4-byte Spill
	jne	LBB0_2
	jmp	LBB0_1
LBB0_1:
	leaq	L_.str.1(%rip), %rax
	movq	%rax, -16(%rbp)
LBB0_2:
	movq	-16(%rbp), %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$1, %edi
	callq	_getErrorStr
	movq	%rax, -24(%rbp)
	leaq	L_.str.2(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	L_.str.3(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	L_.str.4(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	L_.str.5(%rip), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rsi
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%ecx, %ecx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"unknown"

L_.str.1:                               ## @.str.1
	.asciz	"bad data"

L_.str.2:                               ## @.str.2
	.asciz	"sdsdsdsdsdsdsdsdsd"

L_.str.3:                               ## @.str.3
	.asciz	"sdsdsdsdsdsdsdsdsd1"

L_.str.4:                               ## @.str.4
	.asciz	"sdsdsdsdsdsdsdsdsd2"

L_.str.5:                               ## @.str.5
	.asciz	"sdsdsdsdsdsdsdsdsd3"

L_.str.6:                               ## @.str.6
	.asciz	"%s\n"


.subsections_via_symbols
