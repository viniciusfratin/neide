#ifndef WRAP_UP_ACTION_MOCK_H
#define WRAP_UP_ACTION_MOCK_H

#include "wrap_up_action_interface.hpp"

typedef struct WrapUpActionMockInternal* WrapUpActionMock;

#define WRAP_UP_ACTION_MOCK_INVALID_INSTANCE ((WrapUpActionMock)NULL)


WrapUpActionInterface WrapUpActionMock_GetWrapUpActionInterface(WrapUpActionMock instance);
int32_t WrapUpActionMock_GetNumberOfCalls(WrapUpActionMock instance);


WrapUpActionMock WrapUpActionMock_Construct();
void WrapUpActionMock_Destruct(WrapUpActionMock* instancePtr);


#endif