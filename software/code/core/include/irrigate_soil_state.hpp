#ifndef IRRIGATE_SOIL_STATE_HPP
#define IRRIGATE_SOIL_STATE_HPP

#include "core_state_interface.hpp"
#include "irrigator_interface.hpp"
#include <cstdint>
#include <memory>

class IrrigateSoilState : public CoreStateInterface
{
    public:
    IrrigateSoilState(
        IrrigatorInterface* soil_irrigator_interface_ptr,
        int32_t irrigation_time_seconds
    );

    void SetTransitions(
        CoreStateInterface* air_humidity_check_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~IrrigateSoilState();

    private:
    struct impl;
    std::unique_ptr<impl> pImpl;
};

#endif