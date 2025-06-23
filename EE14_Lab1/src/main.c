#include <stdio.h>
#include "stm32l432xx.h"
#include "lab1_helpers.h"

// This function is called by printf() to handle the text string
// We want it to be sent over the serial terminal, so we just delegate to that function
int _write(int file, char *data, int len) {
    serial_write(USART2, data);
    return len;
}

int main()
{
    // Initialize serial port (aka UART) connected to the computer
    // The chip has a second serial port for talking to other devices (like GPS
    // modules and LIDAR rangefinders), but that's a project for another lab...
    host_serial_init();

    int num = 0;

    while(1){
        // Send a message over the serial port
        // printf() is the C equivalent of std::cout in C++.
        // Depending on your terminal settings, you might need \r\n or just \n to get a newline

        printf("Hello %d \r\n", num++);


        // Now wait for a little while
        volatile int i = 100000;
        while(i--) {} // This will evaluate true until i == 0
    }

    return 0; // If we ever get here, something has gone terribly wrong!
}
