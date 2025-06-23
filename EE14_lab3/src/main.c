#include "stm32l432xx.h"

// Decclaring functions
int grab_resistor_edges();
void delay(int random);
int get_press_time();
void figuring_out_timing(volatile int counter);


int main()
{
    // Set the GPIO A enable bit in the RCC AHB2 enable register
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Set A6 to input mode for the button
    GPIOA->MODER &= ~(GPIO_MODER_MODE7);

    // Set A5, A4, A3, A1 to output mode
    GPIOA->MODER &= ~(GPIO_MODER_MODE6); // clearing
    GPIOA->MODER |= (GPIO_MODER_MODE6_0); // setting
    GPIOA->MODER &= ~(GPIO_MODER_MODE5);
    GPIOA->MODER |= (GPIO_MODER_MODE5_0);
    GPIOA->MODER &= ~(GPIO_MODER_MODE4);
    GPIOA->MODER |= (GPIO_MODER_MODE4_0);
    GPIOA->MODER &= ~(GPIO_MODER_MODE1);
    GPIOA->MODER |= (GPIO_MODER_MODE1_0);

    // Setting the button/pull up resistor (A6)
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD7);
    GPIOA->PUPDR |= (GPIO_PUPDR_PUPD7_0);

    // Setting all the LEDs to the off or 0 state
    GPIOA->ODR &= ~(GPIO_ODR_OD6); //green
    GPIOA->ODR &= ~(GPIO_ODR_OD5); //yellow
    GPIOA->ODR &= ~(GPIO_ODR_OD4); //red
    GPIOA->ODR &= ~(GPIO_ODR_OD1); //blue

    // Since I am doing a pull-up resistor here, I have to set its initial value to 1
    // This is because when a pull-up resistor is open, it will be in its "1" state
    volatile int button = 1;

    // Initializing the randomness of the blue LED to be 0
    volatile int random = 0;


    while(1) {

        // Incrementing the level of randomness each time this loops
        random++;

        // Waiting until the button gets pressed to light up the LEDs
        button = grab_resistor_edges();


        // Gameplay

        // if the button has been pressed & the pull-up resistor has been driven low
        if (button == 0) {
          // setting all the LEDs to the off state
          GPIOA->ODR &= ~(GPIO_ODR_OD6); //green
          GPIOA->ODR &= ~(GPIO_ODR_OD5); //yellow
          GPIOA->ODR &= ~(GPIO_ODR_OD4); //red

          // waiting until the blue LED turns on/implementing the delay
          delay(random);

          // getting the time it takes the player to press the button
          volatile int press_time = get_press_time();

          figuring_out_timing(press_time);

          // I noticed when trying to play my game that pressing it too fast would mess up the game, so
          // I tried to delay by an arbitrary amount to see if that would affect the successful game implementation
          // I tried delaying by four, one, and two, but three seems to work the best
          delay(3);
          // This delay helps the game work better for reasons I am unsure of

        }

    }

}

// To implement a pull-up resistor, we have to get a falling edge
// This is because the pull-up resistor ensures the input is high when not driven low/affected by anything
// However, I could not figure out how to grab a falling edge, so I ended up grabbing both rising & falling edges
// My failed falling edge function is commented out below this one
int grab_resistor_edges() {
  // low state for the pull up resistor
  int low = (GPIOA->IDR) & (GPIO_IDR_ID7);
  // high state for the the pull up resistor
  int high = (GPIOA->IDR) & (GPIO_IDR_ID7);

  while(1) {
    high = (GPIOA->IDR) & (GPIO_IDR_ID7);
    low = (GPIOA->IDR) & (GPIO_IDR_ID7);
    // as long as the low state and high states are not the same, return 0
    if (high != low) {
      return 0;
    }
  }

}

// Failed falling edge function
// int grab_falling_edge() {
//   // Since we are using a pull-up resistor, it starts high 
//   static int previous_state = 1;
//   int current_state = (GPIOA->IDR) & (GPIO_IDR_ID7);

//   if (previous_state == 1 && current_state == 0) {
//     previous_state = current_state;
//     return 1;
//   }
//   else {
//     previous_state = current_state;
//     return 0;
//   }
// }

// Randomizing how long it takes for the blue LED to light up after the player presse the button
void delay(int random) {
  for (volatile int i = 0; i < ((100000 * random) % 100000) + 100000; i++) {
  }
}


// Getting the time that elapses between the blue light turning on and the player pressing the button
int get_press_time() {
  GPIOA->ODR |= (GPIO_ODR_OD1); // blue LED output

  // creating a counter that counts from when the blue LED turns on to when the player presses
  volatile int counter = 0;
  // creating an integer that detects if we are at the final loop or not
  volatile int final_loop = 1;
  while (1) {
    final_loop = (GPIOA->IDR) & (GPIO_IDR_ID7);
    if (final_loop == 0) {
      GPIOA->ODR &= ~(GPIO_ODR_OD1); // blue LED output
      return counter;
    }
    else {
      counter++;
    }
  }

}

// Figuring out which LED to light up, based on how long it took the player to press the button
void figuring_out_timing(volatile int counter) {
  // I am not sure what the period of this clock is, so I used large numbers to estimate these counter conditions

  // if the interval is under 200 ms
  if (counter < 100000) {
    // turning on the green LED
    GPIOA->ODR |= (GPIO_ODR_OD6);
  }
  // if the interval is under 250 ms
  else if (counter < 200000) {
    // turning on the yellow LED
    GPIOA->ODR |= (GPIO_ODR_OD5);
  }
  // if the interval is over 250 ms
  else {
    // turning on the red LED
    GPIOA->ODR |= (GPIO_ODR_OD4);
  }

}
