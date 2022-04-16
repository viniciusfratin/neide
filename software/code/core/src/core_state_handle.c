#include "core_state_handle.h"
#include <stdlib.h>

typedef struct CoreStateHandleInternal
{
    void* state_instance;
    CoreState core_state;
    HandleStateCallback handle_state_callback;
} CoreStateHandleImplementation;

CoreStateHandle CoreStateHandle_Construct(void* state_instance, CoreState core_state, HandleStateCallback handle_state_callback)
{
    CoreStateHandle instance = (CoreStateHandle)malloc(sizeof(CoreStateHandleImplementation));

    if(instance != NULL)
    {
        instance->state_instance = (void*)state_instance;
        instance->core_state = core_state;
        instance->handle_state_callback = handle_state_callback;
    }
    else
    {
        instance = CORE_STATE_HANDLE_INVALID_INSTANCE;
    }

    return instance;
}

void CoreStateHandle_Destruct(CoreStateHandle* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = CORE_STATE_HANDLE_INVALID_INSTANCE;
    }
}

CoreStateHandle CoreStateHandle_ExecuteHandleState(CoreStateHandle instance)
{
    return instance->handle_state_callback(instance->state_instance);
}

CoreState CoreStateHandle_GetCoreState(CoreStateHandle instance)
{
    return instance->core_state;
}
