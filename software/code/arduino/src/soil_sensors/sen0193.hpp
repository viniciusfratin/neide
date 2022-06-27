#ifndef SEN0193_SENSOR_HPP
#define SEN0193_SENSOR_HPP

#include "soil_interface/soil_interface.hpp"
#include "pin_utils/adc_defs.hpp"

void SEN0193_Initialize(ADCIdentifier adc_identifier);
SoilInformation SEN0193_GetSoilInformation();

#endif