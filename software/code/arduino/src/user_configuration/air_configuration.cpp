#include "common.hpp"
#include "air_configuration.hpp"
#include "pin_utils/adc_utils.hpp"

#define MIN_RELATIVE_HUMIDITY 0.0f
#define MAX_RELATIVE_HUMIDITY 100.0f

typedef struct AirConfigurationStateInternal
{
    Bool is_initialized;
    ADCIdentifier adc_identifier;
} AirConfigurationState;

static AirConfigurationState singleton = {FALSE, IDENTIFIER_ADC0};

void AirConfiguration_Initialize(ADCIdentifier adc_identifier)
{
    singleton.is_initialized = TRUE;
    singleton.adc_identifier = adc_identifier;
}

AirUserConfiguration AirConfiguration_GetAirUserConfiguration()
{
    AirUserConfiguration air_user_configuration;

    float relative_humidity_threshold = 0.0f;
    float adc_voltage_read;

    if(singleton.is_initialized == TRUE)
    {
        adc_voltage_read = read_adc(singleton.adc_identifier);

        relative_humidity_threshold = MIN_RELATIVE_HUMIDITY + (
            (MAX_RELATIVE_HUMIDITY - MIN_RELATIVE_HUMIDITY) * (adc_voltage_read / A_VCC)
        );
    }

    air_user_configuration.relative_humidity_threshold = relative_humidity_threshold;

    return air_user_configuration;
}