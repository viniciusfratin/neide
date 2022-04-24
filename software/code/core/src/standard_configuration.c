#include "standard_configuration.h"
#include "idle_state.h"
#include "woke_state.h"
#include "soil_humidity_check_state.h"
#include "soil_periodic_check_state.h"
#include "irrigate_soil_state.h"
#include "air_humidity_check_state.h"
#include "air_periodic_check_state.h"
#include "irrigate_air_state.h"
#include "wrap_up_state.h"
#include <stdlib.h>

typedef struct StandardConfigurationInternal
{
    SystemCore system_core;
    IdleState idle_state;
    CoreStateInterface idle_state_interface;
    WokeState woke_state;
    CoreStateInterface woke_state_interface;
    SoilHumidityCheckState soil_humidity_check_state;
    CoreStateInterface soil_humidity_check_state_interface;
    SoilPeriodicCheckState soil_periodic_check_state;
    CoreStateInterface soil_periodic_check_state_interface;
    IrrigateSoilState irrigate_soil_state;
    CoreStateInterface irrigate_soil_state_interface;
    AirHumidityCheckState air_humidity_check_state;
    CoreStateInterface air_humidity_check_state_interface;
    AirPeriodicCheckState air_periodic_check_state;
    CoreStateInterface air_periodic_check_state_interface;
    IrrigateAirState irrigate_air_state;
    CoreStateInterface irrigate_air_state_interface;
    WrapUpState wrap_up_state;
    CoreStateInterface wrap_up_state_interface;
} StandardConfigurationImplementation;

StandardConfiguration StandardConfiguration_Construct(
    ShouldWakeUpCallback should_wake_up_callback,
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
    int soil_periodic_check_maximum_period,
    IrrigatorInterface* soil_irrigator_ptr,
    int soil_irrigation_time,
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
    int air_periodic_check_maximum_period,
    IrrigatorInterface* air_irrigator_ptr,
    int air_irrigation_time,
    WrapUpActionInterface* wrap_up_action_ptr)
{
    StandardConfiguration instance = (StandardConfiguration)malloc(sizeof(StandardConfigurationImplementation));

    if(instance != NULL)
    {
        IdleState idle_state = IdleState_Construct(should_wake_up_callback, &instance->woke_state_interface);
        WokeState woke_state = WokeState_Construct(&instance->soil_humidity_check_state_interface);
        SoilHumidityCheckState soil_humidity_check_state = SoilHumidityCheckState_Construct(
            get_soil_humidity_information_callback,
            &instance->irrigate_soil_state_interface,
            &instance->soil_periodic_check_state_interface
        );
        SoilPeriodicCheckState soil_periodic_check_state = SoilPeriodicCheckState_Construct(
            get_time_from_last_soil_irrigation_callback,
            &instance->irrigate_soil_state_interface,
            &instance->air_humidity_check_state_interface,
            soil_periodic_check_maximum_period
        );
        IrrigateSoilState irrigate_soil_state = IrrigateSoilState_Construct(
            &instance->air_humidity_check_state_interface,
            soil_irrigator_ptr,
            soil_irrigation_time
        );
        AirHumidityCheckState air_humidity_check_state = AirHumidityCheckState_Construct(
            get_air_humidity_information_callback,
            &instance->irrigate_air_state_interface,
            &instance->air_periodic_check_state_interface
        );
        AirPeriodicCheckState air_periodic_check_state = AirPeriodicCheckState_Construct(
            get_time_from_last_air_irrigation_callback,
            &instance->irrigate_air_state_interface,
            &instance->wrap_up_state_interface,
            air_periodic_check_maximum_period
        );
        IrrigateAirState irrigate_air_state = IrrigateAirState_Construct(
            &instance->wrap_up_state_interface,
            air_irrigator_ptr,
            air_irrigation_time
        );
        WrapUpState wrap_up_state = WrapUpState_Construct(
            wrap_up_action_ptr,
            &instance->idle_state_interface
        );

        if(idle_state != IDLE_STATE_INVALID_INSTANCE &&
            woke_state != WOKE_STATE_INVALID_INSTANCE &&
            soil_humidity_check_state != SOIL_HUMIDITY_CHECK_STATE_INVALID_INSTANCE &&
            soil_periodic_check_state != SOIL_PERIODIC_CHECK_STATE_INVALID_INSTANCE &&
            irrigate_soil_state != IRRIGATE_SOIL_STATE_INVALID_INSTANCE &&
            air_humidity_check_state != AIR_HUMIDITY_CHECK_STATE_INVALID_INSTANCE &&
            air_periodic_check_state != AIR_PERIODIC_CHECK_STATE_INVALID_INSTANCE &&
            irrigate_air_state != IRRIGATE_AIR_STATE_INVALID_INSTANCE &&
            wrap_up_state != WRAP_UP_STATE_INVALID_INSTANCE)
        {
            instance->idle_state_interface = IdleState_GetCoreStateInterface(idle_state);
            instance->woke_state_interface = WokeState_GetCoreStateInterface(woke_state);
            instance->soil_humidity_check_state_interface = SoilHumidityCheckState_GetCoreStateInterface(soil_humidity_check_state);
            instance->soil_periodic_check_state_interface = SoilPeriodicCheckState_GetCoreStateInterface(soil_periodic_check_state);
            instance->irrigate_soil_state_interface = IrrigateSoilState_GetCoreStateInterface(irrigate_soil_state);
            instance->air_humidity_check_state_interface = AirHumidityCheckState_GetCoreStateInterface(air_humidity_check_state);
            instance->air_periodic_check_state_interface = AirPeriodicCheckState_GetCoreStateInterface(air_periodic_check_state);
            instance->irrigate_air_state_interface = IrrigateAirState_GetCoreStateInterface(irrigate_air_state);
            instance->wrap_up_state_interface = WrapUpState_GetCoreStateInterface(wrap_up_state);

            SystemCore system_core = SystemCore_Construct(instance->idle_state_interface);
            if(system_core != SYSTEM_CORE_INVALID_INSTANCE)
            {
                instance->idle_state = idle_state;
                instance->woke_state = woke_state;
                instance->soil_humidity_check_state = soil_humidity_check_state;
                instance->soil_periodic_check_state = soil_periodic_check_state;
                instance->irrigate_soil_state = irrigate_soil_state;
                instance->air_humidity_check_state = air_humidity_check_state;
                instance->air_periodic_check_state = air_periodic_check_state;
                instance->irrigate_air_state = irrigate_air_state;
                instance->wrap_up_state = wrap_up_state;

                instance->system_core = system_core;
            }
            else
            {
                instance = STANDARD_CONFIGURATION_INVALID_INSTANCE;
            }
        }
        else
        {
            instance = STANDARD_CONFIGURATION_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = STANDARD_CONFIGURATION_INVALID_INSTANCE;
    }

    return instance;
}

void StandardConfiguration_Destruct(StandardConfiguration* instancePtr)
{
    if(instancePtr != NULL)
    {
        IdleState_Destruct(&((*instancePtr)->idle_state));
        WokeState_Destruct(&((*instancePtr)->woke_state));
        SoilHumidityCheckState_Destruct(&((*instancePtr)->soil_humidity_check_state));
        SoilPeriodicCheckState_Destruct(&((*instancePtr)->soil_periodic_check_state));
        IrrigateSoilState_Destruct(&((*instancePtr)->irrigate_soil_state));
        AirHumidityCheckState_Destruct(&((*instancePtr)->air_humidity_check_state));
        AirPeriodicCheckState_Destruct(&((*instancePtr)->air_periodic_check_state));
        IrrigateAirState_Destruct(&((*instancePtr)->irrigate_air_state));
        WrapUpState_Destruct(&((*instancePtr)->wrap_up_state));

        free(*instancePtr);
        (*instancePtr) = STANDARD_CONFIGURATION_INVALID_INSTANCE;
    }
}

SystemCore StandardConfiguration_GetSystemCore(StandardConfiguration instance)
{
    return instance->system_core;
}