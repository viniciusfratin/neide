#ifndef WRAP_UP_STATE_H
#define WRAP_UP_STATE_H

#include "common.h"
#include "core_state_interface.h"
#include "wrap_up_action_interface.h"

typedef struct WrapUpStateInternal* WrapUpState;

#define WRAP_UP_STATE_INVALID_INSTANCE ((WrapUpState)NULL)


CoreStateInterface WrapUpState_GetCoreStateInterface(WrapUpState instance);


WrapUpState WrapUpState_Construct(WrapUpActionInterface* wrap_up_action_interface_ptr, CoreStateInterface* idle_state_interface_ptr);
void WrapUpState_Destruct(WrapUpState* instancePtr);


#endif