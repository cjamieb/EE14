#include <stm32l432xx.h>
#include "ee14lib.h"
#include <stdio.h>
#include <string.h>

volatile unsigned count = 0;
// This function MUST be named SysTick_Handler for the CMSIS framework
// code to link to it correctly.
void SysTick_Handler(void) {
    count++;
}

void SysTick_initialize(void) {
    SysTick->CTRL = 0; // Enable the SysTick features
    SysTick->LOAD = 39; // set to every 10 kHz
    // This sets the priority of the interrupt to 15 (2^4 - 1), which is the
    // largest supported value (aka lowest priority)
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


int main()
{
    host_serial_init();

    EE14Lib_Pin joystick_x = A4;
    EE14Lib_Pin joystick_y = A5;

    EE14Lib_Pin green = A0;
    EE14Lib_Pin red = A2;
    EE14Lib_Pin blue = A3;
    EE14Lib_Pin yellow = A1;

    gpio_config_mode(green, OUTPUT);
    gpio_config_mode(red, OUTPUT);
    gpio_config_mode(blue, OUTPUT);
    gpio_config_mode(yellow, OUTPUT);

    char buffer[100];

    SysTick_initialize();

    while(1) {

        // adc_config_single(joystick_x);
        // unsigned int x_val = adc_read_single();
        // adc_config_single(joystick_y);
        // unsigned int y_val = adc_read_single();

        // code for the 4 led setup for L5: I setup a row of LEDs
        // if (x_val < 1023) {
        //     gpio_write(blue, 1);
        // }
        // else if (adc_val < 2047) {
        //     gpio_write(red, 1);
        // }
        // else if (adc_val < 3071) {
        //     gpio_write(green, 1);
        // }
        // else {
        //     gpio_write(yellow, 1);
        // }

        // unsigned int adc_val = adc_read_single();
        // sprintf(buffer, "%u\n", x_val);
        
        // gpio_write(blue, x_val >= 0 && x_val < 1000);
        // gpio_write(red, x_val >= 1000 && x_val < 2000);
        // gpio_write(green, x_val >= 2000 && x_val < 3000);
        // gpio_write(yellow, x_val >= 3000 && x_val < 4096);
        
        // start of the timing experiment (L6)

        // volatile unsigned start_time = count;
        adc_config_single(joystick_x);
        // volatile unsigned end_time = count;
        
        // volatile unsigned elapsed_time = end_time - start_time;
        
        // sprintf(buffer, "%u\n", elapsed_time);
        // serial_write(USART2, buffer, strlen(buffer));
        
        volatile unsigned start_read = count;
        unsigned int x_val = adc_read_single();
        volatile unsigned end_read = count;

        volatile unsigned read_time = end_read - start_read;
        
        sprintf(buffer, "%u\n", read_time);
        serial_write(USART2, buffer, strlen(buffer));
    }

}
