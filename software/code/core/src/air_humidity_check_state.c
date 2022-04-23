#include "air_humidity_check_state.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include <stdlib.h>

typedef struct AirHumidityCheckStateInternal
{
    CoreStateInterface air_humidity_check_state_interface;
    CoreState core_state;
    GetAirHumidityInformationCallback get_air_humidity_information_callback;
    CoreStateInterface* irrigate_air_state_interface_ptr;
    CoreStateInterface* air_periodic_check_state_interface_ptr;
} AirHumidityCheckStateImplementation;

static CoreStateInterface AirHumidityCheckState_ExecuteAirHumidityCheckState(void* object_instance);
static CoreState AirHumidityCheckState_GetCoreState(void* object_instance);

AirHumidityCheckState AirHumidityCheckState_Construct(
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* air_periodic_check_state_interface_ptr
)
{
    AirHumidityCheckState instance = (AirHumidityCheckState)malloc(sizeof(AirHumidityCheckStateImplementation));

    if(instance != NULL)
    {
        instance->air_humidity_check_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            AirHumidityCheckState_GetCoreState,
            AirHumidityCheckState_ExecuteAirHumidityCheckState
        );

        if(instance->air_humidity_check_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_AIR_HUMIDITY_CHECK;
            instance->get_air_humidity_information_callback = get_air_humidity_information_callback;
            instance->irrigate_air_state_interface_ptr = irrigate_air_state_interface_ptr;
            instance->air_periodic_check_state_interface_ptr = air_periodic_check_state_interface_ptr;
        }
        else
        {
            instance = AIR_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = AIR_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void AirHumidityCheckState_Destruct(AirHumidityCheckState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->air_humidity_check_state_interface));

        free(*instancePtr);
        (*instancePtr) = AIR_HUMIDITY_CHECK_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface AirHumidityCheckState_GetCoreStateInterface(AirHumidityCheckState instance)
{
    return instance->air_humidity_check_state_interface;
}

static CoreStateInterface AirHumidityCheckState_ExecuteAirHumidityCheckState(void* object_instance)
{
    AirHumidityCheckState instance = (AirHumidityCheckState)object_instance;
    CoreStateInterface next_core_state_interface = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    
    AirHumidityInformation air_humidity_information = instance->get_air_humidity_information_callback();
    
    if(air_humidity_information.current_relative_humidity < air_humidity_information.relative_humidity_threshold)
    {
        next_core_state_interface = *(instance->irrigate_air_state_interface_ptr);
    }
    else
    {
        next_core_state_interface = *(instance->air_periodic_check_state_interface_ptr);
    }
    
    return next_core_state_interface;
}

static CoreState AirHumidityCheckState_GetCoreState(void* object_instance)
{
    AirHumidityCheckState instance = (AirHumidityCheckState)object_instance;
    
    return instance->core_state;
}
