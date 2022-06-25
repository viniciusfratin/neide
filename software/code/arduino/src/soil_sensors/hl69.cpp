#include "common.hpp"
#include "hl69.hpp"
#include "pin_utils/adc_utils.hpp"

#define MIN_RELATIVE_HUMIDITY 0.0f
#define MAX_RELATIVE_HUMIDITY 100.0f

typedef struct HL69StateInternal
{
    Bool is_initialized;
    ADCIdentifier adc_identifier;
} HL69State;

static HL69State singleton = {FALSE, IDENTIFIER_ADC0};

void HL69_Initialize(ADCIdentifier adc_identifier)
{
    singleton.is_initialized = TRUE;
    singleton.adc_identifier = adc_identifier;
}

SoilInformation HL69_GetSoilInformation()
{
    SoilInformation soil_information;

    float current_relative_humidity = 0.0f;
    float adc_voltage_read;

    if(singleton.is_initialized == TRUE)
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


