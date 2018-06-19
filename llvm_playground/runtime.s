	.text
	.file	"runtime.c"
	.globl	readint                 # -- Begin function readint
	.p2align	4, 0x90
	.type	readint,@function
readint:                                # @readint
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	leaq	-12(%rbp), %rsi
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	__isoc99_scanf
	movl	-12(%rbp), %esi
	movl	$.L.str.1, %edi
	xorl	%eax, %eax
	callq	printf
	movl	-12(%rbp), %eax
	movq	%fs:40, %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	.LBB0_2
# %bb.1:                                # %SP_return
	addq	$16, %rsp
	popq	%rbp
	retq
.LBB0_2:                                # %CallStackCheckFailBlk
	callq	__stack_chk_fail
.Lfunc_end0:
	.size	readint, .Lfunc_end0-readint
	.cfi_endproc
                                        # -- End function
	.globl	dog_malloc              # -- Begin function dog_malloc
	.p2align	4, 0x90
	.type	dog_malloc,@function
dog_malloc:                             # @dog_malloc
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movslq	-4(%rbp), %rdi
	callq	malloc
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	dog_malloc, .Lfunc_end1-dog_malloc
	.cfi_endproc
                                        # -- End function
	.globl	readline                # -- Begin function readline
	.p2align	4, 0x90
	.type	readline,@function
readline:                               # @readline
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$100, %edi
	callq	malloc
	movabsq	$.L.str.2, %rdi
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rsi
	movb	$0, %al
	callq	__isoc99_scanf
	movl	$16, %edi
	callq	dog_malloc
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rax, (%rcx)
	movq	-16(%rbp), %rdi
	callq	strlen
	movq	-8(%rbp), %rcx
	movl	%eax, 8(%rcx)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end2:
	.size	readline, .Lfunc_end2-readline
	.cfi_endproc
                                        # -- End function
	.globl	string_cat              # -- Begin function string_cat
	.p2align	4, 0x90
	.type	string_cat,@function
string_cat:                             # @string_cat
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -32(%rbp)
	movq	%rsi, -24(%rbp)
	cmpq	$0, -32(%rbp)
	je	.LBB3_2
# %bb.1:
	jmp	.LBB3_3
.LBB3_2:
	movabsq	$.L.str.3, %rdi
	movabsq	$.L.str.4, %rsi
	movabsq	$.L__PRETTY_FUNCTION__.string_cat, %rcx
	movl	$32, %edx
	callq	__assert_fail
.LBB3_3:
	cmpq	$0, -24(%rbp)
	je	.LBB3_5
# %bb.4:
	jmp	.LBB3_6
.LBB3_5:
	movabsq	$.L.str.5, %rdi
	movabsq	$.L.str.4, %rsi
	movabsq	$.L__PRETTY_FUNCTION__.string_cat, %rcx
	movl	$33, %edx
	callq	__assert_fail
.LBB3_6:
	movq	-32(%rbp), %rax
	movl	8(%rax), %eax
	movq	-24(%rbp), %rcx
	addl	8(%rcx), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edi
	addl	$1, %edi
	callq	dog_malloc
	movq	%rax, -40(%rbp)
	movl	$16, %edi
	callq	dog_malloc
	movq	%rax, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	%rax, (%rcx)
	movl	-4(%rbp), %eax
	movq	-16(%rbp), %rcx
	movl	%eax, 8(%rcx)
	movq	-16(%rbp), %rax
	addq	$48, %rsp
	popq	%rbp
	retq
.Lfunc_end3:
	.size	string_cat, .Lfunc_end3-string_cat
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"tmp=%d"
	.size	.L.str.1, 7

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"%s"
	.size	.L.str.2, 3

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"a"
	.size	.L.str.3, 2

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"runtime.c"
	.size	.L.str.4, 10

	.type	.L__PRETTY_FUNCTION__.string_cat,@object # @__PRETTY_FUNCTION__.string_cat
.L__PRETTY_FUNCTION__.string_cat:
	.asciz	"string *string_cat(string *, string *)"
	.size	.L__PRETTY_FUNCTION__.string_cat, 39

	.type	.L.str.5,@object        # @.str.5
.L.str.5:
	.asciz	"b"
	.size	.L.str.5, 2


	.ident	"clang version 6.0.0 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
