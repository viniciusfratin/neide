#include "core.h"
#include <stdlib.h>

typedef struct SystemCoreInternal
{
    CoreState current_system_state;
} SystemCoreImplementation;

SystemCore SystemCore_Construct()
{
    SystemCore instance = (SystemCore)malloc(sizeof(SystemCoreImplementation));

    if(instance != NULL)
    {
        instance->current_system_state = CORE_STATE_IDLE;
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
    return instance->current_system_state;
}

