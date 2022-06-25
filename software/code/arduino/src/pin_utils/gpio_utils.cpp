#include "gpio_utils.hpp"

void wait_for_gpio_high(volatile unsigned char* input_register_ptr, unsigned char pin, long timeout_cycles)
{
    long elapsed_cycles = 0;
    while(READ_GPIO_PIN(input_register_ptr, pin) == 1)
    {
        if(elapsed_cycles == timeout_cycles)
        {
            break;
        }
     
        elapsed_cycles++;
    }
}

void wait_for_gpio_low(volatile unsigned char* input_register_ptr, unsigned char pin, long timeout_cycles)
{
    long elapsed_cycles = 0;
    while(READ_GPIO_PIN(input_register_ptr, pin) == 0)
    {
        if(elapsed_cycles == timeout_cycles)
        {
            break;
        }
     
        elapsed_cycles++;
    }
}