#include "idle_state.h"
#include <stdlib.h>

typedef struct IdleStateInternal
{
    HandleCoreState handle_idle_state;
    ShouldWakeUpCallback should_wake_up_callback;
    WokeState* woke_state_ptr;
} IdleStateImplementation;

static HandleCoreState* IdleState_HandleIdleState(void* state_instance);

IdleState IdleState_Construct(ShouldWakeUpCallback should_wake_up_callback, WokeState* woke_state_ptr)
{
    IdleState instance = (IdleState)malloc(sizeof(IdleStateImplementation));

    if(instance != NULL)
    {
        instance->handle_idle_state.state_instance = (void*)instance;
        instance->handle_idle_state.handle_state_callback = IdleState_HandleIdleState;
        instance->handle_idle_state.core_state = CORE_STATE_IDLE;

        instance->should_wake_up_callback = should_wake_up_callback;
        instance->woke_state_ptr = woke_state_ptr;
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

HandleCoreState* IdleState_GetHandleCoreState(IdleState instance)
{
    return &instance->handle_idle_state;
}

static HandleCoreState* IdleState_HandleIdleState(void* state_instance)
{
    IdleState instance = (IdleState)state_instance;
    HandleCoreState* next_handle_core_state = NULL;

    if(instance->should_wake_up_callback())
    {
        next_handle_core_state = WokeState_GetHandleCoreState(*(instance->woke_state_ptr));
    }

    else
    {
        next_handle_core_state = IdleState_GetHandleCoreState(instance);
    }

    return next_handle_core_state;
}
