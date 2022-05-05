#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H

#define SET_GPIO_PIN_AS_INPUT(pin_ddr_ptr, pin) ((*pin_ddr_ptr) &= ~((1 << pin)))
#define SET_GPIO_PIN_AS_OUTPUT(pin_ddr_ptr, pin) ((*pin_ddr_ptr) |= (1 << pin))
#define SET_GPIO_PIN_TO_LOW(pin_port_ptr, pin) ((*pin_port_ptr) &= ~((1 << pin)))
#define SET_GPIO_PIN_TO_HIGH(pin_port_ptr, pin) ((*pin_port_ptr) |= (1 << pin))
#define READ_GPIO_PIN(input_register_ptr, pin) ((((*input_register_ptr) & (1 << pin)) >> pin))

#endif