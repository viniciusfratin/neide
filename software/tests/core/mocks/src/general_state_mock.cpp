#include "general_state_mock.hpp"
#include "core_state_interface.hpp"
#include "core_state_interface_construction.hpp"
#include <stdlib.h>

typedef struct GeneralStateMockInternal
{
    CoreStateInterface general_state_interface;
    CoreState core_state;
} GeneralStateMockImplementation;

static CoreStateInterface GeneralStateMock_ExecuteGeneralStateMock(void* object_instance);
static CoreState GeneralStateMock_GetCoreState(void* object_instance);

GeneralStateMock GeneralStateMock_Construct(CoreState core_state)
{
    GeneralStateMock instance = (GeneralStateMock)malloc(sizeof(GeneralStateMockImplementation));

    if(instance != NULL)
    {
        instance->general_state_interface = CoreStateInterface_Construct(
            (void*)instance,
            GeneralStateMock_GetCoreState,
            GeneralStateMock_ExecuteGeneralStateMock
        );

        if(instance->general_state_interface != CORE_STATE_INTERFACE_INVALID_INSTANCE)
        {
            instance->core_state = core_state;
        }
        else
        {
            instance = GENERAL_STATE_MOCK_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = GENERAL_STATE_MOCK_INVALID_INSTANCE;
    }

    return instance;
}

void GeneralStateMock_Destruct(GeneralStateMock* instancePtr)
{
    if(instancePtr != NULL)
    {
        CoreStateInterface_Destruct(&((*instancePtr)->general_state_interface));

        free(*instancePtr);
        (*instancePtr) = GENERAL_STATE_MOCK_INVALID_INSTANCE;
    }
}

CoreStateInterface GeneralStateMock_GetCoreStateInterface(GeneralStateMock instance)
{
    return instance->general_state_interface;
}

static CoreStateInterface GeneralStateMock_ExecuteGeneralStateMock(void* object_instance)
{
    GeneralStateMock instance = (GeneralStateMock)object_instance;
    CoreStateInterface next_core_state_interface = GeneralStateMock_GetCoreStateInterface(instance);

    return next_core_state_interface;
}

static CoreState GeneralStateMock_GetCoreState(void* object_instance)
{
    GeneralStateMock instance = (GeneralStateMock)object_instance;

    return instance->core_state;
}
