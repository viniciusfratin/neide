#ifndef IRRIGATE_SOIL_STATE_H
#define IRRIGATE_SOIL_STATE_H

#include "core_state_interface.h"
#include "soil_irrigator_interface.h"

typedef struct IrrigateSoilStateInternal* IrrigateSoilState;

#define IRRIGATE_SOIL_STATE_INVALID_INSTANCE ((IrrigateSoilState)NULL)


CoreStateInterface IrrigateSoilState_GetCoreStateInterface(IrrigateSoilState instance);


IrrigateSoilState IrrigateSoilState_Construct(SoilIrrigatorInterface* soil_irrigator_interface_ptr, int irrigation_time_seconds);
void IrrigateSoilState_Destruct(IrrigateSoilState* instancePtr);


#endif