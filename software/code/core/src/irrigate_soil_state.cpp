#include "irrigate_soil_state.hpp"
#include "irrigator_interface.hpp"
#include "core_state_interface.hpp"

struct IrrigateSoilState::impl
{
    CoreState core_state;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    IrrigatorInterface* soil_irrigator_interface_ptr;
    IrrigationTimeProviderInterface* soil_irrigation_time_provider_ptr;

    impl(
        IrrigatorInterface* soil_irrigator_interface_ptr,
        IrrigationTimeProviderInterface* soil_irrigation_time_provider_ptr
    )
    {
        this->core_state = CoreState::CORE_STATE_IRRIGATE_SOIL;
        this->soil_irrigator_interface_ptr = soil_irrigator_interface_ptr;
        this->soil_irrigation_time_provider_ptr = soil_irrigation_time_provider_ptr;
    }

    void SetTransitions(
        CoreStateInterface* air_humidity_check_state_interface_ptr
    )
    {
        this->air_humidity_check_state_interface_ptr = air_humidity_check_state_interface_ptr;
    }

    CoreStateInterface* ExecuteState()
    {
        CoreStateInterface* next_core_state_interface = this->air_humidity_check_state_interface_ptr;
    
        this->soil_irrigator_interface_ptr->Irrigate(
            (long)this->soil_irrigation_time_provider_ptr->GetIrrigationTimeSeconds()
        );

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

IrrigateSoilState::IrrigateSoilState(
    IrrigatorInterface* soil_irrigator_interface_ptr,
    IrrigationTimeProviderInterface* soil_irrigation_time_provider_ptr
) : pImpl(
        new impl(
            soil_irrigator_interface_ptr,
            soil_irrigation_time_provider_ptr
        )
    )
{
    
}

IrrigateSoilState::~IrrigateSoilState()
{
    delete pImpl;
}

void IrrigateSoilState::SetTransitions(
    CoreStateInterface* air_humidity_check_state_interface_ptr
)
{
    pImpl->SetTransitions(air_humidity_check_state_interface_ptr);
}

CoreStateInterface* IrrigateSoilState::ExecuteState()
{
    return pImpl->ExecuteState();
}

CoreState IrrigateSoilState::GetCoreState()
{
    return pImpl->GetCoreState();
}
