#include "wrap_up_action_interface.h"
#include "wrap_up_action_interface_construction.h"
#include <stdlib.h>

typedef struct WrapUpActionInterfaceInternal
{
    void* object_instance;
    WrapUpActionCallback wrap_up_callback;
} WrapUpActionInterfaceImplementation;

WrapUpActionInterface WrapUpActionInterface_Construct(void* object_instance, WrapUpActionCallback wrap_up_callback)
{
    WrapUpActionInterface instance = (WrapUpActionInterface)malloc(sizeof(WrapUpActionInterfaceImplementation));

    if(instance != NULL)
    {
        instance->object_instance = object_instance;
        instance->wrap_up_callback = wrap_up_callback;
    }
    else
    {
        instance = WRAP_UP_ACTION_INTERFACE_INVALID_INSTANCE;
    }

    return instance;
}

void WrapUpActionInterface_Destruct(WrapUpActionInterface* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = WRAP_UP_ACTION_INTERFACE_INVALID_INSTANCE;
    }
}

void WrapUpActionInterface_WrapUp(WrapUpActionInterface instance)
{
    instance->wrap_up_callback(instance->object_instance);
}
