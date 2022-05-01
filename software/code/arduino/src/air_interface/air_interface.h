#ifndef AIR_INTERFACE_H
#define AIR_INTERFACE_H

#include "air_humidity_check_state.h"

typedef struct AirInformationInternal
{
    float relative_humidity;
    float temperature;
} AirInformation;

typedef AirInformation (*GetAirInformationCallback)();

void AirInterface_Initialize(GetAirInformationCallback get_air_information_callback);
AirHumidityInformation AirInterface_GetAirHumidityInformation();

#endif