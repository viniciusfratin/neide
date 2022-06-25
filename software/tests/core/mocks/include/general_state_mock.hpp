#ifndef GENERAL_STATE_MOCK_H
#define GENERAL_STATE_MOCK_H

#include "core_state_interface.hpp"

typedef struct GeneralStateMockInternal* GeneralStateMock;

#define GENERAL_STATE_MOCK_INVALID_INSTANCE ((GeneralStateMock)NULL)


CoreStateInterface GeneralStateMock_GetCoreStateInterface(GeneralStateMock instance);


GeneralStateMock GeneralStateMock_Construct(CoreState core_state);
void GeneralStateMock_Destruct(GeneralStateMock* instancePtr);


#endif