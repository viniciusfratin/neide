#include "core.h"
#include <stdlib.h>

typedef struct SystemCoreInternal
{
    CoreStateHandle current_core_state_handle;
} SystemCoreImplementation;

SystemCore SystemCore_Construct(CoreStateHandle initial_core_state_handle)
{
    SystemCore instance = (SystemCore)malloc(sizeof(SystemCoreImplementation));

    if(instance != NULL)
    {
        instance->current_core_state_handle = initial_core_state_handle;
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
    return CoreStateHandle_GetCoreState(instance->current_core_state_handle);
}

void SystemCore_AdvanceCycle(SystemCore instance)
{
    instance->current_core_state_handle = 
        CoreStateHandle_ExecuteHandleState(
            instance->current_core_state_handle
        );
}
