#ifndef DHT11_HPP
#define DHT11_HPP

#include "air_interface/air_interface.hpp"

void DHT11_Initialize(volatile unsigned char* data_pin_input_register_ptr,
    volatile unsigned char* data_pin_ddr_ptr, 
    volatile unsigned char* data_pin_port_ptr, 
    unsigned char data_pin
);

AirInformation DHT11_GetAirInformation();
AirInformation test();

#endif