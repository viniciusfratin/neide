#ifndef AIR_PERIODIC_CHECK_STATE_HPP
#define AIR_PERIODIC_CHECK_STATE_HPP

#include "core_state_interface.hpp"
#include <cstdint>
#include <memory>

typedef int32_t (*GetTimeFromLastAirIrrigationCallback)();

class AirPeriodicCheckState : public CoreStateInterface
{
    public:
    AirPeriodicCheckState(
        GetTimeFromLastAirIrrigationCallback get_time_from_last_irrigation_callback,
        int32_t maximum_period_seconds
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
    std::unique_ptr<impl> pImpl;
};

#endif