#ifndef STANDARD_CONFIGURATION_HPP
#define STANDARD_CONFIGURATION_HPP

#include "core.hpp"
#include "irrigator_interface.hpp"
#include "wrap_up_action_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"
#include "irrigation_time_provider_interface.hpp"
#include "idle_state.hpp"
#include "soil_humidity_check_state.hpp"
#include "soil_periodic_check_state.hpp"
#include "air_humidity_check_state.hpp"
#include "air_periodic_check_state.hpp"

class StandardConfiguration
{
    public:
    StandardConfiguration(
        ShouldWakeUpCallback should_wake_up_callback,
        GetSoilHumidityInformationCallback get_soil_humidity_information_callback,
        TimeFromLastIrrigationProviderInterface* soil_time_provider_ptr,
        long soil_periodic_check_maximum_period,
        IrrigatorInterface* soil_irrigator_ptr,
        IrrigationTimeProviderInterface* soil_irrigation_time_provider_ptr,
        GetAirHumidityInformationCallback get_air_humidity_information_callback,
        TimeFromLastIrrigationProviderInterface* air_time_provider_ptr,
        long air_periodic_check_maximum_period,
        IrrigatorInterface* air_irrigator_ptr,
        IrrigationTimeProviderInterface* air_irrigation_time_provider_ptr,
        WrapUpActionInterface* wrap_up_action_ptr
    );

    SystemCore* GetSystemCore();

    virtual ~StandardConfiguration();

    private:
    struct impl;
    impl* pImpl;
};

#endif