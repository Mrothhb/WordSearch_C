/*
 * Filename: intervalContains.s
 * Author: Matt Roth 
 * UserId: cs30xgs
 * Date: April 17, 2019
 * Sources of Help: Textbook, lecture notes, and discussion section notes.
 *
 */

@ Raspberry Pi directives
	.cpu	cortex-a53		@ Version of our Pis
	.syntax	unified			@ Modern ARM syntax

	.equ	FP_OFFSET, 4		@ Offset from sp to set fp
	
	.global	intervalContains	@ Specify outputChar as a global symbol

	.text				@ Switch to Text segment 
	.align 2			@ Align on evenly divisible by 4 byte 
					@ address;

					@   .align n where 2^n determines
					@ alignment
/*
 * Function Name: intervalContains()
 * Function Prototype: int intervalContains( int start, int end, int value );
 * Description: Determines whether or not value is inside the interval 
 * [start, end] This interval is inclusive on both ends.
 * Parameters: start - the start of the interval 
 * 	       end - the end of the interval
 * Side Effects: None
 * Error Conditions: if start is greater than end, return -1 for error. 
 * Return Value: None.
 *
 * Registers used:
 *	r0 - arg 1 -- start parameter for interval, and return value -1, 0 or 1.
 *	r1 - arg 2 -- end parameter for the interval.
 *	r2 - arg 3 -- the value to find inside of the interval.
 */

intervalContains:
@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
					@ Uses 4, from (#_of_regs_saved - 1)*4.
	cmp	r0, r1			@ comparison between the parameters
	movgt	r0, -1			@ return -1 if start > end
	bgt	done			@ exit program

	cmp	r2, r0			@ if value < start return 0
	movlt	r0, 0			@ if value < start move 0 into return
	blt	done			@ return and exit

	cmp	r2, r1			@ compare value and end
	movgt	r0,0			@ if value > end move 0 into return
	bgt	done			@ return and exit

	mov	r0, 1			@ value is between the interval 
done:
					@ return and exit 
@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@  return 
