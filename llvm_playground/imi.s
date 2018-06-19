	.text
	.file	"my cool jit"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %god_see
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	callq	readline
	movq	%rax, 16(%rsp)
	movl	(%rax), %ecx
	addl	%ecx, %ecx
	movl	%ecx, (%rax)
	movq	%rax, %rdi
	callq	printss
	movl	$100, 12(%rsp)
	callq	readint
                                        # kill: def %eax killed %eax def %rax
	leal	100(%rax), %edi
	callq	refint
	addq	$40, %rsp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function

	.section	".note.GNU-stack","",@progbits
