#ifndef IRRIGATOR_MOCK_H
#define IRRIGATOR_MOCK_H

#include "irrigator_interface.hpp"
#include <stdint.h>

typedef struct IrrigatorMockInternal* IrrigatorMock;

#define IRRIGATOR_MOCK_INVALID_INSTANCE ((IrrigatorMock)NULL)


IrrigatorInterface IrrigatorMock_GetIrrigatorInterface(IrrigatorMock instance);
int32_t IrrigatorMock_GetLastIrrigationTime(IrrigatorMock instance);


IrrigatorMock IrrigatorMock_Construct();
void IrrigatorMock_Destruct(IrrigatorMock* instancePtr);


#endif