#ifndef SOIL_INTERFACE_H
#define SOIL_INTERFACE_H

#include "soil_humidity_check_state.hpp"

typedef struct SoilInformationInternal
{
    float relative_humidity;
} SoilInformation;

typedef struct SoilUserConfigurationInterface
{
    float relative_humidity_threshold;
} SoilUserConfiguration;

typedef SoilInformation (*GetSoilInformationCallback)();
typedef SoilUserConfiguration (*GetSoilUserConfigurationCallback)();

void SoilInterface_Initialize(GetSoilInformationCallback get_soil_information_callback, 
    GetSoilUserConfigurationCallback get_soil_user_configuration_callback
);
SoilHumidityInformation SoilInterface_GetSoilHumidityInformation();

#endif