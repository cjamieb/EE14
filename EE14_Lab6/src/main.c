#include "stm32l432xx.h"
#include "ee14lib.h"

volatile unsigned count = 0;
volatile unsigned counter = 0;
// This function MUST be named SysTick_Handler for the CMSIS framework
// code to link to it correctly.
void SysTick_Handler(void) {
    count++;
}

void SysTick_initialize(void) {
    SysTick->CTRL = 0; // Enable the SysTick features
    SysTick->LOAD = 3999; // Setting the value of the LOAD register to accomodate a 1kHz target frequency
    // This sets the priority of the interrupt to 15 (2^4 - 1), which is the
    // largest supported value (aka lowest priority)
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

int delay_ms(unsigned milliseconds) {
    // timer_config_pwm(TIM2, 1000);
    // timer_config_channel_pwm(TIM2, A4, 100);
    unsigned start = count;
    while (count < (start + milliseconds)) {
    }

}

// this array stores all the pins (A-G) that I am using for the seven seg
EE14Lib_Pin pins[7] = {D2, D3, D4, D5, D6, D9, D10};

// this array stores all the pin values need to display digits 0-9
bool segments[10][7] =        { {0,0,0,0,0,0,1}, //0
                                {1,0,0,1,1,1,1}, //1
                                {0,0,1,0,0,1,0}, //2
                                {0,0,0,0,1,1,0}, //3
                                {1,0,0,1,1,0,0}, //4
                                {0,1,0,0,1,0,0}, //5
                                {0,1,0,0,0,0,0}, //6
                                {0,0,0,1,1,1,1}, //7
                                {0,0,0,0,0,0,0}, //8
                                {0,0,0,1,1,0,0}, }; //9

// this function displays the correct number based on the value given as a parameter
int displays(unsigned digit) {
    for (int i = 0; i < 7; i++) {
        gpio_write(pins[i], segments[digit][i]);
    }
}

// enabling the interrupt by setting the correct bits, based on the manual
void config_gpio_interrupt(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Because I am using PA1, I am setting EXTI1
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;

    // Because I am using PA1, I am setting FT1 to align with EXTI1
    EXTI->FTSR1 |= EXTI_FTSR1_FT1;
    EXTI->IMR1 |= EXTI_FTSR1_FT1;

    NVIC_SetPriority(EXTI1_IRQn, 2);
    NVIC_EnableIRQ(EXTI1_IRQn);
}

// this is my interrupt handler function
// this function stops the timer/shuts off the display when the button is pressed, but resumes it after a delay
void EXTI1_IRQHandler(void)
{
    // turning off the tens digit anode
    gpio_write(D0, 0);
    // turning off the ones digit anode
    gpio_write(D1, 0);

    // because I cannot access the SysTick timer while I am in an external interrupt, I cannot use my delay_ms function
    
    // creating a delay
    for(volatile int i = 0; i < 500000; i++) {
    }

    // the interrupt is over, so we have to clear the pending register
    EXTI->PR1 |= EXTI_PR1_PIF1;
}

int main()
{
    // Take a look in gpio.c for the new GPIO functions which should make your
    // life a little easier for configuring/reading/writing GPIO pins.
    SysTick_initialize();
    //gpio_config_direction(A4, 0b01);
    // while(1) {
    //     gpio_write(A4, 1);
    //     delay_ms(1000);
    //     gpio_write(A4, 0);
    //     delay_ms(1000);
    // }

    // configuring pins A-G plus the tens digit anode and ones digit anode for the seven seg
    gpio_config_direction(D2, 0b01);
    gpio_config_direction(D3, 0b01);
    gpio_config_direction(D4, 0b01);
    gpio_config_direction(D5, 0b01);
    gpio_config_direction(D6, 0b01);
    gpio_config_direction(D0, 0b01);
    gpio_config_direction(D1, 0b01);
    gpio_config_direction(D9, 0b01);
    gpio_config_direction(D10, 0b01);


    // configuring the button for the final part

    // setting A1 (where my button is plugged in) to input mode
    gpio_config_direction(A1, 0b00);
    // enabling the pull up resistor
    gpio_config_pullup(A1, 0b01);

    // calling my interrupt function to execute my task
    config_gpio_interrupt();

    while(1) {
        // // A through G
        // gpio_write(D2, 0);
        // gpio_write(D3, 0);
        // gpio_write(D4, 0);
        // gpio_write(D5, 0);
        // gpio_write(D6, 0);
        // gpio_write(D9, 0);
        // gpio_write(D10, 0);
        unsigned display_tens = ((count/10000)%10);
        unsigned display_ones = ((count/1000)%10);

        displays(display_tens);

        // turning on the tens digit anode
        gpio_write(D0, 1);
        // delay for 5 ms
        delay_ms(5);
        // turning off the tens digit anode
        gpio_write(D0, 0);

        displays(display_ones);
        // turning on the ones digit anode
        gpio_write(D1, 1);
        // delay for 5 ms
        delay_ms(5);
        // turning off the ones digit anode
        gpio_write(D1, 0);

    }

}