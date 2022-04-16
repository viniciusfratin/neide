#include "idle_state.h"
#include <stdlib.h>

typedef struct IdleStateInternal
{
    CoreStateHandle idle_state_handle;
    ShouldWakeUpCallback should_wake_up_callback;
    WokeState* woke_state_ptr;
} IdleStateImplementation;

static CoreStateHandle IdleState_HandleIdleState(void* state_instance);

IdleState IdleState_Construct(ShouldWakeUpCallback should_wake_up_callback, WokeState* woke_state_ptr)
{
    IdleState instance = (IdleState)malloc(sizeof(IdleStateImplementation));

    if(instance != NULL)
    {
        instance->idle_state_handle = CoreStateHandle_Construct(
            (void*)instance,
            CORE_STATE_IDLE,
            IdleState_HandleIdleState
        );

        if(instance->idle_state_handle != CORE_STATE_HANDLE_INVALID_INSTANCE)
        {
            instance->should_wake_up_callback = should_wake_up_callback;
            instance->woke_state_ptr = woke_state_ptr;
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
        free(*instancePtr);
        (*instancePtr) = IDLE_STATE_INVALID_INSTANCE;
    }
}

CoreStateHandle IdleState_GetCoreStateHandle(IdleState instance)
{
    return instance->idle_state_handle;
}

static CoreStateHandle IdleState_HandleIdleState(void* state_instance)
{
    IdleState instance = (IdleState)state_instance;
    CoreStateHandle next_core_state_handle = CORE_STATE_HANDLE_INVALID_INSTANCE;

    if(instance->should_wake_up_callback())
    {
        next_core_state_handle = WokeState_GetCoreStateHandle(*(instance->woke_state_ptr));
    }
    else
    {
        next_core_state_handle = IdleState_GetCoreStateHandle(instance);
    }

    return next_core_state_handle;
}
