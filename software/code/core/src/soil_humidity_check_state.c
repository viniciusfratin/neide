#include "soil_humidity_check_state.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include <stdlib.h>

typedef struct SoilHumidityCheckStateInternal
{
    CoreStateInterface soil_humidity_check_state_interface;
    CoreState core_state;
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback;
    CoreStateInterface* irrigate_soil_state_interface_ptr;
    CoreStateInterface* soil_periodic_check_state_interface_ptr;
} SoilHumidityCheckStateImplementation;

static CoreStateInterface SoilHumidityCheckState_ExecuteSoilHumidityCheckState(void* state_instance);
static CoreState SoilHumidityCheckState_GetCoreState(void* state_instance);

SoilHumidityCheckState SoilHumidityCheckState_Construct(
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
    CoreStateInterface* irrigate_soil_state_interface_ptr,
    CoreStateInterface* soil_periodic_check_state_interface_ptr
)
{
    SoilHumidityCheckState instance = (SoilHumidityCheckState)malloc(sizeof(SoilHumidityCheckStateImplementation));

    if(instance != NULL)
    {
        instance->soil_humidity_check_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            SoilHumidityCheckState_GetCoreState,
            SoilHumidityCheckState_ExecuteSoilHumidityCheckState
        );

        if(instance->soil_humidity_check_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_SOIL_HUMIDITY_CHECK;
            instance->get_soil_humidity_information_callback = get_soil_humidity_information_callback;
            instance->irrigate_soil_state_interface_ptr = irrigate_soil_state_interface_ptr;
            instance->soil_periodic_check_state_interface_ptr = soil_periodic_check_state_interface_ptr;
        }
        else
        {
            instance = SOIL_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = SOIL_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void SoilHumidityCheckState_Destruct(SoilHumidityCheckState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->soil_humidity_check_state_interface));

        free(*instancePtr);
        (*instancePtr) = SOIL_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface SoilHumidityCheckState_GetCoreStateInterface(SoilHumidityCheckState instance)
{
    return instance->soil_humidity_check_state_interface;
}

static CoreStateInterface SoilHumidityCheckState_ExecuteSoilHumidityCheckState(void* state_instance)
{
    SoilHumidityCheckState instance = (SoilHumidityCheckState)state_instance;
    CoreStateInterface next_core_state_interface = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    
    SoilHumidityInformation soil_humidity_information = instance->get_soil_humidity_information_callback();
    
    if(soil_humidity_information.current_relative_humidity < soil_humidity_information.relative_humidity_threshold)
    {
        next_core_state_interface = *(instance->irrigate_soil_state_interface_ptr);
    }
    else
    {
        next_core_state_interface = *(instance->soil_periodic_check_state_interface_ptr);
    }
    
    return next_core_state_interface;
}

static CoreState SoilHumidityCheckState_GetCoreState(void* state_instance)
{
    SoilHumidityCheckState instance = (SoilHumidityCheckState)state_instance;
    
    return instance->core_state;
}
