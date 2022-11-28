#ifndef SOIL_PERIODIC_CHECK_STATE_HPP
#define SOIL_PERIODIC_CHECK_STATE_HPP

#include "core_state_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"

class SoilPeriodicCheckState : public CoreStateInterface
{
    public:
    SoilPeriodicCheckState(
        TimeFromLastIrrigationProviderInterface* soil_time_from_last_irrigation_provider_interface_ptr,
        long maximum_period_seconds
    );

    void SetTransitions(
        CoreStateInterface* irrigate_soil_state_interface_ptr,
        CoreStateInterface* air_humidity_check_state_interface_ptr
    );
    
    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~SoilPeriodicCheckState();

    private:
    struct impl;
    impl* pImpl;
};

#endif