#ifndef WRAP_UP_ACTION_H
#define WRAP_UP_ACTION_H

#include "wrap_up_action_interface.hpp"
#include <stdint.h>

typedef struct WrapUpActionInternal* WrapUpAction;

#define WRAP_UP_ACTION_INVALID_INSTANCE ((WrapUpAction)NULL)


WrapUpActionInterface WrapUpAction_GetWrapUpActionInterface(WrapUpAction instance);
int32_t WrapUpAction_GetNumberOfCalls(WrapUpAction instance);


WrapUpAction WrapUpAction_Construct();
void WrapUpAction_Destruct(WrapUpAction* instancePtr);


#endif