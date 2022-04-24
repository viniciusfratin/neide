#include "wrap_up_action_mock.h"
#include "wrap_up_action_interface.h"
#include "wrap_up_action_interface_construction.h"
#include <stdlib.h>

typedef struct WrapUpActionMockInternal
{
    WrapUpActionInterface wrap_up_action_interface;
    int number_of_calls;
} WrapUpActionMockImplementation;

static void WrapUpActionMock_WrapUp(void* object_instance);

WrapUpActionMock WrapUpActionMock_Construct()
{
    WrapUpActionMock instance = (WrapUpActionMock)malloc(sizeof(WrapUpActionMockImplementation));

    if(instance != NULL)
    {
        instance->wrap_up_action_interface = WrapUpActionInterface_Construct(
            (void*)instance,
            WrapUpActionMock_WrapUp
        );

        if(instance->wrap_up_action_interface != WRAP_UP_ACTION_INTERFACE_INVALID_INSTANCE)
        {
            instance->number_of_calls = 0;
        }
        else
        {
            instance = WRAP_UP_ACTION_MOCK_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = WRAP_UP_ACTION_MOCK_INVALID_INSTANCE;
    }

    return instance;
}

void WrapUpActionMock_Destruct(WrapUpActionMock* instancePtr)
{
    if(instancePtr != NULL)
    {
        WrapUpActionInterface_Destruct(&((*instancePtr)->wrap_up_action_interface));

        free(*instancePtr);
        (*instancePtr) = WRAP_UP_ACTION_MOCK_INVALID_INSTANCE;
    }
}

WrapUpActionInterface WrapUpActionMock_GetWrapUpActionInterface(WrapUpActionMock instance)
{
    return instance->wrap_up_action_interface;
}

int WrapUpActionMock_GetNumberOfCalls(WrapUpActionMock instance)
{
    return instance->number_of_calls;
}

static void WrapUpActionMock_WrapUp(void* object_instance)
{
    WrapUpActionMock instance = (WrapUpActionMock)object_instance;
    instance->number_of_calls += 1;
}


