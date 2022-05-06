#ifndef IRRIGATOR_H
#define IRRIGATOR_H

#include "irrigator_interface.h"
#include "clock/clock.h"
#include <stdint.h>

typedef struct IrrigatorInternal* Irrigator;

#define IRRIGATOR_INVALID_INSTANCE ((Irrigator)NULL)


IrrigatorInterface Irrigator_GetIrrigatorInterface(Irrigator instance);
int Irrigator_GetTimeFromLastIrrigation(Irrigator instance);


Irrigator Irrigator_Construct(GetCurrentTimeSecondsCallback get_current_time_seconds_callback, volatile uint8_t* pin_ddr_ptr, volatile uint8_t* pin_port_ptr, uint8_t pin);
void Irrigator_Destruct(Irrigator* instancePtr);


#endif