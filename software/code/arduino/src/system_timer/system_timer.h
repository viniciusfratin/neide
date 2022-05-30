#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include "clock/clock.h"
#include <stdint.h>

void SystemTimer_Initialize();
int32_t SystemTimer_GetCurrentTimeSeconds();
int32_t SystemTimer_GetCurrentTimeMinutes();

#endif