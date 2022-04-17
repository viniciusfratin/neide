#include "idle_state.h"
#include "core_state_interface_private.h"
#include <stdlib.h>

typedef struct IdleStateInternal
{
    CoreStateInterface idle_state_interface;
    CoreState core_state;
    ShouldWakeUpCallback should_wake_up_callback;
    CoreStateInterface* woke_state_interface_ptr;
} IdleStateImplementation;

static CoreStateInterface IdleState_ExecuteIdleState(void* state_instance);
static CoreState IdleState_GetCoreState(void* state_instance);

IdleState IdleState_Construct(ShouldWakeUpCallback should_wake_up_callback, CoreStateInterface* woke_state_interface_ptr)
{
    IdleState instance = (IdleState)malloc(sizeof(IdleStateImplementation));

    if(instance != NULL)
    {
        instance->idle_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            IdleState_GetCoreState,
            IdleState_ExecuteIdleState
        );

        if(instance->idle_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = CORE_STATE_IDLE;
            instance->should_wake_up_callback = should_wake_up_callback;
            instance->woke_state_interface_ptr = woke_state_interface_ptr;
        }
        else
        {
            instance = IDLE_STATE_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = IDLE_STATE_INVALID_INSTANCE;
    }

    return instance;
}

void IdleState_Destruct(IdleState* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->idle_state_interface));

        free(*instancePtr);
        (*instancePtr) = IDLE_STATE_INVALID_INSTANCE;
    }
}

CoreStateInterface IdleState_GetCoreStateInterface(IdleState instance)
{
    return instance->idle_state_interface;
}

static CoreStateInterface IdleState_ExecuteIdleState(void* state_instance)
{
    IdleState instance = (IdleState)state_instance;
    CoreStateInterface next_core_state_interface = CORE_STATE_INTERFACE_INVALID_INSTANCE;

    if(instance->should_wake_up_callback())
    {
        next_core_state_interface = *(instance->woke_state_interface_ptr);
    }
    else
    {
        next_core_state_interface = IdleState_GetCoreStateInterface(instance);
    }

    return next_core_state_interface;
}

static CoreState IdleState_GetCoreState(void* state_instance)
{
    IdleState instance = (IdleState)state_instance;

    return instance->core_state;
}
