#ifndef AIR_HUMIDITY_CHECK_STATE_H
#define AIR_HUMIDITY_CHECK_STATE_H

#include "core_state_interface.h"

typedef struct AirHumidityCheckStateInternal* AirHumidityCheckState;

#define AIR_HUMIDITY_CHECK_STATE_INVALID_INSTANCE ((AirHumidityCheckState)NULL)

typedef struct AirHumidityInformationInternal
{
    float current_relative_humidity;
    float relative_humidity_threshold;
} AirHumidityInformation;

typedef AirHumidityInformation (*GetAirHumidityInformationCallback)();


CoreStateInterface AirHumidityCheckState_GetCoreStateInterface(AirHumidityCheckState instance);


AirHumidityCheckState AirHumidityCheckState_Construct(
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* air_periodic_check_state_interface_ptr
);
void AirHumidityCheckState_Destruct(AirHumidityCheckState* instancePtr);


#endif