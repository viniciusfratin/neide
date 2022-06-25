#ifndef STANDARD_CONFIGURATION_H
#define STANDARD_CONFIGURATION_H

#include "core.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "idle_state.hpp"
#include "soil_humidity_check_state.hpp"
#include "soil_periodic_check_state.hpp"
#include "air_humidity_check_state.hpp"
#include "air_periodic_check_state.hpp"
#include <stdint.h>

typedef struct StandardConfigurationInternal* StandardConfiguration;

#define STANDARD_CONFIGURATION_INVALID_INSTANCE ((StandardConfiguration)NULL)


SystemCore StandardConfiguration_GetSystemCore(StandardConfiguration instance);


StandardConfiguration StandardConfiguration_Construct(
    ShouldWakeUpCallback should_wake_up_callback,
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
    int32_t soil_periodic_check_maximum_period,
    IrrigatorInterface* soil_irrigator_ptr,
    int32_t soil_irrigation_time,
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
    int32_t air_periodic_check_maximum_period,
    IrrigatorInterface* air_irrigator_ptr,
    int32_t air_irrigation_time,
    WrapUpActionInterface* wrap_up_action_ptr);
void StandardConfiguration_Destruct(StandardConfiguration* instancePtr);



#endif