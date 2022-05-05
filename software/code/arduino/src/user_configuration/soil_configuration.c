#include "common.h"
#include "soil_configuration.h"
#include "pin_utils/adc_utils.h"

#define MIN_RELATIVE_HUMIDITY 0.0f
#define MAX_RELATIVE_HUMIDITY 100.0f

typedef struct SoilConfigurationStateInternal
{
    Bool is_initialized;
    ADCIdentifier adc_identifier;
} SoilConfigurationState;

static SoilConfigurationState singleton = {FALSE, IDENTIFIER_ADC0};

void SoilConfiguration_Initialize(ADCIdentifier adc_identifier)
{
    singleton.is_initialized = TRUE;
    singleton.adc_identifier = adc_identifier;
}

SoilUserConfiguration SoilConfiguration_GetSoilUserConfiguration()
{
    SoilUserConfiguration soil_user_configuration;

    float relative_humidity_threshold = 0.0f;
    float adc_voltage_read;

    if(singleton.is_initialized == TRUE)
    {
        adc_voltage_read = read_adc(singleton.adc_identifier);

        relative_humidity_threshold = MIN_RELATIVE_HUMIDITY + (
            (MAX_RELATIVE_HUMIDITY - MIN_RELATIVE_HUMIDITY) * (adc_voltage_read / A_VCC)
        );
    }

    soil_user_configuration.relative_humidity_threshold = relative_humidity_threshold;

    return soil_user_configuration;
}