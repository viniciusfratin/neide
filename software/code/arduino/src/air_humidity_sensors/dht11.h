#ifndef DHT11_H
#define DHT11_H

#include "air_humidity_check_state.h"
#include <stdint.h>

void DHT11_Initialize(volatile uint8_t* data_pin_port_ptr, uint8_t data_pin);

AirHumidityInformation DHT11_GetAirHumidityInformation();

#endif