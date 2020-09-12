/*
 * Filename: compareWordData.s
 * Author: Matt Roth 
 * UserId: cs30xgs
 * Date: May 22nd, 2019
 * Sources of Help: Textbook, lecture notes, and discussion section notes.
 *
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax
	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	.global	compareWordData		@ Specify compareWordData as a global 
					@ symbol

@ Allocate space on the stack for local variables 
	.equ	LOCAL_SPACE, 8		@ allocate space for two local variables
	.equ	RETURN_VAL_OFFSET, -8	@ Allocate space for return_value
	.equ	STR_CMP_OFFSET, -12	@ Allocate space for str_cmp
	.equ	MAX_WORD_SIZE, 48	@ define the constant MAX_WORD_SIZE

	.text				@ Switch to Text segment 
	.align 2			@ Align on evenly divisible by 4 byte 
					@ address;
					@.align n where 2^n determines alignment
/*
 * Function Name: compareWordData()
 * Function Prototype: int compareWordData( const void * w1, const void * w2 );
 * Description: This function takes two void pointers in its signature, but your
 * 		will pass in wordData_t pointers (const wordData_t *)  and 
 *		compare them. 
 * Parameters: w1 - The first void pointer.
 *	       w2 - The second void pointer.	
 * Side Effects: None.
 * Error Conditions: None. 
 * Return Value: -1 if w1 pointer is a smaller hashValue then w2 pointer 
 *		  hashValue. 1 if the w1 pointer has larger hashValue than w2
 *		  0 if the hashValues are the same but strncmp returns 0.
 *
 * Registers used:
 *	r0 	- arg 1	-- the parameter w1 a pointer to wordData_t. 
 *	r1 	- arg 2	-- the parameter w2 a pointer to wordData_t.
 *	r2 	-    	-- a computational register.
 *	r3 	-   	-- a computational register.
 *
 * Stack variables:
 *	return_value	-- the return value from the comparison of the structs
 *	str_cmp		-- the return value from the strncmp 
 *
 */

compareWordData:
@ Standard prologue
 	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	
						@ Set fp to base of saved 
						@ registers Uses 4, from 
						@ (#_of_regs_saved - 1)*4.

@ Allocate space for the local variables on stack

	sub	sp, sp, LOCAL_SPACE		@ Allocate space for local vars.
	
@ if( w1->hashValue < w2->hashValue )
@	return_value = -1;
	ldr	r3, =G_HASHVALUE_OFFSET		@ get the address of the global
	ldr	r3, [r3]			@ variable hashValue, then get
	ldr	r3, [r0, r3]			@ get the value in the w1 struct
	ldr	r2, =G_HASHVALUE_OFFSET		@ get the hashvalue from w1
	ldr	r2, [r2]			@ get the offset of the hash
	ldr	r2, [r1, r2]			@ get the hashvalue from w2
	cmp	r3, r2				@ if (w1 >= w2) branch to next 
	bhs	if_greater_than			@ branch to next if check
	
	mov	r3, -1				@ load the register with -1
	str	r3, [fp, RETURN_VAL_OFFSET]	@ set the return value to -1
	b	return				@ branch to equals to return 

@ if( w1->hashValue > w2->hashValue )
@	return_value = 1;
if_greater_than:
	ldr	r3, =G_HASHVALUE_OFFSET		@ get the address of the global
	ldr	r3, [r3]			@ variable hashValue, then get
	ldr	r3, [r0, r3]			@ get the value in the w1 struct
	ldr	r2, =G_HASHVALUE_OFFSET		@ get the hashvalue from w1
	ldr	r2, [r2]			@ get the offset of the hash
	ldr	r2, [r1, r2]			@ get the hashvalue from w2
	cmp	r3, r2				@ if (w1 == w2) branch to next
	beq	if_equal			@ branch is the values are equal
	
	mov	r3, 1				@ load the register with 1
	str	r3, [fp, RETURN_VAL_OFFSET]	@ store the return value with 1
	b	return				@ branch to return 

@ if( w1->hashValue == w2->hashValue )
@	str_cmp = strncmp(w1->word, w2->word, MAX_WORD_SIZE) {
@		if( str_cmp < 0 ) {
@			return_value = -1;
@		}
@		if( str_cmp > 0 ) {
@			return_value = 1;
@		}
@		if( str_cmp == 0) {
@			return_value = 0;
@		}

if_equal:
	ldr	r3, =G_WORD_OFFSET		@ get the address of the word 
						@ offset
	ldr	r3, [r3]			@ get the offset of word in w1
	ldr	r2, =G_WORD_OFFSET		@ get the address of the word 
						@ offset
	ldr	r2, [r2]			@ get the offset of the word w2
	mov	r2, MAX_WORD_SIZE		@ get the value from MACRO MAX_

	bl	strncmp				@ call strncmp( w1->word, 
						@ w2->word, 
	str	r0, [fp, STR_CMP_OFFSET]	@ 	MAX_WORD_SIZE)

@ if( str_cmp < 0 )
	ldr	r3, [fp, STR_CMP_OFFSET]	@ get the value for str_cmp
	cmp	r3, 0				@ if( str_cmp >= 0 )
	bge	if_str_greater_than		@ branch to if( str_cmp > 0)
	
	mov	r3, -1				@ load the return value in r3
	str	r3, [fp, RETURN_VAL_OFFSET]	@ store the new return value
	b	return				@ branch to the return 
@ if( str_cmp > 0) 
if_str_greater_than:
	ldr	r3, [fp, STR_CMP_OFFSET]	@ get the value for str_cmp
	cmp	r3, 0				@ if( str_cmp == 0 )
	beq	if_str_equal			@ branch if the str value is 0

	mov	r3, 1				@ load the return value with 1
	str	r3, [fp, RETURN_VAL_OFFSET]	@ store the new return value
	b	return				@ branch to function return

@ if( str_cmp == 0)
if_str_equal:
	mov	r3, 0				@ load the return value with 0
	str	r3, [fp, RETURN_VAL_OFFSET]	@ store the new return value

@ return the value of comparison
return:
	ldr	r0, [fp, RETURN_VAL_OFFSET]	@ load the return value into r0

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved 
						@ registers
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@ for return 
