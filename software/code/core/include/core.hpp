#ifndef CORE_HPP
#define CORE_HPP

#include "core_state_interface.hpp"
#include <memory>

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
    std::unique_ptr<impl> pImpl;
};

#endif