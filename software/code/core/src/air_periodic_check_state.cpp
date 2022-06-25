#include "air_periodic_check_state.hpp"
#include "core_state_interface.hpp"
#include "core_state_interface_construction.hpp"
#include <stdlib.h>

typedef struct AirPeriodicCheckStateInternal
{
    CoreStateInterface air_periodic_check_state_interface;
    CoreState core_state;
    GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback;
    CoreStateInterface* irrigate_air_state_interface_ptr;
    CoreStateInterface* wrap_up_state_interface_ptr;
    int32_t maximum_period_seconds;
} AirPeriodicCheckStateImplementation;

static CoreStateInterface AirPeriodicCheckState_ExecuteAirPeriodicCheckState(void* object_instance);
static CoreState AirPeriodicCheckState_GetCoreState(void* object_instance);

AirPeriodicCheckState AirPeriodicCheckState_Construct(
    GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback,
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* wrap_up_state_interface_ptr,
    int32_t maximum_period_seconds
)
{
    AirPeriodicCheckState instance = (AirPeriodicCheckState)malloc(sizeof(AirPeriodicCheckStateImplementation));

    if(instance != NULL)
    {
        instance->air_periodic_check_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            AirPeriodicCheckState_GetCoreState,
            AirPeriodicCheckState_ExecuteAirPeriodicCheckState
        );

        if(instance->air_periodic_check_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_AIR_PERIODIC_CHECK;
            instance->get_time_from_last_irrigation_callback = get_time_from_last_irrigation_callback;
            instance->irrigate_air_state_interface_ptr = irrigate_air_state_interface_ptr;
            instance->wrap_up_state_interface_ptr = wrap_up_state_interface_ptr;
            instance->maximum_period_seconds = maximum_period_seconds;
        }
        else
        {
            instance = AIR_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = AIR_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void AirPeriodicCheckState_Destruct(AirPeriodicCheckState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->air_periodic_check_state_interface));

        free(*instancePtr);
        (*instancePtr) = AIR_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface AirPeriodicCheckState_GetCoreStateInterface(AirPeriodicCheckState instance)
{
    return instance->air_periodic_check_state_interface;
}

static CoreStateInterface AirPeriodicCheckState_ExecuteAirPeriodicCheckState(void* object_instance)
{
    AirPeriodicCheckState instance = (AirPeriodicCheckState)object_instance;
    CoreStateInterface next_core_state_interface = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    
    int32_t time_from_last_irrigation = instance->get_time_from_last_irrigation_callback();
    
    if(time_from_last_irrigation > instance->maximum_period_seconds)
    {
        next_core_state_interface = *(instance->irrigate_air_state_interface_ptr);
    }
    else
    {
        next_core_state_interface = *(instance->wrap_up_state_interface_ptr);
    }
    
    return next_core_state_interface;
}

static CoreState AirPeriodicCheckState_GetCoreState(void* object_instance)
{
    AirPeriodicCheckState instance = (AirPeriodicCheckState)object_instance;
    
    return instance->core_state;
}
