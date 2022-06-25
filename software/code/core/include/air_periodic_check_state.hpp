#ifndef AIR_PERIODIC_CHECK_STATE_HPP
#define AIR_PERIODIC_CHECK_STATE_HPP

#include "core_state_interface.hpp"

typedef long (*GetTimeFromLastAirIrrigationCallback)();

class AirPeriodicCheckState : public CoreStateInterface
{
    public:
    AirPeriodicCheckState(
        GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback,
        long maximum_period_seconds
    );

    void SetTransitions(
        CoreStateInterface* irrigate_air_state_interface_ptr,
        CoreStateInterface* wrap_up_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~AirPeriodicCheckState();

    private:
    struct impl;
    impl* pImpl;
};

#endif