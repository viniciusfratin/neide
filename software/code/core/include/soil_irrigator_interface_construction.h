#ifndef SOIL_IRRIGATOR_INTERFACE_CONSTRUCTION_H
#define SOIL_IRRIGATOR_INTERFACE_CONSTRUCTION_H

#include "soil_irrigator_interface.h"

typedef void (*IrrigateSoilCallback)(void* object_instance, int irrigation_time_seconds);

SoilIrrigatorInterface SoilIrrigatorInterface_Construct(void* object_instance, IrrigateSoilCallback irrigate_soil_callback);
void SoilIrrigatorInterface_Destruct(SoilIrrigatorInterface* instancePtr);

#endif