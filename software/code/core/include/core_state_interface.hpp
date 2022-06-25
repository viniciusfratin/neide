#ifndef CORE_STATE_INTERFACE_HPP
#define CORE_STATE_INTERFACE_HPP

#include "core_states.hpp"

class CoreStateInterface
{
    public:
    virtual CoreStateInterface* ExecuteState() = 0;
    virtual CoreState GetCoreState() = 0;
};

#endif