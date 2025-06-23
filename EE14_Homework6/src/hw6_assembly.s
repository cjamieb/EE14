.syntax unified
.section .text

product:
    push {lr}

    // first four integers
    mul r0, r0, r1 // int a * int b = r0
    mul r0, r0, r2 // r0 * int c = r0
    mul r0, r0, r3 // r0 * int d = r0

    // remaining four integers (passed via the stack)
    ldr r1, [sp, #4] // loading int e into r1
    mul r0, r0, r1 // r0 * int e = r0

    ldr r1, [sp, #8] // loading int f into r1
    mul r0, r0, r1 // r0 * int f = r0

    ldr r1, [sp, #12] // loading int g into r1
    mul r0, r0, r1 // r0 * int g = r0

    ldr r1, [sp, #16] // loading int h into r1
    mul r0, r0, r1 // r0 * int h = r0

    pop {lr}
    bx lr

power:
    // the value of x is stored in r4
    // the value of y is stored in r5
    push {r4, r5, lr}

    mov r4, r0 // setting x = r0
    mov r5, r1 // setting y = r1

    cmp r5, #0 // checking if y is equal to zero
    bne recursive_pwr // if y isn't equal to zero, branch
    mov r0, #1 
    b end_pwr

recursive_pwr:
    tst r5, #1 // testing to see if r5 is set to 1
    beq even_pwr // if r5 is equal to 1, then branch (since this is an even power)

    sub r1, r5, #1 // subtracting 1 from r5, and then storing it in r1
    mov r0, r4 // moving the value of x into r0
    bl power // branch back to the power subroutine
    mul r0, r4, r0 // multiplying the value of x by the value of r0
    b end_pwr // branch to the statement that finishes this power sequence

even_pwr:
    lsr r1, r5, #1 // perform a logicaql shift right
    mov r0, r4 // moving the value of x into r0
    bl power // branch back again to this power subroutine
    mul r0, r0, r0 // multiplying r0 by itself and storing this in r0

end_pwr:
    pop {r4, r5, lr}
    bx lr

