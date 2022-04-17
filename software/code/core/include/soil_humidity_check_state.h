#ifndef SOIL_HUMIDITY_CHECK_STATE_H
#define SOIL_HUMIDITY_CHECK_STATE_H

#include "core_state_interface.h"

typedef struct SoilHumidityCheckStateInternal* SoilHumidityCheckState;

#define SOIL_HUMIDITY_CHECK_STATE_INVALID_INSTANCE ((SoilHumidityCheckState)NULL)

typedef struct SoilHumidityInformationInternal
{
    float current_relative_humidity;
    float relative_humidity_threshold;
} SoilHumidityInformation;

typedef SoilHumidityInformation (*GetSoilHumidityInformationCallback)();


CoreStateInterface SoilHumidityCheckState_GetCoreStateInterface(SoilHumidityCheckState instance);


SoilHumidityCheckState SoilHumidityCheckState_Construct(GetSoilHumidityInformationCallback get_soil_humidity_information_callback);
void SoilHumidityCheckState_Destruct(SoilHumidityCheckState* instancePtr);


#endif