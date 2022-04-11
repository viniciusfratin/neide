#ifndef CORE_H
#define CORE_H

#include "common.h"
#include "core_states.h"

typedef struct SystemCoreInternal* SystemCore;

#define SYSTEM_CORE_INVALID_INSTANCE ((SystemCore)NULL)


CoreState SystemCore_GetCurrentState(SystemCore instance);
void SystemCore_AdvanceCycle(SystemCore instance);


SystemCore SystemCore_Construct(HandleCoreState* initial_handle_core_state);
void SystemCore_Destruct(SystemCore* instancePtr);


#endif