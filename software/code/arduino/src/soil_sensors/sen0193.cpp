#include "sen0193.hpp"
#include "pin_utils/adc_utils.hpp"

#define MIN_RELATIVE_HUMIDITY 0.0f
#define MAX_RELATIVE_HUMIDITY 100.0f

typedef struct SEN0193StateInternal
{
    bool is_initialized;
    ADCIdentifier adc_identifier;
} SEN0193State;

static SEN0193State singleton = {false, IDENTIFIER_ADC0};

void SEN0193_Initialize(ADCIdentifier adc_identifier)
{
    singleton.is_initialized = true;
    singleton.adc_identifier = adc_identifier;
}

SoilInformation SEN0193_GetSoilInformation()
{
    SoilInformation soil_information;

    float current_relative_humidity = 0.0f;
    float adc_voltage_read;

    if(singleton.is_initialized == true)
    {
        adc_voltage_read = read_adc(singleton.adc_identifier);

        current_relative_humidity = MIN_RELATIVE_HUMIDITY + (
            (MAX_RELATIVE_HUMIDITY - MIN_RELATIVE_HUMIDITY) * (adc_voltage_read / A_VCC)
        );

        current_relative_humidity = MAX_RELATIVE_HUMIDITY - current_relative_humidity;
    }

    soil_information.relative_humidity = current_relative_humidity;

    return soil_information;
}


