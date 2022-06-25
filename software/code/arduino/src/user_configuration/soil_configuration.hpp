#ifndef SOIL_CONFIGURATION_HPP
#define SOIL_CONFIGURATION_HPP

#include "soil_interface/soil_interface.hpp"
#include "pin_utils/adc_defs.hpp"

void SoilConfiguration_Initialize(ADCIdentifier adc_identifier);
SoilUserConfiguration SoilConfiguration_GetSoilUserConfiguration();

#endif