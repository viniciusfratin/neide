#ifndef SOIL_PERIODIC_CHECK_STATE_HPP
#define SOIL_PERIODIC_CHECK_STATE_HPP

#include "core_state_interface.hpp"
#include <memory>

typedef int32_t (*GetTimeFromLastSoilIrrigationCallback)();

class SoilPeriodicCheckState : public CoreStateInterface
{
    public:
    SoilPeriodicCheckState(
        GetTimeFromLastSoilIrrigationCallback get_time_from_last_irrigation_callback,
        int32_t maximum_period_seconds
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
    std::unique_ptr<impl> pImpl;
};

#endif