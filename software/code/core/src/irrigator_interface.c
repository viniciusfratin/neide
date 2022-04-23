#include "irrigator_interface.h"
#include "irrigator_interface_construction.h"
#include <stdlib.h>

typedef struct IrrigatorInterfaceInternal
{
    void* object_instance;
    IrrigateCallback irrigate_callback;
} IrrigatorInterfaceImplementation;

IrrigatorInterface IrrigatorInterface_Construct(void* object_instance, IrrigateCallback irrigate_callback)
{
    IrrigatorInterface instance = (IrrigatorInterface)malloc(sizeof(IrrigatorInterfaceImplementation));

    if(instance != NULL)
    {
        instance->object_instance = object_instance;
        instance->irrigate_callback = irrigate_callback;
    }
    else
    {
        instance = IRRIGATOR_INTERFACE_INVALID_INSTANCE;
    }

    return instance;
}

void IrrigatorInterface_Destruct(IrrigatorInterface* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = IRRIGATOR_INTERFACE_INVALID_INSTANCE;
    }
}

void IrrigatorInterface_Irrigate(IrrigatorInterface instance, int irrigation_time_seconds)
{
    instance->irrigate_callback(instance->object_instance, irrigation_time_seconds);
}
