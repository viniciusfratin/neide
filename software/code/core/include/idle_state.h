#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "common.h"
#include "core_states.h"
#include "woke_state.h"

typedef struct IdleStateInternal* IdleState;

#define IDLE_STATE_INVALID_INSTANCE ((IdleState)NULL)

typedef Bool (*ShouldWakeUpCallback)();


HandleCoreState* IdleState_GetHandleCoreState(IdleState instance);


IdleState IdleState_Construct(ShouldWakeUpCallback should_wake_up_callback, WokeState* woke_state_ptr);
void IdleState_Destruct(IdleState* instancePtr);


#endif