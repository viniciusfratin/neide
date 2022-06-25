#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "common.hpp"
#include "core_state_interface.hpp"

typedef struct IdleStateInternal* IdleState;

#define IDLE_STATE_INVALID_INSTANCE ((IdleState)NULL)

typedef Bool (*ShouldWakeUpCallback)();


CoreStateInterface IdleState_GetCoreStateInterface(IdleState instance);


IdleState IdleState_Construct(ShouldWakeUpCallback should_wake_up_callback, CoreStateInterface* woke_state_interface_ptr);
void IdleState_Destruct(IdleState* instancePtr);


#endif