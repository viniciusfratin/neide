#ifndef IRRIGATE_SOIL_STATE_H
#define IRRIGATE_SOIL_STATE_H

#include "core_state_interface.h"
#include "irrigator_interface.h"
#include <stdint.h>

typedef struct IrrigateSoilStateInternal* IrrigateSoilState;

#define IRRIGATE_SOIL_STATE_INVALID_INSTANCE ((IrrigateSoilState)NULL)


CoreStateInterface IrrigateSoilState_GetCoreStateInterface(IrrigateSoilState instance);


IrrigateSoilState IrrigateSoilState_Construct(
    CoreStateInterface* air_humidity_check_state_interface_ptr,
    IrrigatorInterface* soil_irrigator_interface_ptr,
    int32_t irrigation_time_seconds);
void IrrigateSoilState_Destruct(IrrigateSoilState* instancePtr);


#endif