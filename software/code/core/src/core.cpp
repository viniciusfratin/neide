#include "core.hpp"
#include "core_state_interface.hpp"

struct SystemCore::impl
{
    CoreStateInterface* current_core_state_interface;

    impl(
        CoreStateInterface* initial_core_state_interface
    )
    {
        this->current_core_state_interface = initial_core_state_interface;
    }

    CoreState GetCurrentState()
    {
        return this->current_core_state_interface->GetCoreState();
    }

    void AdvanceCycle()
    {
        this->current_core_state_interface = this->current_core_state_interface->ExecuteState();
    }
};

SystemCore::SystemCore(
    CoreStateInterface* initial_core_state_interface
) : pImpl(
        new impl(
            initial_core_state_interface
        )
    )
{

}

SystemCore::~SystemCore()
{

}

CoreState SystemCore::GetCurrentState()
{
    return pImpl->GetCurrentState();
}

void SystemCore::AdvanceCycle()
{
    pImpl->AdvanceCycle();
}
