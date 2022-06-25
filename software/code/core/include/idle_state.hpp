#ifndef IDLE_STATE_HPP
#define IDLE_STATE_HPP

#include "core_state_interface.hpp"

typedef bool (*ShouldWakeUpCallback)();

class IdleState : public CoreStateInterface
{
    public:
    IdleState(
        ShouldWakeUpCallback should_wake_up_callback
    );

    void SetTransitions(
        CoreStateInterface* woke_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~IdleState();

    private:
    struct impl;
    impl* pImpl;
};

#endif