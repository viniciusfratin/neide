#include "irrigate_soil_state.h"
#include "soil_irrigator_interface.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include <stdlib.h>

typedef struct IrrigateSoilStateInternal
{
    CoreStateInterface irrigate_soil_state_interface;
    CoreState core_state;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    SoilIrrigatorInterface* soil_irrigator_interface_ptr;
    int irrigation_time_seconds;
} IrrigateSoilStateImplementation;

static CoreStateInterface IrrigateSoilState_ExecuteIrrigateSoilState(void* object_instance);
static CoreState IrrigateSoilState_GetCoreState(void* object_instance);

IrrigateSoilState IrrigateSoilState_Construct(
    CoreStateInterface* air_humidity_check_state_interface_ptr,
    SoilIrrigatorInterface* soil_irrigator_interface_ptr,
    int irrigation_time_seconds)
{
    IrrigateSoilState instance = (IrrigateSoilState)malloc(sizeof(IrrigateSoilStateImplementation));

    if(instance != NULL)
    {
        instance->irrigate_soil_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            IrrigateSoilState_GetCoreState,
            IrrigateSoilState_ExecuteIrrigateSoilState
        );

        if(instance->irrigate_soil_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_IRRIGATE_SOIL;
            instance->air_humidity_check_state_interface_ptr = air_humidity_check_state_interface_ptr;
            instance->soil_irrigator_interface_ptr = soil_irrigator_interface_ptr;
            instance->irrigation_time_seconds = irrigation_time_seconds;
        }
        else
        {
            instance = IRRIGATE_SOIL_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = IRRIGATE_SOIL_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void IrrigateSoilState_Destruct(IrrigateSoilState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->irrigate_soil_state_interface));

        free(*instancePtr);
        (*instancePtr) = IRRIGATE_SOIL_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface IrrigateSoilState_GetCoreStateInterface(IrrigateSoilState instance)
{
    return instance->irrigate_soil_state_interface;
}

static CoreStateInterface IrrigateSoilState_ExecuteIrrigateSoilState(void* object_instance)
{
    IrrigateSoilState instance = (IrrigateSoilState)object_instance;
    CoreStateInterface next_core_state_interface = *(instance->air_humidity_check_state_interface_ptr);
    
    SoilIrrigatorInterface_IrrigateSoil(*(instance->soil_irrigator_interface_ptr), instance->irrigation_time_seconds);
    
    return next_core_state_interface;
}

static CoreState IrrigateSoilState_GetCoreState(void* object_instance)
{
    IrrigateSoilState instance = (IrrigateSoilState)object_instance;
    
    return instance->core_state;
}
