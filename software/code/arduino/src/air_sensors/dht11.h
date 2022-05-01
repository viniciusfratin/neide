#ifndef DHT11_H
#define DHT11_H

#include "air_interface/air_interface.h"
#include <stdint.h>

void DHT11_Initialize(volatile uint8_t* data_pin_input_register_ptr,
    volatile uint8_t* data_pin_ddr_ptr, 
    volatile uint8_t* data_pin_port_ptr, 
    uint8_t data_pin
);

AirInformation DHT11_GetAirInformation();

#endif