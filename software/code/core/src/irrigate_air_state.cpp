#include "irrigate_air_state.hpp"
#include "irrigator_interface.hpp"
#include "core_state_interface.hpp"

struct IrrigateAirState::impl
{
    CoreState core_state;
    CoreStateInterface* wrap_up_state_interface_ptr;
    IrrigatorInterface* air_irrigator_interface_ptr;
    long irrigation_time_seconds;

    impl(
        IrrigatorInterface* air_irrigator_interface_ptr,
        long irrigation_time_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_IRRIGATE_AIR;
        this->air_irrigator_interface_ptr = air_irrigator_interface_ptr;
        this->irrigation_time_seconds = irrigation_time_seconds;
    }

    void SetTransitions(
        CoreStateInterface* wrap_up_state_interface_ptr
    )
    {
        this->wrap_up_state_interface_ptr = wrap_up_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = this->wrap_up_state_interface_ptr;
    
        this->air_irrigator_interface_ptr->Irrigate(this->irrigation_time_seconds);

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

IrrigateAirState::IrrigateAirState(
    IrrigatorInterface* air_irrigator_interface_ptr,
    long irrigation_time_seconds
) : pImpl(
        new impl(
            air_irrigator_interface_ptr,
            irrigation_time_seconds
        )
    )
{

}

IrrigateAirState::~IrrigateAirState()
{
    
}

void IrrigateAirState::SetTransitions(
    CoreStateInterface* wrap_up_state_interface_ptr
)
{
    pImpl->SetTransitions(
        wrap_up_state_interface_ptr
    );
}

CoreStateInterface* IrrigateAirState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState IrrigateAirState::GetCoreState()
{
    return pImpl->GetCoreState();
}
