#include "stm32l432xx.h"
#include "ee14lib.h"

// This version of the code has the LEDS, speaker and button working but the
// alarm system only triggers when the VCC of the distance sensor is disconnected
// and then reconnected.

// LED Pins
EE14Lib_Pin led1 = A1;
EE14Lib_Pin led2 = A2;
EE14Lib_Pin led3 = A0;

// Ultrasonic sensor pins
EE14Lib_Pin trig = D10;
EE14Lib_Pin echo = D9;

// Button Pin
EE14Lib_Pin button = A6;
EE14Lib_Pin Onbutton = A4;

// Speaker Pin
EE14Lib_Pin speaker = D1;

// Constants
#define ALARM_THRESHOLD 3  // Distance threshold in cm to trigger alarm

// Define different alarm patterns
#define PATTERN_RAPID_BEEP 1
#define PATTERN_RISING_TONE 2
#define PATTERN_ALTERNATING 3

// Use higher frequencies for better audibility with small speaker
#define ALARM_LOW_FREQ 2000   // 2kHz 
#define ALARM_HIGH_FREQ 4000  // 4kHz

// Global variables
volatile unsigned count = 0;
volatile bool alarm_active = false;
bool buttonPressed = false;

// volatile unsigned count = 0;
// volatile unsigned counter = 0;

// Systick Handler for timing
void SysTick_Handler(void) {
    count++;
}

// Initialize SysTick timer for 1ms intervals
void SysTick_initialize(void) {
    SysTick->CTRL = 0; // Enable the SysTick features
    SysTick->LOAD = 3999;
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

// Delay function using SysTick
int delay_ms(unsigned milliseconds) {
    unsigned start = count;
    while (count < (start + milliseconds)) {
        // Wait
    }

}

// Measure distance using ultrasonic sensor
int measure_distance(void) {
    // Send trigger pulse
    gpio_write(trig, 0);
    delay_ms(2);
    gpio_write(trig, 1);
    delay_ms(1);  // 10µs pulse (minimum is plenty)
    gpio_write(trig, 0);
    
    // Measure echo pulse duration
    unsigned start_time = 0;
    unsigned end_time = 0;
    unsigned timeout = count + 100;  // 100ms timeout
    
    // Wait for echo to go high
    while (gpio_read(echo) == 0) {
        if (count > timeout) return -1;  // Timeout
    }
    start_time = count;
    
    // Wait for echo to go low
    while (gpio_read(echo) == 1) {
        if (count > timeout) return -1;  // Timeout
    }
    end_time = count;
    
    // Calculate distance in cm (speed of sound = 343m/s = 0.0343cm/µs)
    // Time is in ms, so multiply by 10 to get rough cm value
    // Distance = (time * 0.0343 * 1000) / 2 ≈ time * 17.15
    return (end_time - start_time) * 17 / 10;
}

// Set the state of all LEDs
void set_leds(bool state) {
    gpio_write(led1, state);
    gpio_write(led2, state);
    gpio_write(led3, state);
}

// Toggle LEDs for flashing effect
void toggle_leds(void) {
    static bool led_state = false;
    led_state = !led_state;
    set_leds(led_state);
}

// Play a tone with rapid on-off pulsing for better audibility
void play_pulsed_tone(unsigned frequency, unsigned duration_ms) {
    unsigned period_us = 1000000 / frequency;
    unsigned half_period_us = period_us / 2;
    unsigned end_time = count + duration_ms;
    
    while (count < end_time) {
        // Rapidly pulse the speaker on/off for 10 cycles
        for (int i = 0; i < 10; i++) {
            gpio_write(speaker, 1);
            
            // Very short delay (half cycle)
            for (volatile int j = 0; j < half_period_us / 5; j++) {
                // Empty loop for short delay
            }
            
            gpio_write(speaker, 0);
            
            // Very short delay (half cycle)
            for (volatile int j = 0; j < half_period_us / 5; j++) {
                // Empty loop for short delay
            }
        }
        
        // Brief pause between pulses
        delay_ms(5);
    }
}

// Create a rising tone pattern
void play_rising_tone(unsigned duration_ms) {
    unsigned start_time = count;
    unsigned end_time = count + duration_ms;
    
    while (count < end_time) {
        // Calculate current frequency based on time elapsed
        unsigned elapsed = count - start_time;
        unsigned frequency = ALARM_LOW_FREQ + 
                           ((ALARM_HIGH_FREQ - ALARM_LOW_FREQ) * elapsed) / duration_ms;
        
        unsigned period_us = 1000000 / frequency;
        unsigned half_period_us = period_us / 2;
        
        // Generate one cycle at current frequency
        gpio_write(speaker, 1);
        for (volatile int i = 0; i < half_period_us / 10; i++) { }
        gpio_write(speaker, 0);
        for (volatile int i = 0; i < half_period_us / 10; i++) { }
    }
}

// Alternating between two frequencies
void play_alternating_tone(unsigned duration_ms) {
    unsigned end_time = count + duration_ms;
    bool high_freq = true;
    unsigned switch_time = count + 100; // Switch every 100ms
    
    while (count < end_time) {
        unsigned frequency = high_freq ? ALARM_HIGH_FREQ : ALARM_LOW_FREQ;
        unsigned period_us = 1000000 / frequency;
        unsigned half_period_us = period_us / 2;
        
        if (count >= switch_time) {
            high_freq = !high_freq;
            switch_time = count + 100;
        }
        
        // Generate sound at current frequency
        gpio_write(speaker, 1);
        for (volatile int i = 0; i < half_period_us / 10; i++) { }
        gpio_write(speaker, 0);
        for (volatile int i = 0; i < half_period_us / 10; i++) { }
    }
}

// Basic square wave tone - higher volume version with tighter timing
void play_basic_tone(unsigned frequency, unsigned duration_ms) {
    unsigned period_us = 1000000 / frequency;
    unsigned half_period_us = period_us / 2;
    unsigned end_time = count + duration_ms;
    
    while (count < end_time) {
        gpio_write(speaker, 1);
        // Use very tight timing loops to maximize frequency accuracy
        for (volatile int i = 0; i < half_period_us / 8; i++) { }
        
        gpio_write(speaker, 0);
        for (volatile int i = 0; i < half_period_us / 8; i++) { }
    }
}




// Configure button interrupt
void config_button_interrupt(void) {
    // Enable SYSCFG clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    
    // Map external interrupt line to the correct GPIO port
    // A6 = PA7, so we need EXTI7
    SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI7;  // Clear bits
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI7_PA;  // PA7
    
    // Configure interrupt for falling edge
    EXTI->FTSR1 |= EXTI_FTSR1_FT7;  // Falling trigger for line 7
    EXTI->IMR1 |= EXTI_IMR1_IM7;    // Unmask interrupt line 7
    
    // Enable interrupt in NVIC
    NVIC_SetPriority(EXTI9_5_IRQn, 2);  // Lines 5-9 share an IRQ
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

// Button interrupt handler
void EXTI9_5_IRQHandler(void) {
    
    //delay_ms(1);
    if (EXTI->PR1 & EXTI_PR1_PIF7) {  // Check if it's EXTI7 (A6/PA7)
    //turn off operations until button is pressed again to reset
        buttonPressed = true;
        // Button pressed - disable alarm
        alarm_active = false;
        set_leds(0);  // Turn off LEDs
        // Clear pending bit
        EXTI->PR1 |= EXTI_PR1_PIF7;
        
    }
}

// Try to set up hardware PWM for the speaker (may produce better sound)
void setup_speaker_pwm(void) {
    // Enable TIM2 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    
    // Configure the timer for PWM mode
    // PA9 (D1) is connected to TIM1_CH2 (AF1)
    gpio_config_mode(speaker, ALTERNATE_FUNCTION);
    gpio_config_alternate_function(speaker, 1);  // AF1 for TIM1
    
    // Try to configure PWM with the timer functions from ee14lib
    timer_config_pwm(TIM1, ALARM_HIGH_FREQ);
    timer_config_channel_pwm(TIM1, speaker, 0);  // Start with 0% duty cycle
}

// // enabling the interrupt by setting the correct bits, based on the manual
// void config_gpio_interrupt(void)
// {
//     RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

//     // Because I am using PA8, I am setting EXTI8
//     SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR3_EXTI8;
//     SYSCFG->EXTICR[0] |= SYSCFG_EXTICR3_EXTI8_PA;

//     // Because I am using PA8, I am setting FT8 to align with EXTI8
//     EXTI->FTSR1 |= EXTI_FTSR1_FT8;
//     EXTI->IMR1 |= EXTI_FTSR1_FT8;

//     NVIC_SetPriority(EXTI1_IRQn, 2);
//     NVIC_EnableIRQ(EXTI1_IRQn);
// }


// // this is my interrupt handler function
// // this function stops the timer/shuts off the display when the button is pressed, but resumes it after a delay
// void EXTI1_IRQHandler(void)
// {

//     // configuring the trigger
//     gpio_config_mode(trig, OUTPUT);
//     gpio_config_mode(echo, INPUT);

//     // writing a 1 to the trigger
//     gpio_write(trig, 0b01);

//     // if pin is high


//     // because I cannot access the SysTick timer while I am in an external interrupt, I cannot use my delay_ms function
    
//     // creating a delay
//     for(volatile int i = 0; i < 10; i++) {
//     }

//     // the interrupt is over, so we have to clear the pending register
//     EXTI->PR1 |= EXTI_PR1_PIF1;
// }



int main() {
    // Initialize timing
    SysTick_initialize();

    // Configure LEDs
    gpio_config_mode(led1, OUTPUT);
    gpio_config_mode(led2, OUTPUT);
    gpio_config_mode(led3, OUTPUT);
    set_leds(0);  // Ensure LEDs start off

    // Configure ultrasonic sensor
    gpio_config_mode(trig, OUTPUT);
    gpio_config_mode(echo, INPUT);
    gpio_write(trig, 0);  // Start with trigger low

    // Configure button with pullup
    gpio_config_mode(button, INPUT);
    gpio_config_pullup(button, PULL_UP);

    gpio_config_mode(Onbutton, INPUT);
    gpio_config_pullup(Onbutton, PULL_UP);
    


    config_button_interrupt();

    // Try to set up hardware PWM for better speaker sound
    // If this doesn't work, we'll fall back to the basic speaker output
    bool use_pwm = false;

    // If speaker supports PWM, configure it
    if (use_pwm) {
        setup_speaker_pwm();
    } else {
        // Otherwise, use basic GPIO for speaker
        gpio_config_mode(speaker, OUTPUT);
        gpio_write(speaker, 0);  // Start with speaker off
    }
    
    int distance;
    unsigned led_toggle_time = 0;
    unsigned speaker_toggle_time = 0;

    // Test the speaker at startup
    //play_alternating_tone(200);  // Alternating high/low pitch
    //play_rising_tone(200);     // Rising pitch
    play_pulsed_tone(3000, 200); // Rapid beeping
    //play_basic_tone(3500, 200); // Basic high pitch tone
    delay_ms(500);

    while (1) {
        if(!gpio_read(Onbutton)){
            set_leds(0);
            buttonPressed = false;  

        }

        
        while(!buttonPressed){
            // Measure distance
            distance = measure_distance();
            // Debug - flash LED based on distance
            if (distance > 0 && distance < ALARM_THRESHOLD) {
                // Valid distance measured
                for (int i = 0; i < 2; i++) {
                    set_leds(1);
                    delay_ms(100);
                    set_leds(0);
                    delay_ms(100);
                }
            }
            
            // Check if object is within threshold
            if (distance > 0 && distance < ALARM_THRESHOLD) {
                if (!alarm_active) {
                    // Activate alarm
                    alarm_active = true;
                    led_toggle_time = count;
                    speaker_toggle_time = count;
                }
            }
            
            // Handle alarm effects if active
            if (alarm_active) {
                // Toggle LEDs every 250ms
                if (count - led_toggle_time >= 250) {
                    toggle_leds();
                    led_toggle_time = count;
                }
                
                // Generate speaker alarm sounds
                if (count - speaker_toggle_time >= 300) {
                    if (use_pwm) {
                        // Use hardware PWM
                        timer_config_channel_pwm(TIM1, speaker, 50);  // 50% duty cycle
                    } else {
                        // Try different sound patterns
                        // Uncomment the one that works best with your speaker
                        //play_alternating_tone(200);  // Alternating high/low pitch
                        //play_rising_tone(200);     // Rising pitch
                        play_pulsed_tone(3000, 200); // Rapid beeping
                        //play_basic_tone(3500, 200); // Basic high pitch tone
                    }
                    speaker_toggle_time = count;
                }
            } else {
                // If alarm is not active, ensure speaker is off
                if (use_pwm) {
                    timer_config_channel_pwm(TIM1, speaker, 0);  // 0% duty cycle
                } else {
                    gpio_write(speaker, 0);
                }
            }
            // Small delay between readings
            delay_ms(50);
        }
    }
    return 1;
}