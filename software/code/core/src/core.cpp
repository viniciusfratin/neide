#include "core.hpp"
#include <stdlib.h>

typedef struct SystemCoreInternal
{
    CoreStateInterface current_core_state_interface;
} SystemCoreImplementation;

SystemCore SystemCore_Construct(CoreStateInterface initial_core_state_interface)
{
    SystemCore instance = (SystemCore)malloc(sizeof(SystemCoreImplementation));

    if(instance != NULL)
    {
        instance->current_core_state_interface = initial_core_state_interface;
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
    return CoreStateInterface_GetCoreState(instance->current_core_state_interface);
}

void SystemCore_AdvanceCycle(SystemCore instance)
{
    instance->current_core_state_interface = 
        CoreStateInterface_ExecuteState(
            instance->current_core_state_interface
        );
}
