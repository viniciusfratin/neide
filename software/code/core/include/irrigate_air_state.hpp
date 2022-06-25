#ifndef IRRIGATE_AIR_STATE_HPP
#define IRRIGATE_AIR_STATE_HPP

#include "core_state_interface.hpp"
#include "irrigator_interface.hpp"

class IrrigateAirState : public CoreStateInterface
{
    public:
    IrrigateAirState(
        IrrigatorInterface* air_irrigator_interface_ptr,
        long irrigation_time_seconds
    );

    void SetTransitions(
        CoreStateInterface* wrap_up_state_interface_ptr
    );
    
    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~IrrigateAirState();

    private:
    struct impl;
    impl* pImpl;
};

#endif