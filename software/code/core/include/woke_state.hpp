#ifndef WOKE_STATE_H
#define WOKE_STATE_H

#include "core_state_interface.hpp"

typedef struct WokeStateInternal* WokeState;

#define WOKE_STATE_INVALID_INSTANCE ((WokeState)NULL)


CoreStateInterface WokeState_GetCoreStateInterface(WokeState instance);


WokeState WokeState_Construct(CoreStateInterface* soil_humidity_check_state_interface_ptr);
void WokeState_Destruct(WokeState* instancePtr);


#endif