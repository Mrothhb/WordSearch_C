/*
 * Filename: computeHash.s
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
	
	.global	computeHash		@ Specify computeHash as a global symbol

@ Allocate space for the local variables and fromal parameters
	.equ	LOCAL_SPACE, 8		@ allocate space for 4 bytes
	.equ	PARAM_SPACE, 8		@ allocate space for 4 bytes
	.equ	I_OFFSET, -8		@ allocate space for i 
	.equ	HASH_OFFSET, -12	@ allocate space for the hash value
	.equ	STR_OFFSET, -16		@ allocate space for the str parameter
	
@ Constants ;

	.equ	NULL_CHAR, 0		@ the constant for the '\0'
	.text				@ Switch to Text segment 
	.align 2			@ Align on evenly divisible by 4 byte 
					@ address;
					@ .align n where 2^n determines
					@ alignment
/*
 * Function Name: computerHash()
 * Function Prototype: unsigned int computeHash( const char * str );
 * Description: This function will be used to create the hash value of a string.
 *		This function creates an unsigned integer hash value from str
 *		with the following hashing algorithm. 
 * Parameters: str -  the the string to create a hash value from. 
 * Side Effects: The hash value is computed and returned. 
 * Error Conditions: return -1 if failure to compute the hash value of str. 
 * Return Value: the hash value of str.
 *
 * Registers used:
 *	r0 - arg 1 -- the parameter str, used for the hash value
 *	r1 - 	   -- computatational register. 
 *	r3 - 	   -- computational register. 
 *
 * Stack variables:
 *	i 	-- The "i" for the loop iterator.
 *	hash	-- The hash value.
 *	str	-- The formal parameter string to compute for a hash value.
 */

computeHash:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
					@ Uses 4, from (#_of_regs_saved - 1)*4.

@ Check if the argument string is Null
	cmp	r0, 0			@ check if( str == NULL )
	beq	epilogue		@ branch before allocating stack space

@ Allocate space for the local variables
	sub	sp, sp, LOCAL_SPACE	@ allocate space for the local variable
	ldr	r3, =G_HASH_START_VAL	@ get the address of the global variable
	ldr	r3, [r3]		@ get the value of the global variable
	str	r3, [fp, HASH_OFFSET]	@ store the new value in hash
@ i = 0;
	mov	r3, 0			@ get the value 0 ready to store in i
	str	r3, [fp, I_OFFSET]	@ store i = 0;  in memory

@ Allocate space for the formal paramter
	sub	sp, sp, PARAM_SPACE	@ allocate space for the parameters
	str	r0, [fp, STR_OFFSET]	@ store the address of str in memory

@ Begin the for loop for the function computation
	ldr	r3, [fp, I_OFFSET]	@ get the current value of i
	ldr	r0, [fp, STR_OFFSET]	@ get the value of str[0]
	ldrb	r0, [r0, r3]		@ get the first character in the string
	mov	r1, NULL_CHAR		@ move the '\0' into r1
	cmp	r0, r1			@ str[i] == '\0'
	beq	end_loop		@ branch to the end of the loop

loop:
@ hash = hash * HASH_PRIME + str[i];
	ldr	r3, [fp, HASH_OFFSET]	@ get the value of hash
	ldr	r0, =G_HASH_PRIME	@ load the r0 with the HASH_PRIME value
	ldr	r0, [r0]		@ get the value of HASH_PRIME 
	mul	r3, r3, r0		@ hash * HASH_PRIME
	ldr	r1, [fp, I_OFFSET]	@ get the current value of i
	ldr	r0, [fp, STR_OFFSET]	@ get the address of the str param
	ldrb	r0, [r0, r1]		@ get the value of str[i]
	add	r3, r3, r0		@ hash * HASH_PRIME + str[i]
	str	r3, [fp, HASH_OFFSET]	@ store the new value in hash

@ loop condition check 
	ldr	r3, [fp, I_OFFSET] 	@ get the current value of i 
	add	r3, r3, 1		@ i = i + 1;
	str	r3, [fp, I_OFFSET]	@ store the new value of i

	ldr	r0, [fp, STR_OFFSET]	@ get the address of the str
	ldrb	r0, [r0, r3]		@ get the value of str[i]
	mov	r1, NULL_CHAR		@ move the '\0' into r1
	cmp	r0, r1			@ str[i] != '\0'
	bne	loop			@ str[i] != '\0' then branch to loop 

@ End of loop
end_loop:
	
	ldr	r0, [fp, HASH_OFFSET]	@ get the current value of hash

@ Standard epilogue
epilogue:

	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@  return 
