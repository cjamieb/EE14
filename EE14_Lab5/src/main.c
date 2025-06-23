#include "ee14lib.h"

int main() {
    // Configuring the timer 
    timer_config_pwm(TIM2, 1000);

    // Set the maximum duration value to 1023
    const unsigned int duration = 1023;

    // For each color value, set its duty to 90 and then flash it using the duty value equivalent to 
    // the difference between the current duty value and the maximum duration.
    // Keep incrementing the duty values to contiinue this process.
    while(1) {
        for (unsigned int red = 90; red < duration; red++) {
            timer_config_channel_pwm(TIM2, A2, red);
            timer_config_channel_pwm(TIM2, A2, duration - red);
            // Create a delay for each color value so the LED flashes and the color changes
            // are not instantaneous
            int delay = 0;
            while (delay < 1000) {
                delay++;
            }
        }
        for (unsigned int green = 90; green < duration; green++) {
            timer_config_channel_pwm(TIM2, A4, green);
            timer_config_channel_pwm(TIM2, A4, duration - green);
            int delay = 0;
            while (delay < 1000) {
                delay++;
            }
        }
        for (unsigned int blue = 90; blue < duration; blue++) {
            timer_config_channel_pwm(TIM2, A7, blue);
            timer_config_channel_pwm(TIM2, A7, duration - blue);
            int delay = 0;
            while (delay < 1000) {
                delay++;
            }
        }
        
    }

}

 // 0 = brightest, 123 = darkest