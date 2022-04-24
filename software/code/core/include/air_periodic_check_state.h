#ifndef AIR_PERIODIC_CHECK_STATE_H
#define AIR_PERIODIC_CHECK_STATE_H

#include "core_state_interface.h"

typedef struct AirPeriodicCheckStateInternal* AirPeriodicCheckState;

#define AIR_PERIODIC_CHECK_STATE_INVALID_INSTANCE ((AirPeriodicCheckState)NULL)

typedef int (*GetTimeFromLastIrrigationCallback)();


CoreStateInterface AirPeriodicCheckState_GetCoreStateInterface(AirPeriodicCheckState instance);


AirPeriodicCheckState AirPeriodicCheckState_Construct(
    GetTimeFromLastIrrigationCallback get_time_from_last_irrigation_callback,
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* wrap_up_state_interface_ptr,
    int maximum_period_seconds
);
void AirPeriodicCheckState_Destruct(AirPeriodicCheckState* instancePtr);


#endif