#ifndef SOIL_IRRIGATOR_H
#define SOIL_IRRIGATOR_H

#include "irrigator_interface.hpp"
#include "clock/clock.hpp"
#include <cstdint>

typedef struct SoilIrrigatorInternal* SoilIrrigator;

#define SOIL_IRRIGATOR_INVALID_INSTANCE ((SoilIrrigator)NULL)


IrrigatorInterface SoilIrrigator_GetIrrigatorInterface(SoilIrrigator instance);
int32_t SoilIrrigator_GetTimeFromLastIrrigation(SoilIrrigator instance);


SoilIrrigator SoilIrrigator_Construct(GetCurrentTimeSecondsCallback get_current_time_seconds_callback, volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin);
void SoilIrrigator_Destruct(SoilIrrigator* instancePtr);


#endif