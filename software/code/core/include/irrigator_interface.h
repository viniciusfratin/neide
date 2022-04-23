#ifndef IRRIGATOR_INTERFACE_H
#define IRRIGATOR_INTERFACE_H

typedef struct IrrigatorInterfaceInternal* IrrigatorInterface;

#define IRRIGATOR_INTERFACE_INVALID_INSTANCE ((IrrigatorInterface)NULL)


void IrrigatorInterface_Irrigate(IrrigatorInterface instance, int irrigation_time_seconds);


#endif