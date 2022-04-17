#ifndef WOKE_STATE_H
#define WOKE_STATE_H

#include "common.h"
#include "core_state_handle.h"

typedef struct WokeStateInternal* WokeState;

#define WOKE_STATE_INVALID_INSTANCE ((WokeState)NULL)


CoreStateInterface WokeState_GetCoreStateInterface(WokeState instance);


WokeState WokeState_Construct();
void WokeState_Destruct(WokeState* instancePtr);


#endif