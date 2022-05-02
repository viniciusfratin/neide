#ifndef AIR_CONFIGURATION_H
#define AIR_CONFIGURATION_H

#include "air_interface/air_interface.h"
#include "pin_utils/adc_defs.h"

void AirConfiguration_Initialize(ADCIdentifier adc_identifier);
AirUserConfiguration AirConfiguration_GetAirUserConfiguration();

#endif