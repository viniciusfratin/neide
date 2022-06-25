#include "idle_state.hpp"
#include "core_state_interface.hpp"

struct IdleState::impl
{
    CoreState core_state;
    CoreStateInterface* instance;
    ShouldWakeUpCallback should_wake_up_callback;
    CoreStateInterface* woke_state_interface_ptr;

    impl(
        CoreStateInterface* instance,
        ShouldWakeUpCallback should_wake_up_callback
    )
    {
        this->core_state = CoreState::CORE_STATE_IDLE;
        this->instance = instance;
        this->should_wake_up_callback = should_wake_up_callback;
    }
    
    void SetTransitions(
        CoreStateInterface* woke_state_interface_ptr
    )
    {
        this->woke_state_interface_ptr = woke_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = nullptr;

        if(this->should_wake_up_callback())
        {
            next_core_state_interface = this->woke_state_interface_ptr;
        }
        else
        {
            next_core_state_interface = instance;
        }

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

IdleState::IdleState(
    ShouldWakeUpCallback should_wake_up_callback
) : pImpl(
        new impl(
            this,
            should_wake_up_callback
        )
    )
{

}

IdleState::~IdleState()
{
    delete pImpl;
}

void IdleState::SetTransitions(
    CoreStateInterface* woke_state_interface_ptr
)
{
    pImpl->SetTransitions(
        woke_state_interface_ptr
    );
}

CoreStateInterface* IdleState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState IdleState::GetCoreState()
{
    return pImpl->GetCoreState();
}
