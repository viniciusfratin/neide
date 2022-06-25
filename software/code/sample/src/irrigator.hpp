#ifndef IRRIGATOR_H
#define IRRIGATOR_H

#include "irrigator_interface.hpp"
#include <stdint.h>

typedef struct IrrigatorInternal* Irrigator;

#define IRRIGATOR_INVALID_INSTANCE ((Irrigator)NULL)


IrrigatorInterface Irrigator_GetIrrigatorInterface(Irrigator instance);
int32_t Irrigator_GetLastIrrigationTime(Irrigator instance);


Irrigator Irrigator_Construct();
void Irrigator_Destruct(Irrigator* instancePtr);


#endif