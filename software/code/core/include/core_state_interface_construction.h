#ifndef CORE_STATE_INTERFACE_CONSTRUCTION_H
#define CORE_STATE_INTERFACE_CONSTRUCTION_H

#include "core_state_interface.h"

typedef CoreStateInterface (*ExecuteStateCallback)(void* state_instance);
typedef CoreState (*GetCoreStateCallback)(void* state_instance);

CoreStateInterface CoreStateInterface_Construct(void* state_instance, GetCoreStateCallback get_core_state_callback, ExecuteStateCallback execute_state_callback);
void CoreStateInterface_Destruct(CoreStateInterface* instancePtr);

#endif