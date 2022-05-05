#include "dht11.h"
#include "common.h"
#include "pin_utils/gpio_utils.h"
#include <stdint.h>
#include <stddef.h>
#include <util/delay.h>


typedef struct DHT11StateInternal
{
    Bool is_initialized;
    volatile uint8_t* data_pin_input_register_ptr;
    volatile uint8_t* data_pin_ddr_ptr;
    volatile uint8_t* data_pin_port_ptr;
    uint8_t data_pin;
} DHT11State;

typedef struct DHT11InterchangeDataInternal
{
    int relative_humidity_integral_part;
    int relative_humidity_decimal_part;
    int temperature_integral_part;
    int temperature_decimal_part;
    Bool is_valid;
} DHT11InterchangeData;

static DHT11State singleton = {FALSE, NULL, NULL, NULL, 0U};

static AirInformation DHT11_ReadAirInformationFromSensor();
static DHT11InterchangeData DHT11_GetSensorData();

#define DHT_TIMEOUT_CYCLES 2000
static void DHT11_ProtocolRequest();
static void DHT11_ProtocolWaitForResponse();
static int DHT11_ProtocolReceiveByte();
static void DHT11_ProtocolFinishInterchange();

static float DHT11_GetFloatingPointFromDecimalPart(int decimal_part);

void DHT11_Initialize(volatile uint8_t* data_pin_input_register_ptr,
    volatile uint8_t* data_pin_ddr_ptr, 
    volatile uint8_t* data_pin_port_ptr, 
    uint8_t data_pin)
{
    singleton.is_initialized = TRUE;
    singleton.data_pin_input_register_ptr = data_pin_input_register_ptr;
    singleton.data_pin_ddr_ptr = data_pin_ddr_ptr;
    singleton.data_pin_port_ptr = data_pin_port_ptr;
    singleton.data_pin = data_pin;
}

AirInformation DHT11_GetAirInformation()
{
    AirInformation air_information;
    air_information.relative_humidity = 0.0f;
    air_information.temperature = 0.0f;

    if(singleton.is_initialized == TRUE)
    {
        air_information = DHT11_ReadAirInformationFromSensor();
    }

    return air_information;
}

static AirInformation DHT11_ReadAirInformationFromSensor()
{
    AirInformation information;
    DHT11InterchangeData sensor_data = DHT11_GetSensorData();

    float relative_humidity = 0.0f;
    float temperature = 0.0f;

    if(sensor_data.is_valid == TRUE)
    {
        relative_humidity = (float)sensor_data.relative_humidity_integral_part;
        relative_humidity += DHT11_GetFloatingPointFromDecimalPart(sensor_data.relative_humidity_decimal_part);

        temperature = (float)sensor_data.temperature_integral_part;
        temperature += DHT11_GetFloatingPointFromDecimalPart(sensor_data.temperature_decimal_part);
    }
    else
    {
        relative_humidity = 0.0f;
        temperature = 0.0f;
    }
    
    information.relative_humidity = relative_humidity;
    information.temperature = temperature;

    return information;
}

static void DHT11_ProtocolRequest()
{
    SET_GPIO_PIN_AS_OUTPUT(singleton.data_pin_ddr_ptr, singleton.data_pin);

    SET_GPIO_PIN_TO_HIGH(singleton.data_pin_port_ptr, singleton.data_pin);
    _delay_ms(100);
	
    SET_GPIO_PIN_TO_LOW(singleton.data_pin_port_ptr, singleton.data_pin);
    _delay_ms(18);
	
    SET_GPIO_PIN_TO_HIGH(singleton.data_pin_port_ptr, singleton.data_pin);
}

static void DHT11_ProtocolWaitForResponse()
{
	SET_GPIO_PIN_AS_INPUT(singleton.data_pin_ddr_ptr, singleton.data_pin);
    _delay_us(40);

    wait_for_gpio_low(singleton.data_pin_input_register_ptr, singleton.data_pin, DHT_TIMEOUT_CYCLES);
    wait_for_gpio_high(singleton.data_pin_input_register_ptr, singleton.data_pin, DHT_TIMEOUT_CYCLES);
}

static int DHT11_ProtocolReceiveByte()
{
    int result = 0;

    for(int i = 0; i < 8; i++)
    {
        wait_for_gpio_low(singleton.data_pin_input_register_ptr, singleton.data_pin, DHT_TIMEOUT_CYCLES);

        _delay_us(30);
        if(READ_GPIO_PIN(singleton.data_pin_input_register_ptr, singleton.data_pin) == 1)
        {
            result = ((result << 1) | 0x01);
        }
        else
        {
            result = (result << 1);
        }

        wait_for_gpio_high(singleton.data_pin_input_register_ptr, singleton.data_pin, DHT_TIMEOUT_CYCLES);
    }

    return result;
}

static void DHT11_ProtocolFinishInterchange()
{
    SET_GPIO_PIN_AS_OUTPUT(singleton.data_pin_ddr_ptr, singleton.data_pin);

    SET_GPIO_PIN_TO_HIGH(singleton.data_pin_port_ptr, singleton.data_pin);
	_delay_ms(100);
}

static DHT11InterchangeData DHT11_GetSensorData()
{
    DHT11InterchangeData interchange_data;
    int received_checksum;
    int calculated_checksum;
    
    DHT11_ProtocolRequest();
    DHT11_ProtocolWaitForResponse();
	
    interchange_data.relative_humidity_integral_part = DHT11_ProtocolReceiveByte();
    interchange_data.relative_humidity_decimal_part = DHT11_ProtocolReceiveByte();
    interchange_data.temperature_integral_part = DHT11_ProtocolReceiveByte();
    interchange_data.temperature_decimal_part = DHT11_ProtocolReceiveByte();
    received_checksum = DHT11_ProtocolReceiveByte();

	DHT11_ProtocolFinishInterchange();

    calculated_checksum = interchange_data.relative_humidity_integral_part;
    calculated_checksum += interchange_data.relative_humidity_decimal_part;
    calculated_checksum += interchange_data.temperature_integral_part;
    calculated_checksum += interchange_data.temperature_decimal_part;
    calculated_checksum = (calculated_checksum & 0x00FF);

    if(calculated_checksum == received_checksum)
    {
        interchange_data.is_valid = TRUE;
    }
    else
    {
        interchange_data.is_valid = FALSE;
    }

    return interchange_data;
}

static float DHT11_GetFloatingPointFromDecimalPart(int decimal_part)
{
    float floating_point_decimal_part = (float)decimal_part;
    while(!(floating_point_decimal_part < 1.0f))
    {
        floating_point_decimal_part /= 10.0f;
    }

    return floating_point_decimal_part;
}
