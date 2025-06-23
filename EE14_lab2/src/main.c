// Lab 2 Campbell Braun
#define RCC_Register 0x40021000
#define RCC (RCC_Register + 0x4C)
#define GPIO_Port_Mode_Register 0x48000000
#define GPIO_PMR GPIO_Port_Mode_Register
#define GPIO_Pin (GPIO_Port_Mode_Register + 0x14)


int main()
{
    //configure the RCC to enable the GPIO clock
    volatile unsigned int* rcc_reg = (unsigned int*) RCC;
    *rcc_reg |= 0b1;

    //configure the GPIO port/pin as an output

    volatile unsigned int* gpio_preg = (unsigned int*) GPIO_Port_Mode_Register;
    *gpio_preg &= ~(0b11 << 24);
    *gpio_preg |= (0b01 << 24);

    volatile unsigned int* pin = (unsigned int*) GPIO_Pin;
    while(1) {
        *pin |= (0b1 << 12);
        *pin &= ~(0b1 << 12);
    }
}