#ifndef HL69_SENSOR_HPP
#define HL69_SENSOR_HPP

#include "soil_interface/soil_interface.hpp"
#include "pin_utils/adc_defs.hpp"

void HL69_Initialize(ADCIdentifier adc_identifier);
SoilInformation HL69_GetSoilInformation();

#endif