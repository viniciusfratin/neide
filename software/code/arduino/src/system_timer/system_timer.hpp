#ifndef SYSTEM_TIMER_H
#define SYSTEM_TIMER_H

#include "clock/clock.hpp"

void SystemTimer_Initialize();
long SystemTimer_GetCurrentTimeSeconds();
long SystemTimer_GetCurrentTimeMinutes();

#endif