#ifndef AIR_INTERFACE_H
#define AIR_INTERFACE_H

#include "air_humidity_check_state.hpp"

typedef struct AirInformationInternal
{
    float relative_humidity;
    float temperature;
} AirInformation;

typedef struct AirUserConfigurationInterface
{
    float relative_humidity_threshold;
} AirUserConfiguration;

typedef AirInformation (*GetAirInformationCallback)();
typedef AirUserConfiguration (*GetAirUserConfigurationCallback)();

void AirInterface_Initialize(GetAirInformationCallback get_air_information_callback, 
    GetAirUserConfigurationCallback get_air_user_configuration_callback
);
AirHumidityInformation AirInterface_GetAirHumidityInformation();

#endif