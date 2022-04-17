#include "core_state_interface.h"
#include "core_state_interface_private.h"
#include <stdlib.h>

typedef struct CoreStateInterfaceInternal
{
    void* state_instance;
    GetCoreStateCallback get_core_state_callback;
    ExecuteStateCallback execute_state_callback;
} CoreStateInterfaceImplementation;

CoreStateInterface CoreStateInterface_Construct(void* state_instance, GetCoreStateCallback get_core_state_callback, ExecuteStateCallback execute_state_callback)
{
    CoreStateInterface instance = (CoreStateInterface)malloc(sizeof(CoreStateInterfaceImplementation));

    if(instance != NULL)
    {
        instance->state_instance = (void*)state_instance;
        instance->get_core_state_callback = get_core_state_callback;
        instance->execute_state_callback = execute_state_callback;
    }
    else
    {
        instance = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    }

    return instance;
}

void CoreStateInterface_Destruct(CoreStateInterface* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = CORE_STATE_INTERFACE_INVALID_INSTANCE;
    }
}

CoreStateInterface CoreStateInterface_ExecuteState(CoreStateInterface instance)
{
    return instance->execute_state_callback(instance->state_instance);
}

CoreState CoreStateInterface_GetCoreState(CoreStateInterface instance)
{
    return instance->get_core_state_callback(instance->state_instance);
}