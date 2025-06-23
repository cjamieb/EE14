/*
 *  main.s
 * 
 *  Sam Sugerman
 *  3/31/25
 *  EE14
 *
 *  Use this file to test your assembly program for Homework 5. We will supply
 *  code for basic testing, but we will not supply actual test cases. 
 */

.include "src/hw5_assembly.s"

.syntax unified
.section .text
.global main

main:
    /* 
     * This program doesn't take any arguments; however, if you look at 
     * hw5_assembly.s, you'll see that your function must assume r0 = 0x20000000
     * when it is called, so we'll take care of that here before branching to
     * the function.
     */

    // Do not change these two lines.
    LDR r0, =test_value
    BL  q2

    /*
     * Once the function returns, you can use the debugger to check the memory
     * contents at 0x20000000 to ensure your program worked as intended.
     */

    B . // Leave this line here.


.section .data
/*
 * Since your program is meant to access a value stored in memory, we must place
 * one there. This is the first (and only) value being stored in data memory, so 
 * it will be stored at 0x20000000 by default. To test your program with
 * different inputs, simply change the value below before running the debugger.
 */
test_value:
    .word 0x01020304
