#include "air_periodic_check_state.hpp"
#include "core_state_interface.hpp"

struct AirPeriodicCheckState::impl
{
    CoreState core_state;
    TimeFromLastIrrigationProviderInterface* air_time_from_last_irrigation_provider_interface_ptr;
    CoreStateInterface* irrigate_air_state_interface_ptr;
    CoreStateInterface* wrap_up_state_interface_ptr;
    long maximum_period_seconds;

    impl(
        TimeFromLastIrrigationProviderInterface* air_time_from_last_irrigation_provider_interface_ptr,
        long maximum_period_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_AIR_PERIODIC_CHECK;
        this->air_time_from_last_irrigation_provider_interface_ptr = air_time_from_last_irrigation_provider_interface_ptr;
        this->maximum_period_seconds = maximum_period_seconds;
    }

    void SetTransitions(
        CoreStateInterface* irrigate_air_state_interface_ptr,
        CoreStateInterface* wrap_up_state_interface_ptr
    )
    {
        this->irrigate_air_state_interface_ptr = irrigate_air_state_interface_ptr;
        this->wrap_up_state_interface_ptr = wrap_up_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = nullptr;
        
        long time_from_last_irrigation = this->air_time_from_last_irrigation_provider_interface_ptr->GetTimeFromLastIrrigationSeconds();
        
        if(time_from_last_irrigation > this->maximum_period_seconds)
        {
            next_core_state_interface = this->irrigate_air_state_interface_ptr;
        }
        else
        {
            next_core_state_interface = this->wrap_up_state_interface_ptr;
        }
        
        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

AirPeriodicCheckState::AirPeriodicCheckState(
    TimeFromLastIrrigationProviderInterface* air_time_from_last_irrigation_provider_interface_ptr,
    long maximum_period_seconds
) : pImpl(
        new impl(
            air_time_from_last_irrigation_provider_interface_ptr,
            maximum_period_seconds
        )
    )
{

}

AirPeriodicCheckState::~AirPeriodicCheckState()
{
    delete pImpl;
}

void AirPeriodicCheckState::SetTransitions(
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* wrap_up_state_interface_ptr
)
{
    pImpl->SetTransitions(
        irrigate_air_state_interface_ptr,
        wrap_up_state_interface_ptr
    );
}

CoreStateInterface* AirPeriodicCheckState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState AirPeriodicCheckState::GetCoreState()
{
    return pImpl->GetCoreState();
}
