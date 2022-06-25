#include "soil_humidity_check_state.hpp"
#include "core_state_interface.hpp"

struct SoilHumidityCheckState::impl
{
    CoreState core_state;
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback;
    CoreStateInterface* irrigate_soil_state_interface_ptr;
    CoreStateInterface* soil_periodic_check_state_interface_ptr;

    impl(
        GetSoilHumidityInformationCallback get_soil_humidity_information_callback
    )
    {
        this->core_state = CoreState::CORE_STATE_SOIL_HUMIDITY_CHECK;
        this->get_soil_humidity_information_callback = get_soil_humidity_information_callback;
    }

    void SetTransitions(
        CoreStateInterface* irrigate_soil_state_interface_ptr,
        CoreStateInterface* soil_periodic_check_state_interface_ptr
    )
    {
        this->irrigate_soil_state_interface_ptr = irrigate_soil_state_interface_ptr;
        this->soil_periodic_check_state_interface_ptr = soil_periodic_check_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = nullptr;
    
        SoilHumidityInformation soil_humidity_information = this->get_soil_humidity_information_callback();
        
        if(soil_humidity_information.current_relative_humidity < soil_humidity_information.relative_humidity_threshold)
        {
            next_core_state_interface = this->irrigate_soil_state_interface_ptr;
        }
        else
        {
            next_core_state_interface = this->soil_periodic_check_state_interface_ptr;
        }

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

SoilHumidityCheckState::SoilHumidityCheckState(
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback
) : pImpl(
        new impl(
            get_soil_humidity_information_callback
        )
    )
{

}

void SoilHumidityCheckState::SetTransitions(
    CoreStateInterface* irrigate_soil_state_interface_ptr,
    CoreStateInterface* soil_periodic_check_state_interface_ptr
)
{
    pImpl->SetTransitions(
        irrigate_soil_state_interface_ptr,
        soil_periodic_check_state_interface_ptr
    );
}

SoilHumidityCheckState::~SoilHumidityCheckState()
{
    
}

CoreStateInterface* SoilHumidityCheckState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState SoilHumidityCheckState::GetCoreState()
{
    return pImpl->GetCoreState();
}
