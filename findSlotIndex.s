/*
 * Filename: findSlotIndex.s
 * Author: Matt Roth 
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of Help: Textbook, lecture notes, and discussion section notes.
 *
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	
	.global	findSlotIndex		@ Specify findSlotIndex as a global 
					@ symbol

@ Allocate space on the stack for local variables 
	
	@ Local variables 	
	.equ	LOCAL_SPACE, 8		@ allocate space for the local variables
	
	@ Formal parameters
	.equ	PARAM_SPACE, 8		@ allocate space for the formal params.
	
	.equ	INDEX_OFFSET, -8	@ allocate space on stack for the index
	.equ	WORD_STR_OFFSET, -12	@ allocate space for the wordStr param
	.equ	NUM_SLOTS_OFFSET, -16	@ allocate space for numSlots
	.text				@ Switch to Text segment 
	.align 2			@ Align on evenly divisible by 4 byte 
					@ address;
					@.align n where 2^n determines alignment
/*
 * Function Name: findSlotIndex()
 * Function Prototype: unsigned int findSlotIndex( const char * wordStr, 
 *							size_t numSlots );
 * Description: This function will calculate the index into the slot array for 
 *		the string wordStr in a slot array of size numSlots. 
 * Parameters: wordStr - the word to calculate for slot index.
 *	       numSlots - size of slot array.	
 * Side Effects: The index of wordStr is calculated.
 * Error Conditions: None. 
 * Return Value: The index of wordStr in the slot array.
 *
 * Registers used:
 *	r0 - arg 1 -- the parametr wordStr.
 *	r1 - arg 2 -- the parameter numSlots.
 * Stack Variables:
 *	wordStr   --  the string to compute hash and find index
 *	index     --  the index to calculate
 *	numSlots  --  the number of slots in the table 
 */

findSlotIndex:
@ Standard prologue
 	push	{fp, lr}			@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET		@ Set fp to base of saved 
						@ registers Uses 4, from 
						@ (#_of_regs_saved - 1)*4.

@ Allocate space for the local variable
	sub	sp, sp, LOCAL_SPACE		@ allocate space for the local 
						@ variable on the stack

@ Allocate space for the formal parameters
	sub	sp, sp, PARAM_SPACE		@ allocate space for the 
						@ parameters on the stack
	str	r0, [fp, WORD_STR_OFFSET]	@ store the wordStr in memory
	str	r1, [fp, NUM_SLOTS_OFFSET]	@ store the numSlots in memory

@ call function computeHash to obtain the hash index
@ index = computeHash( wordStr );
	ldr	r0, [fp, WORD_STR_OFFSET]	@ get the address of wordStr
	
	bl	computeHash			@ computeHash( wordStr );
	str	r0, [fp, INDEX_OFFSET]		@ store the return value of 
						@ compute has in the index
@ index = myURem( index, numSlots )
	ldr	r1, [fp, NUM_SLOTS_OFFSET]	@ get the value of numSlots
	bl	myURem				@ myURem( index, numSlots );

	str	r0, [fp, INDEX_OFFSET]		@ index = return value of myURem

@ Standard epilogue
	sub	sp, fp, FP_OFFSET		@ Set sp to top of saved 
						@ registers
	pop	{fp, pc}			@ Restore fp; restore lr into pc
						@ for return 
