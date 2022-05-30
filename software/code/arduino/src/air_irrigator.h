#ifndef AIR_IRRIGATOR_H
#define AIR_IRRIGATOR_H

#include "irrigator_interface.h"
#include "clock/clock.h"
#include <stdint.h>

typedef struct AirIrrigatorInternal* AirIrrigator;

#define AIR_IRRIGATOR_INVALID_INSTANCE ((AirIrrigator)NULL)


IrrigatorInterface AirIrrigator_GetIrrigatorInterface(AirIrrigator instance);
int32_t AirIrrigator_GetTimeFromLastIrrigation(AirIrrigator instance);


AirIrrigator AirIrrigator_Construct(GetCurrentTimeSecondsCallback get_current_time_seconds_callback, volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin);
void AirIrrigator_Destruct(AirIrrigator* instancePtr);


#endif