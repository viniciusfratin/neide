#ifndef SOIL_IRRIGATOR_HPP
#define SOIL_IRRIGATOR_HPP

#include "irrigator_interface.hpp"
#include "time_from_last_irrigation_provider_interface.hpp"
#include "clock/clock.hpp"

class SoilIrrigator : public IrrigatorInterface, public TimeFromLastIrrigationProviderInterface
{
    public:
    SoilIrrigator(
        GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
        volatile unsigned char* pin_ddr_ptr, 
        volatile unsigned char* pin_port_ptr, 
        unsigned char pin
    );

    void Irrigate(long irrigation_time_seconds) override;
    long GetTimeFromLastIrrigationSeconds() override;
    
    virtual ~SoilIrrigator();

    private:
    struct impl;
    impl* pImpl;
};


#endif