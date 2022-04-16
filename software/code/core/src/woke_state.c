#include "woke_state.h"
#include <stdlib.h>

typedef struct WokeStateInternal
{
    CoreStateHandle handle_woke_state;
} WokeStateImplementation;

static CoreStateHandle WokeState_HandleWokeState(void* state_instance);

WokeState WokeState_Construct()
{
    WokeState instance = (WokeState)malloc(sizeof(WokeStateImplementation));

    if(instance != NULL)
    {
        instance->handle_woke_state = CoreStateHandle_Construct(
            (void*)instance,
            CORE_STATE_WOKE,
            WokeState_HandleWokeState
        );

        if(instance->handle_woke_state == CORE_STATE_HANDLE_INVALID_INSTANCE)
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
        free(*instancePtr);
        (*instancePtr) = WOKE_STATE_INVALID_INSTANCE;
    }
}

CoreStateHandle WokeState_GetCoreStateHandle(WokeState instance)
{
    return instance->handle_woke_state;
}

static CoreStateHandle WokeState_HandleWokeState(void* state_instance)
{
    WokeState instance = (WokeState)state_instance;
    CoreStateHandle next_core_state_handle = WokeState_GetCoreStateHandle(instance);

    return next_core_state_handle;
}
