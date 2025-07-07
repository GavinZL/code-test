	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 3
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 155, ___gxx_personality_v0
	.cfi_lsda 16, Lexception0
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movl	$0, -4(%rbp)
	callq	_objc_autoreleasePoolPush
	movq	%rax, -56(%rbp)                 ## 8-byte Spill
	movl	$8, -8(%rbp)
	movl	$6, -12(%rbp)
	movq	_OBJC_CLASSLIST_REFERENCES_$_(%rip), %rdi
	callq	_objc_alloc
	movq	%rax, %rdi
	movq	_OBJC_SELECTOR_REFERENCES_(%rip), %rsi
	leaq	L_.str(%rip), %rdx
	movq	_objc_msgSend@GOTPCREL(%rip), %rax
	callq	*%rax
	movq	%rax, -24(%rbp)
	movl	-8(%rbp), %eax
	movl	-12(%rbp), %ecx
	addl	%ecx, %eax
	movl	%eax, -28(%rbp)
	movq	-24(%rbp), %rsi
	movl	-28(%rbp), %edx
Ltmp0:
	leaq	L__unnamed_cfstring_(%rip), %rdi
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	callq	_NSLog
Ltmp1:
	jmp	LBB0_1
LBB0_1:
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	_objc_storeStrong
	movq	-56(%rbp), %rdi                 ## 8-byte Reload
	callq	_objc_autoreleasePoolPop
	xorl	%eax, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
LBB0_2:
Ltmp2:
	movq	%rax, %rcx
	movl	%edx, %eax
	movq	%rcx, -40(%rbp)
	movl	%eax, -44(%rbp)
	leaq	-24(%rbp), %rdi
	xorl	%eax, %eax
	movl	%eax, %esi
	callq	_objc_storeStrong
## %bb.3:
	movq	-40(%rbp), %rdi
	callq	__Unwind_Resume
Lfunc_end0:
	.cfi_endproc
	.section	__TEXT,__gcc_except_tab
	.p2align	2
GCC_except_table0:
Lexception0:
	.byte	255                             ## @LPStart Encoding = omit
	.byte	255                             ## @TType Encoding = omit
	.byte	1                               ## Call site Encoding = uleb128
	.uleb128 Lcst_end0-Lcst_begin0
Lcst_begin0:
	.uleb128 Lfunc_begin0-Lfunc_begin0      ## >> Call Site 1 <<
	.uleb128 Ltmp0-Lfunc_begin0             ##   Call between Lfunc_begin0 and Ltmp0
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp0-Lfunc_begin0             ## >> Call Site 2 <<
	.uleb128 Ltmp1-Ltmp0                    ##   Call between Ltmp0 and Ltmp1
	.uleb128 Ltmp2-Lfunc_begin0             ##     jumps to Ltmp2
	.byte	0                               ##   On action: cleanup
	.uleb128 Ltmp1-Lfunc_begin0             ## >> Call Site 3 <<
	.uleb128 Lfunc_end0-Ltmp1               ##   Call between Ltmp1 and Lfunc_end0
	.byte	0                               ##     has no landing pad
	.byte	0                               ##   On action: cleanup
Lcst_end0:
	.p2align	2
                                        ## -- End function
	.section	__DATA,__objc_classrefs,regular,no_dead_strip
	.p2align	3                               ## @"OBJC_CLASSLIST_REFERENCES_$_"
_OBJC_CLASSLIST_REFERENCES_$_:
	.quad	_OBJC_CLASS_$_NSString

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"starming"

	.section	__TEXT,__objc_methname,cstring_literals
L_OBJC_METH_VAR_NAME_:                  ## @OBJC_METH_VAR_NAME_
	.asciz	"initWithUTF8String:"

	.section	__DATA,__objc_selrefs,literal_pointers,no_dead_strip
	.p2align	3                               ## @OBJC_SELECTOR_REFERENCES_
_OBJC_SELECTOR_REFERENCES_:
	.quad	L_OBJC_METH_VAR_NAME_

	.section	__TEXT,__cstring,cstring_literals
L_.str.1:                               ## @.str.1
	.asciz	"%@ rank %d"

	.section	__DATA,__cfstring
	.p2align	3                               ## @_unnamed_cfstring_
L__unnamed_cfstring_:
	.quad	___CFConstantStringClassReference
	.long	1992                            ## 0x7c8
	.space	4
	.quad	L_.str.1
	.quad	10                              ## 0xa

	.section	__DATA,__objc_imageinfo,regular,no_dead_strip
L_OBJC_IMAGE_INFO:
	.long	0
	.long	64

.subsections_via_symbols
