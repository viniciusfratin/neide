#ifndef WRAP_UP_STATE_HPP
#define WRAP_UP_STATE_HPP

#include "core_state_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include <memory>

class WrapUpState : public CoreStateInterface
{
    public:
    WrapUpState(
        WrapUpActionInterface* wrap_up_action_interface_ptr
    );

    void SetTransitions(
        CoreStateInterface* idle_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~WrapUpState();

    private:
    struct impl;
    std::unique_ptr<impl> pImpl;
};

#endif