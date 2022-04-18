#ifndef SOIL_IRRIGATOR_INTERFACE_H
#define SOIL_IRRIGATOR_INTERFACE_H

typedef struct SoilIrrigatorInterfaceInternal* SoilIrrigatorInterface;

#define SOIL_IRRIGATOR_INTERFACE_INVALID_INSTANCE ((SoilIrrigatorInterface)NULL)


void SoilIrrigatorInterface_IrrigateSoil(SoilIrrigatorInterface instance, int irrigation_time_seconds);


#endif