#ifndef AIR_HUMIDITY_CHECK_STATE_HPP
#define AIR_HUMIDITY_CHECK_STATE_HPP

#include "core_state_interface.hpp"

typedef struct AirHumidityInformationInternal
{
    float current_relative_humidity;
    float relative_humidity_threshold;
} AirHumidityInformation;

typedef AirHumidityInformation (*GetAirHumidityInformationCallback)();

class AirHumidityCheckState : public CoreStateInterface
{
    public:
    AirHumidityCheckState(
        GetAirHumidityInformationCallback get_air_humidity_information_callback
    );

    void SetTransitions(
        CoreStateInterface* irrigate_air_state_interface_ptr,
        CoreStateInterface* air_periodic_check_state_interface_ptr
    );

    CoreStateInterface* ExecuteState() override;
    CoreState GetCoreState() override;

    virtual ~AirHumidityCheckState();

    private:
    struct impl;
    impl* pImpl;
};

#endif