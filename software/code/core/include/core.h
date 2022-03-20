#ifndef CORE_H
#define CORE_H

#include "common.h"

typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0
} CoreState;

typedef struct SystemCoreInternal* SystemCore;

SystemCore SystemCore_Construct();
Bool SystemCore_IsInstanceValid(SystemCore instance);
void SystemCore_Destruct(SystemCore* instancePtr);

CoreState SystemCore_GetCurrentState(SystemCore instance);

#endif