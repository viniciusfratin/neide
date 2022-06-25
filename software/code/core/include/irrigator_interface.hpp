#ifndef IRRIGATOR_INTERFACE_H
#define IRRIGATOR_INTERFACE_H

#include <stdint.h>

typedef struct IrrigatorInterfaceInternal* IrrigatorInterface;

#define IRRIGATOR_INTERFACE_INVALID_INSTANCE ((IrrigatorInterface)NULL)


void IrrigatorInterface_Irrigate(IrrigatorInterface instance, int32_t irrigation_time_seconds);


#endif