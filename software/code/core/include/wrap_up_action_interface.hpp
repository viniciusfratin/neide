#ifndef WRAP_UP_ACTION_INTERFACE_H
#define WRAP_UP_ACTION_INTERFACE_H

typedef struct WrapUpActionInterfaceInternal* WrapUpActionInterface;

#define WRAP_UP_ACTION_INTERFACE_INVALID_INSTANCE ((WrapUpActionInterface)NULL)


void WrapUpActionInterface_WrapUp(WrapUpActionInterface instance);


#endif