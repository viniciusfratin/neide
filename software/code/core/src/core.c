#include "core.h"
#include <stdlib.h>

typedef struct SystemCoreInternal
{
    CoreState current_system_state;
    ShouldWakeUpCallback should_wake_up_callback;
} SystemCoreImplementation;

SystemCore SystemCore_Construct(ShouldWakeUpCallback should_wake_up_callback)
{
    SystemCore instance = (SystemCore)malloc(sizeof(SystemCoreImplementation));

    if(instance != NULL)
    {
        instance->current_system_state = CORE_STATE_IDLE;
        instance->should_wake_up_callback = should_wake_up_callback;
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

void SystemCore_AdvanceCycle(SystemCore instance)
{
    CoreState next_state = CORE_STATE_IDLE;

    switch (instance->current_system_state)
    {
        case CORE_STATE_IDLE:
            if(instance->should_wake_up_callback() == TRUE)
            {
                next_state = CORE_STATE_WOKE;
            }
            else
            {
                next_state = CORE_STATE_IDLE;
            }
            break;

        case CORE_STATE_WOKE:
            break;
    }

    instance->current_system_state = next_state;
}
