#include "gpio_utils.h"

void wait_for_gpio_high(volatile uint8_t* input_register_ptr, uint8_t pin, int timeout_cycles)
{
    int elapsed_cycles = 0;
    while(READ_GPIO_PIN(input_register_ptr, pin) == 1)
    {
        if(elapsed_cycles == timeout_cycles)
        {
            break;
        }
     
        elapsed_cycles++;
    }
}

void wait_for_gpio_low(volatile uint8_t* input_register_ptr, uint8_t pin, int timeout_cycles)
{
    int elapsed_cycles = 0;
    while(READ_GPIO_PIN(input_register_ptr, pin) == 0)
    {
        if(elapsed_cycles == timeout_cycles)
        {
            break;
        }
     
        elapsed_cycles++;
    }
}