#include "standard_configuration.hpp"
#include "idle_state.hpp"
#include "woke_state.hpp"
#include "soil_humidity_check_state.hpp"
#include "soil_periodic_check_state.hpp"
#include "irrigate_soil_state.hpp"
#include "air_humidity_check_state.hpp"
#include "air_periodic_check_state.hpp"
#include "irrigate_air_state.hpp"
#include "wrap_up_state.hpp"
#include <memory>
#include <cstdint>

struct StandardConfiguration::impl
{
    std::unique_ptr<SystemCore> system_core;

    std::unique_ptr<IdleState> idle_state;
    std::unique_ptr<WokeState> woke_state;
    std::unique_ptr<SoilHumidityCheckState> soil_humidity_check_state;
    std::unique_ptr<SoilPeriodicCheckState> soil_periodic_check_state;
    std::unique_ptr<IrrigateSoilState> irrigate_soil_state;
    std::unique_ptr<AirHumidityCheckState> air_humidity_check_state;
    std::unique_ptr<AirPeriodicCheckState> air_periodic_check_state;
    std::unique_ptr<IrrigateAirState> irrigate_air_state;
    std::unique_ptr<WrapUpState> wrap_up_state;

    impl(
        ShouldWakeUpCallback should_wake_up_callback,
        GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
        GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
        int32_t soil_periodic_check_maximum_period,
        IrrigatorInterface* soil_irrigator_ptr,
        int32_t soil_irrigation_time,
        GetAirHumidityInformationCallback get_air_humidity_information_callback,
        GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
        int32_t air_periodic_check_maximum_period,
        IrrigatorInterface* air_irrigator_ptr,
        int32_t air_irrigation_time,
        WrapUpActionInterface* wrap_up_action_ptr
    )
    {
        
        idle_state = std::make_unique<IdleState>(
            should_wake_up_callback
        );

        woke_state = std::make_unique<WokeState>();

        soil_humidity_check_state = std::make_unique<SoilHumidityCheckState>(
            get_soil_humidity_information_callback
        );
        
        soil_periodic_check_state = std::make_unique<SoilPeriodicCheckState>(
            get_time_from_last_soil_irrigation_callback,
            soil_periodic_check_maximum_period
        );
        
        irrigate_soil_state = std::make_unique<IrrigateSoilState>(
            soil_irrigator_ptr,
            soil_irrigation_time
        );
        
        air_humidity_check_state = std::make_unique<AirHumidityCheckState>(
            get_air_humidity_information_callback
        );
        
        air_periodic_check_state = std::make_unique<AirPeriodicCheckState>(
            get_time_from_last_air_irrigation_callback,
            air_periodic_check_maximum_period
        );

        irrigate_air_state = std::make_unique<IrrigateAirState>(
            air_irrigator_ptr,
            air_irrigation_time
        );
        
        wrap_up_state = std::make_unique<WrapUpState>(
            wrap_up_action_ptr
        );

        idle_state->SetTransitions(
            woke_state.get()
        );

        woke_state->SetTransitions(
            soil_humidity_check_state.get()
        );

        soil_humidity_check_state->SetTransitions(
            irrigate_soil_state.get(),
            soil_periodic_check_state.get()
        );

        soil_periodic_check_state->SetTransitions(
            irrigate_soil_state.get(),
            air_humidity_check_state.get()
        );

        irrigate_soil_state->SetTransitions(
            air_humidity_check_state.get()
        );
        
        air_humidity_check_state->SetTransitions(
            irrigate_air_state.get(),
            air_periodic_check_state.get()
        );
        
        air_periodic_check_state->SetTransitions(
            irrigate_air_state.get(), 
            wrap_up_state.get()
        );
        
        irrigate_air_state->SetTransitions(
            wrap_up_state.get()
        );
        
        wrap_up_state->SetTransitions(
            idle_state.get()
        );
        
        this->system_core = std::make_unique<SystemCore>(idle_state.get());
    }

    SystemCore* GetSystemCore()
    {
        return this->system_core.get();
    }
};

StandardConfiguration::StandardConfiguration(
    ShouldWakeUpCallback should_wake_up_callback,
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
    int32_t soil_periodic_check_maximum_period,
    IrrigatorInterface* soil_irrigator_ptr,
    int32_t soil_irrigation_time,
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
    int32_t air_periodic_check_maximum_period,
    IrrigatorInterface* air_irrigator_ptr,
    int32_t air_irrigation_time,
    WrapUpActionInterface* wrap_up_action_ptr
) : pImpl(
        std::make_unique<impl>(
            should_wake_up_callback,
            get_soil_humidity_information_callback,
            get_time_from_last_soil_irrigation_callback,
            soil_periodic_check_maximum_period,
            soil_irrigator_ptr,
            soil_irrigation_time,
            get_air_humidity_information_callback,
            get_time_from_last_air_irrigation_callback,
            air_periodic_check_maximum_period,
            air_irrigator_ptr,
            air_irrigation_time,
            wrap_up_action_ptr
        )
    )
{

}

StandardConfiguration::~StandardConfiguration()
{

}

SystemCore* StandardConfiguration::GetSystemCore()
{
    return pImpl->GetSystemCore();
}
