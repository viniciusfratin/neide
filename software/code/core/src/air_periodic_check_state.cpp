#include "air_periodic_check_state.hpp"
#include "core_state_interface.hpp"
#include <memory>

struct AirPeriodicCheckState::impl
{
    CoreState core_state;
    GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback;
    CoreStateInterface* irrigate_air_state_interface_ptr;
    CoreStateInterface* wrap_up_state_interface_ptr;
    int32_t maximum_period_seconds;

    impl(
        GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback,
        int32_t maximum_period_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_AIR_PERIODIC_CHECK;
        this->get_time_from_last_irrigation_callback = get_time_from_last_irrigation_callback;
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
        
        int32_t time_from_last_irrigation = this->get_time_from_last_irrigation_callback();
        
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
    GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback,
    int32_t maximum_period_seconds
) : pImpl(
        std::make_unique<impl>(
            get_time_from_last_irrigation_callback,
            maximum_period_seconds
        )
    )
{

}

AirPeriodicCheckState::~AirPeriodicCheckState()
{
    
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
