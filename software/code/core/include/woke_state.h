#ifndef WOKE_STATE_H
#define WOKE_STATE_H

#include "common.h"
#include "core_states.h"

typedef struct WokeStateInternal* WokeState;

#define WOKE_STATE_INVALID_INSTANCE ((WokeState)NULL)


HandleCoreState* WokeState_GetHandleCoreState(WokeState instance);


WokeState WokeState_Construct();
void WokeState_Destruct(WokeState* instancePtr);


#endif