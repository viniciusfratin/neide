#include "wrap_up_state.hpp"
#include "core_state_interface.hpp"
#include "wrap_up_action_interface.hpp"

struct WrapUpState::impl
{
    CoreState core_state;
    WrapUpActionInterface* wrap_up_action_interface_ptr;
    CoreStateInterface* idle_state_interface_ptr;

    impl(
        WrapUpActionInterface* wrap_up_action_interface_ptr
    )
    {
        this->core_state = CoreState::CORE_STATE_WRAP_UP;
        this->wrap_up_action_interface_ptr = wrap_up_action_interface_ptr;
    }

    void SetTransitions(
        CoreStateInterface* idle_state_interface_ptr
    )
    {
        this->idle_state_interface_ptr = idle_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = this->idle_state_interface_ptr;

        this->wrap_up_action_interface_ptr->WrapUp();

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

WrapUpState::WrapUpState(
    WrapUpActionInterface* wrap_up_action_interface_ptr
) : pImpl(
        new impl(
            wrap_up_action_interface_ptr
        )
    )
{

}

WrapUpState::~WrapUpState()
{

}

void WrapUpState::SetTransitions(
    CoreStateInterface* idle_state_interface_ptr
)
{
    pImpl->SetTransitions(idle_state_interface_ptr);
}

CoreStateInterface* WrapUpState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState WrapUpState::GetCoreState()
{
    return pImpl->GetCoreState();
}
