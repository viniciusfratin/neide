#ifndef WRAP_UP_ACTION_INTERFACE_CONSTRUCTION_H
#define WRAP_UP_ACTION_INTERFACE_CONSTRUCTION_H

#include "wrap_up_action_interface.hpp"

typedef void (*WrapUpActionCallback)(void* object_instance);

WrapUpActionInterface WrapUpActionInterface_Construct(void* object_instance, WrapUpActionCallback wrap_up_action_callback);
void WrapUpActionInterface_Destruct(WrapUpActionInterface* instancePtr);

#endif