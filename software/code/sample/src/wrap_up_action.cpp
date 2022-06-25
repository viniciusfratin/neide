#include "wrap_up_action.hpp"
#include "wrap_up_action_interface.hpp"
#include "wrap_up_action_interface_construction.hpp"
#include <stdlib.h>
#include <stdio.h>

typedef struct WrapUpActionInternal
{
    WrapUpActionInterface wrap_up_action_interface;
    int32_t number_of_calls;
} WrapUpActionImplementation;

static void WrapUpAction_WrapUp(void* object_instance);

WrapUpAction WrapUpAction_Construct()
{
    WrapUpAction instance = (WrapUpAction)malloc(sizeof(WrapUpActionImplementation));

    if(instance != NULL)
    {
        instance->wrap_up_action_interface = WrapUpActionInterface_Construct(
            (void*)instance,
            WrapUpAction_WrapUp
        );

        if(instance->wrap_up_action_interface != WRAP_UP_ACTION_INTERFACE_INVALID_INSTANCE)
        {
            instance->number_of_calls = 0;
        }
        else
        {
            instance = WRAP_UP_ACTION_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = WRAP_UP_ACTION_INVALID_INSTANCE;
    }

    return instance;
}

void WrapUpAction_Destruct(WrapUpAction* instancePtr)
{
    if(instancePtr != NULL)
    {
        WrapUpActionInterface_Destruct(&((*instancePtr)->wrap_up_action_interface));

        free(*instancePtr);
        (*instancePtr) = WRAP_UP_ACTION_INVALID_INSTANCE;
    }
}

WrapUpActionInterface WrapUpAction_GetWrapUpActionInterface(WrapUpAction instance)
{
    return instance->wrap_up_action_interface;
}

int32_t WrapUpAction_GetNumberOfCalls(WrapUpAction instance)
{
    return instance->number_of_calls;
}

static void WrapUpAction_WrapUp(void* object_instance)
{
    WrapUpAction instance = (WrapUpAction)object_instance;
    instance->number_of_calls += 1;
    printf("- Wrapping up.\n");
}


