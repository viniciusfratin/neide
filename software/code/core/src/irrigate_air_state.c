#include "irrigate_air_state.h"
#include "irrigator_interface.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include <stdlib.h>

typedef struct IrrigateAirStateInternal
{
    CoreStateInterface irrigate_air_state_interface;
    CoreState core_state;
    CoreStateInterface* wrap_up_state_interface_ptr;
    IrrigatorInterface* air_irrigator_interface_ptr;
    int32_t irrigation_time_seconds;
} IrrigateAirStateImplementation;

static CoreStateInterface IrrigateAirState_ExecuteIrrigateAirState(void* object_instance);
static CoreState IrrigateAirState_GetCoreState(void* object_instance);

IrrigateAirState IrrigateAirState_Construct(
    CoreStateInterface* wrap_up_state_interface_ptr,
    IrrigatorInterface* air_irrigator_interface_ptr,
    int32_t irrigation_time_seconds)
{
    IrrigateAirState instance = (IrrigateAirState)malloc(sizeof(IrrigateAirStateImplementation));

    if(instance != NULL)
    {
        instance->irrigate_air_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            IrrigateAirState_GetCoreState,
            IrrigateAirState_ExecuteIrrigateAirState
        );

        if(instance->irrigate_air_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_IRRIGATE_AIR;
            instance->wrap_up_state_interface_ptr = wrap_up_state_interface_ptr;
            instance->air_irrigator_interface_ptr = air_irrigator_interface_ptr;
            instance->irrigation_time_seconds = irrigation_time_seconds;
        }
        else
        {
            instance = IRRIGATE_AIR_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = IRRIGATE_AIR_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void IrrigateAirState_Destruct(IrrigateAirState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->irrigate_air_state_interface));

        free(*instancePtr);
        (*instancePtr) = IRRIGATE_AIR_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface IrrigateAirState_GetCoreStateInterface(IrrigateAirState instance)
{
    return instance->irrigate_air_state_interface;
}

static CoreStateInterface IrrigateAirState_ExecuteIrrigateAirState(void* object_instance)
{
    IrrigateAirState instance = (IrrigateAirState)object_instance;
    CoreStateInterface next_core_state_interface = *(instance->wrap_up_state_interface_ptr);
    
    IrrigatorInterface_Irrigate(*(instance->air_irrigator_interface_ptr), instance->irrigation_time_seconds);
    
    return next_core_state_interface;
}

static CoreState IrrigateAirState_GetCoreState(void* object_instance)
{
    IrrigateAirState instance = (IrrigateAirState)object_instance;
    
    return instance->core_state;
}
