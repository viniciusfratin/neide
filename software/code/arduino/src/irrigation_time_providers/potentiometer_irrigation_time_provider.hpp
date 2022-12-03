#ifndef POTENTIOMETER_IRRIGATION_TIME_PROVIDER_HPP
#define POTENTIOMETER_IRRIGATION_TIME_PROVIDER_HPP

#include "irrigation_time_provider_interface.hpp"
#include "devices/potentiometer_interface.hpp"

class PotentiometerIrrigationTimeProvider : public IrrigationTimeProviderInterface
{
    public:
    PotentiometerIrrigationTimeProvider(
        PotentiometerInterface* potentiometer,
        int min_irrigation_time_seconds,
        int max_irrigation_time_seconds
    );

    int GetIrrigationTimeSeconds() override;
    
    virtual ~PotentiometerIrrigationTimeProvider();

    private:
    struct impl;
    impl* pImpl;
};

#endif