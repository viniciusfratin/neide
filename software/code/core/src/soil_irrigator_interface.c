#include "soil_irrigator_interface.h"
#include "soil_irrigator_interface_construction.h"
#include <stdlib.h>

typedef struct SoilIrrigatorInterfaceInternal
{
    void* object_instance;
    IrrigateSoilCallback irrigate_soil_callback;
} SoilIrrigatorInterfaceImplementation;

SoilIrrigatorInterface SoilIrrigatorInterface_Construct(void* object_instance, IrrigateSoilCallback irrigate_soil_callback)
{
    SoilIrrigatorInterface instance = (SoilIrrigatorInterface)malloc(sizeof(SoilIrrigatorInterfaceImplementation));

    if(instance != NULL)
    {
        instance->object_instance = object_instance;
        instance->irrigate_soil_callback = irrigate_soil_callback;
    }
    else
    {
        instance = SOIL_IRRIGATOR_INTERFACE_INVALID_INSTANCE;
    }

    return instance;
}

void SoilIrrigatorInterface_Destruct(SoilIrrigatorInterface* instancePtr)
{
    if(instancePtr != NULL)
    {
        free(*instancePtr);
        (*instancePtr) = SOIL_IRRIGATOR_INTERFACE_INVALID_INSTANCE;
    }
}

void SoilIrrigatorInterface_IrrigateSoil(SoilIrrigatorInterface instance, int irrigation_time_seconds)
{
    instance->irrigate_soil_callback(instance->object_instance, irrigation_time_seconds);
}
