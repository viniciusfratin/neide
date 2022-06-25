#ifndef IRRIGATE_AIR_STATE_H
#define IRRIGATE_AIR_STATE_H

#include "core_state_interface.hpp"
#include "irrigator_interface.hpp"
#include <stdint.h>

typedef struct IrrigateAirStateInternal* IrrigateAirState;

#define IRRIGATE_AIR_STATE_INVALID_INSTANCE ((IrrigateAirState)NULL)


CoreStateInterface IrrigateAirState_GetCoreStateInterface(IrrigateAirState instance);


IrrigateAirState IrrigateAirState_Construct(
    CoreStateInterface* wrap_up_state_interface_ptr,
    IrrigatorInterface* air_irrigator_interface_ptr,
    int32_t irrigation_time_seconds);
void IrrigateAirState_Destruct(IrrigateAirState* instancePtr);


#endif