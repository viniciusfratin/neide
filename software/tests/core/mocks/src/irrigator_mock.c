#include "irrigator_mock.h"
#include "irrigator_interface.h"
#include "irrigator_interface_construction.h"
#include <stdlib.h>

typedef struct IrrigatorMockInternal
{
    IrrigatorInterface irrigator_interface;
    int last_irrigation_time;
} IrrigatorMockImplementation;

static void IrrigatorMock_Irrigate(void* object_instance, int irrigation_time_seconds);

IrrigatorMock IrrigatorMock_Construct()
{
    IrrigatorMock instance = (IrrigatorMock)malloc(sizeof(IrrigatorMockImplementation));

    if(instance != NULL)
    {
        instance->irrigator_interface = IrrigatorInterface_Construct(
            (void*)instance,
            IrrigatorMock_Irrigate
        );

        if(instance->irrigator_interface != IRRIGATOR_INTERFACE_INVALID_INSTANCE)
        {
            instance->last_irrigation_time = -1;
        }
        else
        {
            instance = IRRIGATOR_MOCK_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = IRRIGATOR_MOCK_INVALID_INSTANCE;
    }

    return instance;
}

void IrrigatorMock_Destruct(IrrigatorMock* instancePtr)
{
    if(instancePtr != NULL)
    {
        IrrigatorInterface_Destruct(&((*instancePtr)->irrigator_interface));

        free(*instancePtr);
        (*instancePtr) = IRRIGATOR_MOCK_INVALID_INSTANCE;
    }
}

IrrigatorInterface IrrigatorMock_GetIrrigatorInterface(IrrigatorMock instance)
{
    return instance->irrigator_interface;
}

int IrrigatorMock_GetLastIrrigationTime(IrrigatorMock instance)
{
    return instance->last_irrigation_time;
}

static void IrrigatorMock_Irrigate(void* object_instance, int irrigation_time_seconds)
{
    IrrigatorMock instance = (IrrigatorMock)object_instance;
    instance->last_irrigation_time = irrigation_time_seconds;
}


