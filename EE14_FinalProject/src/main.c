#include "stm32l432xx.h"
#include "ee14lib.h"

// numbering is from left to right, with the distance sensor facing you
EE14Lib_Pin led1 = A1;
EE14Lib_Pin led2 = A2;
EE14Lib_Pin led3 = A0;

EE14Lib_Pin trig = D9;
EE14Lib_Pin echo = D10;

EE14Lib_Pin button = A6;


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


// enabling the interrupt by setting the correct bits, based on the manual
void config_gpio_interrupt(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Because I am using PA8, I am setting EXTI8
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR3_EXTI8;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR3_EXTI8_PA;

    // Because I am using PA8, I am setting FT8 to align with EXTI8
    EXTI->FTSR1 |= EXTI_FTSR1_FT8;
    EXTI->IMR1 |= EXTI_FTSR1_FT8;

    NVIC_SetPriority(EXTI1_IRQn, 2);
    NVIC_EnableIRQ(EXTI1_IRQn);
}

// this is my interrupt handler function
// this function stops the timer/shuts off the display when the button is pressed, but resumes it after a delay
void EXTI1_IRQHandler(void)
{

    // configuring the trigger
    gpio_config_mode(trig, OUTPUT);
    gpio_config_mode(echo, INPUT);

    // writing a 1 to the trigger
    gpio_write(trig, 0b01);

    // if pin is high


    // because I cannot access the SysTick timer while I am in an external interrupt, I cannot use my delay_ms function
    
    // creating a delay
    for(volatile int i = 0; i < 10; i++) {
    }





    

    // the interrupt is over, so we have to clear the pending register
    EXTI->PR1 |= EXTI_PR1_PIF1;
}

int main()
{

    // Take a look in gpio.c for the new GPIO functions which should make your
    // life a little easier for configuring/reading/writing GPIO pins.
    SysTick_initialize();

    long duration;
    long distance;
    

    // configuring the LEDs
    gpio_config_mode(led1, OUTPUT);
    gpio_config_mode(led2, OUTPUT);
    gpio_config_mode(led3, OUTPUT);

    // configuring the button that will end the interrupt
    gpio_config_mode(button, INPUT);

    

    // calling my interrupt function to execute my task
    config_gpio_interrupt();
    gpio_config_mode(trig, OUTPUT);
    gpio_config_mode(echo, INPUT);
    while(1) {
        
        // turning on the tens digit anode
        gpio_write(D0, 1);
        // delay for 5 ms
        delay_ms(5);

        
    
        // writing a 1 to the trigger
        gpio_write(trig, 0b01);
        // wait 10 micro seconds
        for(int i = 0; i < 1000; i++){
        }
       int start = count;
       int end;
       while(gpio_read(echo) == 1){
            end = counter;
       }   
       int dist = end - start;
       float speed_of_sound = .0343; // this is centimeters per microsecond
       dist = (dist * speed_of_sound) / 2;     
    }

}