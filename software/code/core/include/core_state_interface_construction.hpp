#ifndef CORE_STATE_INTERFACE_CONSTRUCTION_H
#define CORE_STATE_INTERFACE_CONSTRUCTION_H

#include "core_state_interface.hpp"

typedef CoreStateInterface (*ExecuteStateCallback)(void* object_instance);
typedef CoreState (*GetCoreStateCallback)(void* object_instance);

CoreStateInterface CoreStateInterface_Construct(void* object_instance, GetCoreStateCallback get_core_state_callback, ExecuteStateCallback execute_state_callback);
void CoreStateInterface_Destruct(CoreStateInterface* instancePtr);

#endif