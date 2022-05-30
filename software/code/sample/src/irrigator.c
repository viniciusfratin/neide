#include "irrigator.h"
#include "irrigator_interface.h"
#include "irrigator_interface_construction.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct IrrigatorInternal
{
    IrrigatorInterface irrigator_interface;
    int32_t last_irrigation_time;
} IrrigatorImplementation;

static void Irrigator_Irrigate(void* object_instance, int32_t irrigation_time_seconds);

Irrigator Irrigator_Construct()
{
    Irrigator instance = (Irrigator)malloc(sizeof(IrrigatorImplementation));

    if(instance != NULL)
    {
        instance->irrigator_interface = IrrigatorInterface_Construct(
            (void*)instance,
            Irrigator_Irrigate
        );

        if(instance->irrigator_interface != IRRIGATOR_INTERFACE_INVALID_INSTANCE)
        {
            instance->last_irrigation_time = -1;
        }
        else
        {
            instance = IRRIGATOR_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = IRRIGATOR_INVALID_INSTANCE;
    }

    return instance;
}

void Irrigator_Destruct(Irrigator* instancePtr)
{
    if(instancePtr != NULL)
    {
        IrrigatorInterface_Destruct(&((*instancePtr)->irrigator_interface));

        free(*instancePtr);
        (*instancePtr) = IRRIGATOR_INVALID_INSTANCE;
    }
}

IrrigatorInterface Irrigator_GetIrrigatorInterface(Irrigator instance)
{
    return instance->irrigator_interface;
}

int32_t Irrigator_GetLastIrrigationTime(Irrigator instance)
{
    return instance->last_irrigation_time;
}

static void Irrigator_Irrigate(void* object_instance, int32_t irrigation_time_seconds)
{
    Irrigator instance = (Irrigator)object_instance;
    instance->last_irrigation_time = irrigation_time_seconds;
    printf("- Irrigating: %d\n", irrigation_time_seconds);
}


