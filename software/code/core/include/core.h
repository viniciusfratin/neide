#ifndef CORE_H
#define CORE_H

#include "common.h"
#include "core_state_handle.h"

typedef struct SystemCoreInternal* SystemCore;

#define SYSTEM_CORE_INVALID_INSTANCE ((SystemCore)NULL)


CoreState SystemCore_GetCurrentState(SystemCore instance);
void SystemCore_AdvanceCycle(SystemCore instance);


SystemCore SystemCore_Construct(CoreStateHandle initial_core_state_handle);
void SystemCore_Destruct(SystemCore* instancePtr);


#endif