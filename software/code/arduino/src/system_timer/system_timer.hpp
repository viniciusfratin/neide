#ifndef SYSTEM_TIMER_HPP
#define SYSTEM_TIMER_HPP

#include "clock/clock.hpp"

void SystemTimer_Initialize();
long SystemTimer_GetCurrentTimeSeconds();
long SystemTimer_GetCurrentTimeMinutes();

#endif