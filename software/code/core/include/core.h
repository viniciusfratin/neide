#ifndef CORE_H
#define CORE_H

#include "common.h"

typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0
} CoreState;

typedef struct SystemCoreInternal* SystemCore;

#define SYSTEM_CORE_INVALID_INSTANCE ((SystemCore)NULL)

SystemCore SystemCore_Construct();
void SystemCore_Destruct(SystemCore* instancePtr);

CoreState SystemCore_GetCurrentState(SystemCore instance);

#endif