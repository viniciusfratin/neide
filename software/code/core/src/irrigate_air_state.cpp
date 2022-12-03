#include "irrigate_air_state.hpp"
#include "irrigator_interface.hpp"
#include "core_state_interface.hpp"

struct IrrigateAirState::impl
{
    CoreState core_state;
    CoreStateInterface* wrap_up_state_interface_ptr;
    IrrigatorInterface* air_irrigator_interface_ptr;
    IrrigationTimeProviderInterface* air_irrigation_time_provider_ptr;

    impl(
        IrrigatorInterface* air_irrigator_interface_ptr,
        IrrigationTimeProviderInterface* air_irrigation_time_provider_ptr
    )
    {
        this->core_state = CoreState::CORE_STATE_IRRIGATE_AIR;
        this->air_irrigator_interface_ptr = air_irrigator_interface_ptr;
        this->air_irrigation_time_provider_ptr = air_irrigation_time_provider_ptr;
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
    
        this->air_irrigator_interface_ptr->Irrigate(
            (long)this->air_irrigation_time_provider_ptr->GetIrrigationTimeSeconds()
        );

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

IrrigateAirState::IrrigateAirState(
    IrrigatorInterface* air_irrigator_interface_ptr,
    IrrigationTimeProviderInterface* air_irrigation_time_provider_ptr
) : pImpl(
        new impl(
            air_irrigator_interface_ptr,
            air_irrigation_time_provider_ptr
        )
    )
{

}

IrrigateAirState::~IrrigateAirState()
{
    delete pImpl;
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
