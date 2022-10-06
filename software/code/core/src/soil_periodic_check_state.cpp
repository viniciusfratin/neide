#include "soil_periodic_check_state.hpp"
#include "core_state_interface.hpp"

struct SoilPeriodicCheckState::impl
{
    CoreState core_state;
    IrrigationTimeProviderInterface* soil_irrigation_time_provider_interface_ptr;
    CoreStateInterface* irrigate_soil_state_interface_ptr;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    long maximum_period_seconds;

    impl(
        IrrigationTimeProviderInterface* soil_irrigation_time_provider_interface_ptr,
        long maximum_period_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_SOIL_PERIODIC_CHECK;
        this->soil_irrigation_time_provider_interface_ptr = soil_irrigation_time_provider_interface_ptr;
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
    
        long time_from_last_irrigation = this->soil_irrigation_time_provider_interface_ptr->GetTimeFromLastIrrigationSeconds();
        
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
    IrrigationTimeProviderInterface* soil_irrigation_time_provider_interface_ptr,
    long maximum_period_seconds
) : pImpl(
        new impl(
            soil_irrigation_time_provider_interface_ptr,
            maximum_period_seconds
        )
    )
{

}

SoilPeriodicCheckState::~SoilPeriodicCheckState()
{
    delete pImpl;
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
