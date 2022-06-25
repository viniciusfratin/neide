#ifndef WRAP_UP_STATE_H
#define WRAP_UP_STATE_H

#include "common.hpp"
#include "core_state_interface.hpp"
#include "wrap_up_action_interface.hpp"

typedef struct WrapUpStateInternal* WrapUpState;

#define WRAP_UP_STATE_INVALID_INSTANCE ((WrapUpState)NULL)


CoreStateInterface WrapUpState_GetCoreStateInterface(WrapUpState instance);


WrapUpState WrapUpState_Construct(WrapUpActionInterface* wrap_up_action_interface_ptr, CoreStateInterface* idle_state_interface_ptr);
void WrapUpState_Destruct(WrapUpState* instancePtr);


#endif