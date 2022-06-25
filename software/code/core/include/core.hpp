#ifndef CORE_HPP
#define CORE_HPP

#include "core_state_interface.hpp"

class SystemCore
{
    public:
    SystemCore(
        CoreStateInterface* initial_core_state_interface
    );

    CoreState GetCurrentState();
    void AdvanceCycle();

    virtual ~SystemCore();

    private:
    struct impl;
    impl* pImpl;
};

#endif