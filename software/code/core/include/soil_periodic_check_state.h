#ifndef SOIL_PERIODIC_CHECK_STATE_H
#define SOIL_PERIODIC_CHECK_STATE_H

#include "core_state_interface.h"

typedef struct SoilPeriodicCheckStateInternal* SoilPeriodicCheckState;

#define SOIL_PERIODIC_CHECK_STATE_INVALID_INSTANCE ((SoilPeriodicCheckState)NULL)

typedef int (*GetTimeFromLastSoilIrrigationCallback)();


CoreStateInterface SoilPeriodicCheckState_GetCoreStateInterface(SoilPeriodicCheckState instance);


SoilPeriodicCheckState SoilPeriodicCheckState_Construct(
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback,
    CoreStateInterface* irrigate_soil_state_interface_ptr,
    CoreStateInterface* air_humidity_check_state_interface_ptr,
    int maximum_period_seconds
);
void SoilPeriodicCheckState_Destruct(SoilPeriodicCheckState* instancePtr);


#endif