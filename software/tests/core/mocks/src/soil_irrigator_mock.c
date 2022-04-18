#include "soil_irrigator_mock.h"
#include "soil_irrigator_interface.h"
#include "soil_irrigator_interface_construction.h"
#include <stdlib.h>

typedef struct SoilIrrigatorMockInternal
{
    SoilIrrigatorInterface soil_irrigator_interface;
    int last_irrigation_time;
} SoilIrrigatorMockImplementation;

static void SoilIrrigatorMock_IrrigateSoil(void* object_instance, int irrigation_time_seconds);

SoilIrrigatorMock SoilIrrigatorMock_Construct()
{
    SoilIrrigatorMock instance = (SoilIrrigatorMock)malloc(sizeof(SoilIrrigatorMockImplementation));

    if(instance != NULL)
    {
        instance->soil_irrigator_interface = SoilIrrigatorInterface_Construct(
            (void*)instance,
            SoilIrrigatorMock_IrrigateSoil
        );

        if(instance->soil_irrigator_interface != SOIL_IRRIGATOR_INTERFACE_INVALID_INSTANCE)
        {
            instance->last_irrigation_time = -1;
        }
        else
        {
            instance = SOIL_IRRIGATOR_MOCK_INVALID_INSTANCE;
        }
    }
    else
    {
        instance = SOIL_IRRIGATOR_MOCK_INVALID_INSTANCE;
    }

    return instance;
}

void SoilIrrigatorMock_Destruct(SoilIrrigatorMock* instancePtr)
{
    if(instancePtr != NULL)
    {
        SoilIrrigatorInterface_Destruct(&((*instancePtr)->soil_irrigator_interface));

        free(*instancePtr);
        (*instancePtr) = SOIL_IRRIGATOR_MOCK_INVALID_INSTANCE;
    }
}

SoilIrrigatorInterface SoilIrrigatorMock_GetSoilIrrigatorInterface(SoilIrrigatorMock instance)
{
    return instance->soil_irrigator_interface;
}

int SoilIrrigatorMock_GetLastIrrigationTime(SoilIrrigatorMock instance)
{
    return instance->last_irrigation_time;
}

static void SoilIrrigatorMock_IrrigateSoil(void* object_instance, int irrigation_time_seconds)
{
    SoilIrrigatorMock instance = (SoilIrrigatorMock)object_instance;
    instance->last_irrigation_time = irrigation_time_seconds;
}


