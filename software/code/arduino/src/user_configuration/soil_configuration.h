#ifndef SOIL_CONFIGURATION_H
#define SOIL_CONFIGURATION_H

#include "soil_interface/soil_interface.h"
#include "pin_utils/adc_defs.h"

void SoilConfiguration_Initialize(ADCIdentifier adc_identifier);
SoilUserConfiguration SoilConfiguration_GetSoilUserConfiguration();

#endif