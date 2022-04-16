#ifndef CORE_STATE_HANDLE_H
#define CORE_STATE_HANDLE_H

#include "core_states.h"

typedef struct CoreStateHandleInternal* CoreStateHandle;
typedef CoreStateHandle (*HandleStateCallback)(void* state_instance);

#define CORE_STATE_HANDLE_INVALID_INSTANCE ((CoreStateHandle)NULL)


CoreStateHandle CoreStateHandle_ExecuteHandleState(CoreStateHandle instance);
CoreState CoreStateHandle_GetCoreState(CoreStateHandle instance);


CoreStateHandle CoreStateHandle_Construct(void* state_instance, CoreState core_state, HandleStateCallback handle_state_callback);
void CoreStateHandle_Destruct(CoreStateHandle* instancePtr);


#endif