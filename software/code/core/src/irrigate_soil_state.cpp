#include "irrigate_soil_state.hpp"
#include "irrigator_interface.hpp"
#include "core_state_interface.hpp"
#include <memory>

struct IrrigateSoilState::impl
{
    CoreState core_state;
    CoreStateInterface* air_humidity_check_state_interface_ptr;
    IrrigatorInterface* soil_irrigator_interface_ptr;
    int32_t irrigation_time_seconds;

    impl(
        IrrigatorInterface* soil_irrigator_interface_ptr,
        int32_t irrigation_time_seconds
    )
    {
        this->core_state = CoreState::CORE_STATE_IRRIGATE_SOIL;
        this->soil_irrigator_interface_ptr = soil_irrigator_interface_ptr;
        this->irrigation_time_seconds = irrigation_time_seconds;
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
    
        this->soil_irrigator_interface_ptr->Irrigate(this->irrigation_time_seconds);

        return next_core_state_interface;
    }
    
    CoreState GetCoreState()
    {
        return this->core_state;
    }
};

IrrigateSoilState::IrrigateSoilState(
    IrrigatorInterface* soil_irrigator_interface_ptr,
    int32_t irrigation_time_seconds
) : pImpl(
        std::make_unique<impl>(
            soil_irrigator_interface_ptr,
            irrigation_time_seconds
        )
    )
{

}

IrrigateSoilState::~IrrigateSoilState()
{

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
