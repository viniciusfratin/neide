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

    return instance;
}

Bool SystemCore_IsInstanceValid(SystemCore instance)
{
    Bool is_instance_valid = FALSE;

    if(instance != NULL)
    {
        is_instance_valid = TRUE;
    }

    return is_instance_valid;
}

void SystemCore_Destruct(SystemCore* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = NULL;
    }
}

CoreState SystemCore_GetCurrentState(SystemCore instance)
{
    return instance->current_system_state;
}

