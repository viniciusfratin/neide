#include "woke_state.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include <stdlib.h>

typedef struct WokeStateInternal
{
    CoreStateInterface woke_state_interface;
    CoreState core_state;
    CoreStateInterface* soil_humidity_check_state_interface_ptr;
} WokeStateImplementation;

static CoreStateInterface WokeState_ExecuteWokeState(void* object_instance);
static CoreState WokeState_GetCoreState(void* object_instance);

WokeState WokeState_Construct(CoreStateInterface* soil_humidity_check_state_interface_ptr)
{
    WokeState instance = (WokeState)malloc(sizeof(WokeStateImplementation));

    if(instance != NULL)
    {
        instance->woke_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            WokeState_GetCoreState,
            WokeState_ExecuteWokeState
        );

        if(instance->woke_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_WOKE;
            instance->soil_humidity_check_state_interface_ptr = soil_humidity_check_state_interface_ptr;
        }
        else
        {
            instance = WOKE_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = WOKE_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void WokeState_Destruct(WokeState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->woke_state_interface));

        free(*instancePtr);
        (*instancePtr) = WOKE_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface WokeState_GetCoreStateInterface(WokeState instance)
{
    return instance->woke_state_interface;
}

static CoreStateInterface WokeState_ExecuteWokeState(void* object_instance)
{
    WokeState instance = (WokeState)object_instance;
    CoreStateInterface next_core_state_interface = *(instance->soil_humidity_check_state_interface_ptr);

    return next_core_state_interface;
}

static CoreState WokeState_GetCoreState(void* object_instance)
{
    WokeState instance = (WokeState)object_instance;
    
    return instance->core_state;
}
