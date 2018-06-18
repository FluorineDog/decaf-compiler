	.text
	.file	"sample.c"
	.globl	get42                   # -- Begin function get42
	.p2align	4, 0x90
	.type	get42,@function
get42:                                  # @get42
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$42, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	get42, .Lfunc_end0-get42
	.cfi_endproc
                                        # -- End function

	.ident	"clang version 6.0.0 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
