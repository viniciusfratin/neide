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

struct StandardConfiguration::impl
{
    SystemCore* system_core;

    IdleState* idle_state;
    WokeState* woke_state;
    SoilHumidityCheckState* soil_humidity_check_state;
    SoilPeriodicCheckState* soil_periodic_check_state;
    IrrigateSoilState* irrigate_soil_state;
    AirHumidityCheckState* air_humidity_check_state;
    AirPeriodicCheckState* air_periodic_check_state;
    IrrigateAirState* irrigate_air_state;
    WrapUpState* wrap_up_state;

    impl(
        ShouldWakeUpCallback should_wake_up_callback,
        GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
        GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
        long soil_periodic_check_maximum_period,
        IrrigatorInterface* soil_irrigator_ptr,
        long soil_irrigation_time,
        GetAirHumidityInformationCallback get_air_humidity_information_callback,
        GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
        long air_periodic_check_maximum_period,
        IrrigatorInterface* air_irrigator_ptr,
        long air_irrigation_time,
        WrapUpActionInterface* wrap_up_action_ptr
    )
    {
        
        idle_state = new IdleState(
            should_wake_up_callback
        );

        woke_state = new WokeState();

        soil_humidity_check_state = new SoilHumidityCheckState(
            get_soil_humidity_information_callback
        );
        
        soil_periodic_check_state = new SoilPeriodicCheckState(
            get_time_from_last_soil_irrigation_callback,
            soil_periodic_check_maximum_period
        );
        
        irrigate_soil_state = new IrrigateSoilState(
            soil_irrigator_ptr,
            soil_irrigation_time
        );
        
        air_humidity_check_state = new AirHumidityCheckState(
            get_air_humidity_information_callback
        );
        
        air_periodic_check_state = new AirPeriodicCheckState(
            get_time_from_last_air_irrigation_callback,
            air_periodic_check_maximum_period
        );

        irrigate_air_state = new IrrigateAirState(
            air_irrigator_ptr,
            air_irrigation_time
        );
        
        wrap_up_state = new WrapUpState(
            wrap_up_action_ptr
        );

        idle_state->SetTransitions(
            woke_state
        );

        woke_state->SetTransitions(
            soil_humidity_check_state
        );

        soil_humidity_check_state->SetTransitions(
            irrigate_soil_state,
            soil_periodic_check_state
        );

        soil_periodic_check_state->SetTransitions(
            irrigate_soil_state,
            air_humidity_check_state
        );

        irrigate_soil_state->SetTransitions(
            air_humidity_check_state
        );
        
        air_humidity_check_state->SetTransitions(
            irrigate_air_state,
            air_periodic_check_state
        );
        
        air_periodic_check_state->SetTransitions(
            irrigate_air_state, 
            wrap_up_state
        );
        
        irrigate_air_state->SetTransitions(
            wrap_up_state
        );
        
        wrap_up_state->SetTransitions(
            idle_state
        );
        
        this->system_core = new SystemCore(idle_state);
    }

    SystemCore* GetSystemCore()
    {
        return this->system_core;
    }
};

StandardConfiguration::StandardConfiguration(
    ShouldWakeUpCallback should_wake_up_callback,
    GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
    GetTimeFromLastSoilIrrigationCallback get_time_from_last_soil_irrigation_callback,
    long soil_periodic_check_maximum_period,
    IrrigatorInterface* soil_irrigator_ptr,
    long soil_irrigation_time,
    GetAirHumidityInformationCallback get_air_humidity_information_callback,
    GetTimeFromLastAirIrrigationCallback get_time_from_last_air_irrigation_callback,
    long air_periodic_check_maximum_period,
    IrrigatorInterface* air_irrigator_ptr,
    long air_irrigation_time,
    WrapUpActionInterface* wrap_up_action_ptr
) : pImpl(
        new impl(
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