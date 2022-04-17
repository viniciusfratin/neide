#ifndef CORE_STATES_H
#define CORE_STATES_H

typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0,
    CORE_STATE_WOKE = 1,
    CORE_STATE_SOIL_HUMIDITY_CHECK = 2
} CoreState;

#endif