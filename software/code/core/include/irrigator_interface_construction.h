#ifndef IRRIGATOR_INTERFACE_CONSTRUCTION_H
#define IRRIGATOR_INTERFACE_CONSTRUCTION_H

#include "irrigator_interface.h"

typedef void (*IrrigateCallback)(void* object_instance, int irrigation_time_seconds);

IrrigatorInterface IrrigatorInterface_Construct(void* object_instance, IrrigateCallback irrigate_callback);
void IrrigatorInterface_Destruct(IrrigatorInterface* instancePtr);

#endif