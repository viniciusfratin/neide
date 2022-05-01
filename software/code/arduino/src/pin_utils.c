#include "common.h"
#include "pin_utils.h"
#include <avr/io.h>

static Bool is_pin_input(volatile uint8_t* pin_ddr_ptr, uint8_t pin); 
static Bool is_pin_output(volatile uint8_t* pin_ddr_ptr, uint8_t pin);

void set_pin_as_input(volatile uint8_t* pin_ddr_ptr, uint8_t pin)
{
    (*pin_ddr_ptr) &= ~(_BV(pin));
}

void set_pin_as_output(volatile uint8_t* pin_ddr_ptr, uint8_t pin)
{
    (*pin_ddr_ptr) |= _BV(pin);
}

void set_pin_to_low(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin)
{
    if(is_pin_output(pin_ddr_ptr, pin) == TRUE)
    {
        (*pin_port_ptr) &= ~(_BV(pin));
    }
}

void set_pin_to_high(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin)
{
    if(is_pin_output(pin_ddr_ptr, pin) == TRUE)
    {
        (*pin_port_ptr) |= _BV(pin);
    }
}

int read_pin(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_input_register_ptr, uint8_t pin)
{
    int pin_value = 0;

    if(is_pin_input(pin_ddr_ptr, pin) == TRUE)
    {
        pin_value = (*pin_input_register_ptr) & _BV(pin);
    }

    return pin_value;
}

static Bool is_pin_input(volatile uint8_t* pin_ddr_ptr, uint8_t pin)
{
    Bool is_input = FALSE;
    
    if(bit_is_clear(*pin_ddr_ptr, pin))
    {
        is_input = TRUE;
    }

    return is_input;
}

static Bool is_pin_output(volatile uint8_t* pin_ddr_ptr, uint8_t pin)
{
    Bool is_output = FALSE;
    
    if(bit_is_set(*pin_ddr_ptr, pin))
    {
        is_output = TRUE;
    }

    return is_output;
}