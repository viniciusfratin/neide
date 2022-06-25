#include "woke_state.hpp"
#include "core_state_interface.hpp"

struct WokeState::impl
{
    CoreState core_state;
    CoreStateInterface* soil_humidity_check_state_interface_ptr;

    impl()
    {
        this->core_state = CoreState::CORE_STATE_WOKE;
        
    }

    void SetTransitions(
        CoreStateInterface* soil_humidity_check_state_interface_ptr
    )
    {
        this->soil_humidity_check_state_interface_ptr = soil_humidity_check_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface =  this->soil_humidity_check_state_interface_ptr;

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

WokeState::WokeState() : 
    pImpl(
        new impl()
    )
{

}

WokeState::~WokeState()
{
    delete pImpl;
}

void WokeState::SetTransitions(
    CoreStateInterface* soil_humidity_check_state_interface_ptr
)
{
    pImpl->SetTransitions(
        soil_humidity_check_state_interface_ptr
    );
}

CoreStateInterface* WokeState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState WokeState::GetCoreState()
{
    return pImpl->GetCoreState();
}
