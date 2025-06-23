/*
 *  hw5_assembly.s
 * 
 *  Sam Sugerman
 *  3/31/25
 *  EE14
 *
 *  Use this file to implement your assembly program. Do NOT change the name of
 *  the function, otherwise the autograder will fail to compile your code. 
 */

.syntax unified
.section .text

/*
 * Implement Question 2 below. You may assume that r0 = 0x20000000 when this
 * function is called, and the data you are switching from little endian to big
 * endian is stored beginning at this address (i.e., 0x20000000).
 */
q2:

    // TODO: implement question 2
    MOV r7, r0
    LDR r0, [r0]
    ROR r1, r0, #8
    AND r2, r1, #0xFF000000
    ROR r1, r0, #24
    AND r3, r1, #0x00FF0000
    ROR r1, r0, #8
    AND r4, r1, #0x0000FF00
    ROR r1, r0, #24
    AND r5, r1, #0x000000FF
    ORR r6, r2, r3
    ORR r6, r6, r4
    ORR r6, r6, r5
    STR r6, [r7]
    MOV r0, r6


    bx lr   // return from the function, leave this line here
