#include "dht11.h"
#include "common.h"
#include <stddef.h>

typedef struct DHT11StateInternal
{
    Bool is_initialized;
    volatile uint8_t* data_pin_port_ptr;
    uint8_t data_pin;
} DHT11State;

static DHT11State singleton = {FALSE, NULL, 0U};

static AirHumidityInformation DHT11_ReadAirHumidityInformationFromSensor();

void DHT11_Initialize(volatile uint8_t* data_pin_port_ptr, uint8_t data_pin)
{
    singleton.is_initialized = TRUE;
    singleton.data_pin_port_ptr = data_pin_port_ptr;
    singleton.data_pin = data_pin;
}

AirHumidityInformation DHT11_GetAirHumidityInformation()
{
    AirHumidityInformation information;
    information.current_relative_humidity = 0.0f;
    information.relative_humidity_threshold = 0.0f;

    if(singleton.is_initialized == TRUE)
    {
        DHT11_ReadAirHumidityInformationFromSensor();
    }

    return information;
}

static AirHumidityInformation DHT11_ReadAirHumidityInformationFromSensor()
{
    AirHumidityInformation information;
    information.current_relative_humidity = 60.0f;
    information.relative_humidity_threshold = 70.0f;

    return information;
}
