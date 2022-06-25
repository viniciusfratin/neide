#ifndef SOIL_HUMIDITY_CHECK_STATE_HPP
#define SOIL_HUMIDITY_CHECK_STATE_HPP

#include "core_state_interface.hpp"

typedef struct SoilHumidityInformationInternal
{
    float current_relative_humidity;
    float relative_humidity_threshold;
} SoilHumidityInformation;

typedef SoilHumidityInformation (*GetSoilHumidityInformationCallback)();

class SoilHumidityCheckState : public CoreStateInterface
{
    public:
    SoilHumidityCheckState(
        GetSoilHumidityInformationCallback get_soil_humidity_information_callback
    );

    void SetTransitions(
        CoreStateInterface* irrigate_soil_state_interface_ptr,
        CoreStateInterface* soil_periodic_check_state_interface_ptr
    );
    
    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~SoilHumidityCheckState();

    private:
    struct impl;
    impl* pImpl;
};

#endif