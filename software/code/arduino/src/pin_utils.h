#ifndef PIN_UTILS_H
#define PIN_UTILS_H

#include <stdint.h>

void set_pin_as_input(volatile uint8_t* pin_ddr_ptr, uint8_t pin);
void set_pin_as_output(volatile uint8_t* pin_ddr_ptr, uint8_t pin);
void set_pin_to_low(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin);
void set_pin_to_high(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin);
int read_pin(volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_input_register_ptr, uint8_t pin);

#endif