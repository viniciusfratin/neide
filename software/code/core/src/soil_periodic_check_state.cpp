#include "soil_periodic_check_state.hpp"
#include "core_state_interface.hpp"

struct SoilPeriodicCheckState::impl
{
    CoreState core_state;
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback;
    CoreStateInterface* irrigate_soil_state_interface_ptr;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    long maximum_period_seconds;

    impl(
        GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback,
        long maximum_period_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_SOIL_PERIODIC_CHECK;
        this->get_time_from_last_irrigation_callback = get_time_from_last_irrigation_callback;
        this->maximum_period_seconds = maximum_period_seconds;
    }

    void SetTransitions(
        CoreStateInterface* irrigate_soil_state_interface_ptr,
        CoreStateInterface* air_humidity_check_state_interface_ptr
    )
    {
        this->irrigate_soil_state_interface_ptr = irrigate_soil_state_interface_ptr;
        this->air_humidity_check_state_interface_ptr = air_humidity_check_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = nullptr;
    
        long time_from_last_irrigation = this->get_time_from_last_irrigation_callback();
        
        if(time_from_last_irrigation > this->maximum_period_seconds)
        {
            next_core_state_interface = this->irrigate_soil_state_interface_ptr;
        }
        else
        {
            next_core_state_interface = this->air_humidity_check_state_interface_ptr;
        }

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

SoilPeriodicCheckState::SoilPeriodicCheckState(
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback,
    long maximum_period_seconds
) : pImpl(
        new impl(
            get_time_from_last_irrigation_callback,
            maximum_period_seconds
        )
    )
{

}

SoilPeriodicCheckState::~SoilPeriodicCheckState()
{

}

void SoilPeriodicCheckState::SetTransitions(
    CoreStateInterface* irrigate_soil_state_interface_ptr,
    CoreStateInterface* air_humidity_check_state_interface_ptr
)
{
    pImpl->SetTransitions(
        irrigate_soil_state_interface_ptr, 
        air_humidity_check_state_interface_ptr
    );
}

CoreStateInterface* SoilPeriodicCheckState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState SoilPeriodicCheckState::GetCoreState()
{
    return pImpl->GetCoreState();
}
