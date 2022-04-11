#include "core.h"
#include <stdlib.h>

typedef struct SystemCoreInternal
{
    HandleCoreState* current_handle_core_state;
} SystemCoreImplementation;

SystemCore SystemCore_Construct(HandleCoreState* initial_handle_core_state)
{
    SystemCore instance = (SystemCore)malloc(sizeof(SystemCoreImplementation));

    if(instance != NULL)
    {
        instance->current_handle_core_state = initial_handle_core_state;
    }
    else
    {
        instance = SYSTEM_CORE_INVALID_INSTANCE;
    }

    return instance;
}

void SystemCore_Destruct(SystemCore* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = SYSTEM_CORE_INVALID_INSTANCE;
    }
}

CoreState SystemCore_GetCurrentState(SystemCore instance)
{
    return instance->current_handle_core_state->core_state;
}

void SystemCore_AdvanceCycle(SystemCore instance)
{
    instance->current_handle_core_state = 
        instance->current_handle_core_state->handle_state_callback(
            instance->current_handle_core_state->state_instance
        );
}
