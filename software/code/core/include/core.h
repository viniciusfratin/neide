#ifndef CORE_H
#define CORE_H

#include "common.h"


typedef struct SystemCoreInternal* SystemCore;

#define SYSTEM_CORE_INVALID_INSTANCE ((SystemCore)NULL)


typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0,
    CORE_STATE_WOKE = 1
} CoreState;

typedef Bool (*ShouldWakeUpCallback)();

CoreState SystemCore_GetCurrentState(SystemCore instance);
void SystemCore_AdvanceCycle(SystemCore instance);


SystemCore SystemCore_Construct(ShouldWakeUpCallback should_wake_up_callback);
void SystemCore_Destruct(SystemCore* instancePtr);


#endif