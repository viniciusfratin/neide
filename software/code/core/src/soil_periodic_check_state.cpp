#include "soil_periodic_check_state.hpp"
#include "core_state_interface.hpp"
#include "core_state_interface_construction.hpp"
#include <stdlib.h>

typedef struct SoilPeriodicCheckStateInternal
{
    CoreStateInterface soil_periodic_check_state_interface;
    CoreState core_state;
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback;
    CoreStateInterface* irrigate_soil_state_interface_ptr;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    int32_t maximum_period_seconds;
} SoilPeriodicCheckStateImplementation;

static CoreStateInterface SoilPeriodicCheckState_ExecuteSoilPeriodicCheckState(void* object_instance);
static CoreState SoilPeriodicCheckState_GetCoreState(void* object_instance);

SoilPeriodicCheckState SoilPeriodicCheckState_Construct(
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback,
    CoreStateInterface* irrigate_soil_state_interface_ptr,
    CoreStateInterface* air_humidity_check_state_interface_ptr,
    int32_t maximum_period_seconds
)
{
    SoilPeriodicCheckState instance = (SoilPeriodicCheckState)malloc(sizeof(SoilPeriodicCheckStateImplementation));

    if(instance != NULL)
    {
        instance->soil_periodic_check_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            SoilPeriodicCheckState_GetCoreState,
            SoilPeriodicCheckState_ExecuteSoilPeriodicCheckState
        );

        if(instance->soil_periodic_check_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_SOIL_PERIODIC_CHECK;
            instance->get_time_from_last_irrigation_callback = get_time_from_last_irrigation_callback;
            instance->irrigate_soil_state_interface_ptr = irrigate_soil_state_interface_ptr;
            instance->air_humidity_check_state_interface_ptr = air_humidity_check_state_interface_ptr;
            instance->maximum_period_seconds = maximum_period_seconds;
        }
        else
        {
            instance = SOIL_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = SOIL_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void SoilPeriodicCheckState_Destruct(SoilPeriodicCheckState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->soil_periodic_check_state_interface));

        free(*instancePtr);
        (*instancePtr) = SOIL_PERIODIC_CHECK_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface SoilPeriodicCheckState_GetCoreStateInterface(SoilPeriodicCheckState instance)
{
    return instance->soil_periodic_check_state_interface;
}

static CoreStateInterface SoilPeriodicCheckState_ExecuteSoilPeriodicCheckState(void* object_instance)
{
    SoilPeriodicCheckState instance = (SoilPeriodicCheckState)object_instance;
    CoreStateInterface next_core_state_interface = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    
    int32_t time_from_last_irrigation = instance->get_time_from_last_irrigation_callback();
    
    if(time_from_last_irrigation > instance->maximum_period_seconds)
    {
        next_core_state_interface = *(instance->irrigate_soil_state_interface_ptr);
    }
    else
    {
        next_core_state_interface = *(instance->air_humidity_check_state_interface_ptr);
    }
    
    return next_core_state_interface;
}

static CoreState SoilPeriodicCheckState_GetCoreState(void* object_instance)
{
    SoilPeriodicCheckState instance = (SoilPeriodicCheckState)object_instance;
    
    return instance->core_state;
}
