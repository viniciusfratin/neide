#ifndef AIR_CONFIGURATION_HPP
#define AIR_CONFIGURATION_HPP

#include "air_interface/air_interface.hpp"
#include "pin_utils/adc_defs.hpp"

void AirConfiguration_Initialize(ADCIdentifier adc_identifier);
AirUserConfiguration AirConfiguration_GetAirUserConfiguration();

#endif