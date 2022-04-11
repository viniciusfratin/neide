#ifndef CORE_STATES_H
#define CORE_STATES_H

typedef enum CoreStateInternal
{
    CORE_STATE_IDLE = 0,
    CORE_STATE_WOKE = 1
} CoreState;

typedef struct HandleCoreStateInternal
{
    void* state_instance;
    CoreState core_state;
    struct HandleCoreStateInternal* (*handle_state_callback)(void* state_instance);
} HandleCoreState;

#endif