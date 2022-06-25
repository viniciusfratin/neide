#ifndef HL69_SENSOR_H
#define HL69_SENSOR_H

#include "soil_interface/soil_interface.hpp"
#include "pin_utils/adc_defs.hpp"

void HL69_Initialize(ADCIdentifier adc_identifier);
SoilInformation HL69_GetSoilInformation();

#endif