#include "air_humidity_check_state.hpp"
#include "core_state_interface.hpp"

struct AirHumidityCheckState::impl
{
    CoreState core_state;
    GetAirHumidityInformationCallback get_air_humidity_information_callback;
    CoreStateInterface* irrigate_air_state_interface_ptr;
    CoreStateInterface* air_periodic_check_state_interface_ptr;

    impl(
        GetAirHumidityInformationCallback get_air_humidity_information_callback
    )
    {
        this->core_state = CoreState::CORE_STATE_AIR_HUMIDITY_CHECK;
        this->get_air_humidity_information_callback = get_air_humidity_information_callback;
    }

    void SetTransitions(
        CoreStateInterface* irrigate_air_state_interface_ptr,
        CoreStateInterface* air_periodic_check_state_interface_ptr
    )
    {
        this->irrigate_air_state_interface_ptr = irrigate_air_state_interface_ptr;
        this->air_periodic_check_state_interface_ptr = air_periodic_check_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = nullptr;
        
        AirHumidityInformation air_humidity_information = this->get_air_humidity_information_callback();
        
        if(air_humidity_information.current_relative_humidity < air_humidity_information.relative_humidity_threshold)
        {
            next_core_state_interface = this->irrigate_air_state_interface_ptr;
        }
        else
        {
            next_core_state_interface = this->air_periodic_check_state_interface_ptr;
        }
        
        return next_core_state_interface;
    }

    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

AirHumidityCheckState::AirHumidityCheckState(
    GetAirHumidityInformationCallback get_air_humidity_information_callback
) : pImpl(
        new impl(
            get_air_humidity_information_callback
        )
    )
{

}

AirHumidityCheckState::~AirHumidityCheckState()
{
    delete pImpl;
}

void AirHumidityCheckState::SetTransitions(
    CoreStateInterface* irrigate_air_state_interface_ptr,
    CoreStateInterface* air_periodic_check_state_interface_ptr
)
{
    pImpl->SetTransitions(
        irrigate_air_state_interface_ptr,
        air_periodic_check_state_interface_ptr
    );
}

CoreStateInterface* AirHumidityCheckState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState AirHumidityCheckState::GetCoreState()
{
    return pImpl->GetCoreState();
}
