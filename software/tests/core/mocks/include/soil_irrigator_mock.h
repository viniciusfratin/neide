#ifndef SOIL_IRRIGATOR_MOCK_H
#define SOIL_IRRIGATOR_MOCK_H

#include "soil_irrigator_interface.h"

typedef struct SoilIrrigatorMockInternal* SoilIrrigatorMock;

#define SOIL_IRRIGATOR_MOCK_INVALID_INSTANCE ((SoilIrrigatorMock)NULL)


SoilIrrigatorInterface SoilIrrigatorMock_GetSoilIrrigatorInterface(SoilIrrigatorMock instance);
int SoilIrrigatorMock_GetLastIrrigationTime(SoilIrrigatorMock instance);


SoilIrrigatorMock SoilIrrigatorMock_Construct();
void SoilIrrigatorMock_Destruct(SoilIrrigatorMock* instancePtr);


#endif