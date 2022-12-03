#ifndef IRRIGATE_SOIL_STATE_HPP
#define IRRIGATE_SOIL_STATE_HPP

#include "core_state_interface.hpp"
#include "irrigator_interface.hpp"
#include "irrigation_time_provider_interface.hpp"

class IrrigateSoilState : public CoreStateInterface
{
    public:
    IrrigateSoilState(
        IrrigatorInterface* soil_irrigator_interface_ptr,
        IrrigationTimeProviderInterface* soil_irrigation_time_provider_ptr
    );

    void SetTransitions(
        CoreStateInterface* air_humidity_check_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~IrrigateSoilState();

    private:
    struct impl;
    impl* pImpl;
};

#endif