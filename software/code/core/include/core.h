#ifndef CORE_H
#define CORE_H

#include "common.h"


typedef struct SystemCoreInternal* SystemCore;

#define SYSTEM_CORE_INVALID_INSTANCE ((SystemCore)NULL)

SystemCore SystemCore_Construct();
void SystemCore_Destruct(SystemCore* instancePtr);


typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0
} CoreState;

CoreState SystemCore_GetCurrentState(SystemCore instance);

#endif