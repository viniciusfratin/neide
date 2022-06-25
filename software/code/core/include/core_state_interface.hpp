#ifndef CORE_STATE_INTERFACE_H
#define CORE_STATE_INTERFACE_H

#include "core_states.hpp"

typedef struct CoreStateInterfaceInternal* CoreStateInterface;

#define CORE_STATE_INTERFACE_INVALID_INSTANCE ((CoreStateInterface)NULL)


CoreStateInterface CoreStateInterface_ExecuteState(CoreStateInterface instance);
CoreState CoreStateInterface_GetCoreState(CoreStateInterface instance);


#endif