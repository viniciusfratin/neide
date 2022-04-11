#include "woke_state.h"
#include <stdlib.h>

typedef struct WokeStateInternal
{
    HandleCoreState handle_woke_state;
} WokeStateImplementation;

static HandleCoreState* WokeState_HandleWokeState(void* state_instance);

WokeState WokeState_Construct()
{
    WokeState instance = (WokeState)malloc(sizeof(WokeStateImplementation));

    if(instance != NULL)
    {
        instance->handle_woke_state.state_instance = (void*)instance;
        instance->handle_woke_state.handle_state_callback = WokeState_HandleWokeState;
        instance->handle_woke_state.core_state = CORE_STATE_WOKE;
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
        free(*instancePtr);
        (*instancePtr) = WOKE_STATE_INVALID_INSTANCE;
    }
}

HandleCoreState* WokeState_GetHandleCoreState(WokeState instance)
{
    return &instance->handle_woke_state;
}

static HandleCoreState* WokeState_HandleWokeState(void* state_instance)
{
    WokeState instance = (WokeState)state_instance;
    HandleCoreState* next_handle_core_state = WokeState_GetHandleCoreState(instance);

    return next_handle_core_state;
}
