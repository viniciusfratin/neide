#ifndef AIR_IRRIGATOR_HPP
#define AIR_IRRIGATOR_HPP

#include "irrigator_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"
#include "pin_utils/adc_utils.hpp"
#include "clock/clock.hpp"

class AirIrrigator : public IrrigatorInterface, public TimeFromLastIrrigationProviderInterface
{
    public:
    AirIrrigator(
        GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
        volatile unsigned char* pin_ddr_ptr, 
        volatile unsigned char* pin_port_ptr, 
        unsigned char pin,
        ADCIdentifier configuration_adc
    );

    void Irrigate(long irrigation_time_seconds) override;
    long GetTimeFromLastIrrigationSeconds() override;
    
    virtual ~AirIrrigator();

    private:
    struct impl;
    impl* pImpl;
};

#endif