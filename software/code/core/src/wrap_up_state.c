#include "wrap_up_state.h"
#include "core_state_interface.h"
#include "core_state_interface_construction.h"
#include "wrap_up_action_interface.h"
#include <stdlib.h>

typedef struct WrapUpStateInternal
{
    CoreStateInterface wrap_up_state_interface;
    CoreState core_state;
    WrapUpActionInterface* wrap_up_action_interface_ptr;
    CoreStateInterface* idle_state_interface_ptr;
} WrapUpStateImplementation;

static CoreStateInterface WrapUpState_ExecuteWrapUpState(void* object_instance);
static CoreState WrapUpState_GetCoreState(void* object_instance);

WrapUpState WrapUpState_Construct(WrapUpActionInterface* wrap_up_action_interface_ptr, CoreStateInterface* idle_state_interface_ptr)
{
    WrapUpState instance = (WrapUpState)malloc(sizeof(WrapUpStateImplementation));

    if(instance != NULL)
    {
        instance->wrap_up_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            WrapUpState_GetCoreState,
            WrapUpState_ExecuteWrapUpState
        );

        if(instance->wrap_up_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_WRAP_UP;
            instance->wrap_up_action_interface_ptr = wrap_up_action_interface_ptr;
            instance->idle_state_interface_ptr = idle_state_interface_ptr;
        }
        else
        {
            instance = WRAP_UP_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = WRAP_UP_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void WrapUpState_Destruct(WrapUpState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->wrap_up_state_interface));

        free(*instancePtr);
        (*instancePtr) = WRAP_UP_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface WrapUpState_GetCoreStateInterface(WrapUpState instance)
{
    return instance->wrap_up_state_interface;
}

static CoreStateInterface WrapUpState_ExecuteWrapUpState(void* object_instance)
{
    WrapUpState instance = (WrapUpState)object_instance;
    CoreStateInterface next_core_state_interface = *(instance->idle_state_interface_ptr);

    WrapUpActionInterface_WrapUp(*(instance->wrap_up_action_interface_ptr));
    
    return next_core_state_interface;
}

static CoreState WrapUpState_GetCoreState(void* object_instance)
{
    WrapUpState instance = (WrapUpState)object_instance;

    return instance->core_state;
}
