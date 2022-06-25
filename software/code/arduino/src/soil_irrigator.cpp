#include "soil_irrigator.hpp"
#include "irrigator_interface.hpp"
#include "pin_utils/gpio_utils.hpp"

struct SoilIrrigator::impl
{
    long last_irrigation_time;
    GetCurrentTimeSecondsCallback get_current_time_seconds_callback;
    volatile unsigned char* pin_ddr_ptr;
    volatile unsigned char* pin_port_ptr; 
    unsigned char pin;

    impl(
        GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
        volatile unsigned char* pin_ddr_ptr, 
        volatile unsigned char* pin_port_ptr, 
        unsigned char pin
    )
    {
        this->last_irrigation_time = 0;
        this->get_current_time_seconds_callback = get_current_time_seconds_callback;
        this->pin_ddr_ptr = pin_ddr_ptr;
        this->pin_port_ptr = pin_port_ptr;
        this->pin = pin;

        SET_GPIO_PIN_AS_OUTPUT(this->pin_ddr_ptr, this->pin);
        SET_GPIO_PIN_TO_LOW(this->pin_port_ptr, this->pin);
    }

    long GetTimeFromLastIrrigation()
    {
        long current_time = this->get_current_time_seconds_callback();

        return (current_time - this->last_irrigation_time);
    }

    void Irrigate(long irrigation_time_seconds)
    {
        this->last_irrigation_time = this->get_current_time_seconds_callback();

        SET_GPIO_PIN_TO_HIGH(this->pin_port_ptr, this->pin);
        while((this->get_current_time_seconds_callback() - this->last_irrigation_time) <= irrigation_time_seconds);
        SET_GPIO_PIN_TO_LOW(this->pin_port_ptr, this->pin);
    }
};

SoilIrrigator::SoilIrrigator(
    GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
    volatile unsigned char* pin_ddr_ptr, 
    volatile unsigned char* pin_port_ptr, 
    unsigned char pin
) : pImpl(
        new impl(
            get_current_time_seconds_callback,
            pin_ddr_ptr,
            pin_port_ptr,
            pin
        )
    )
{

}

SoilIrrigator::~SoilIrrigator()
{
    delete pImpl;
}

void SoilIrrigator::Irrigate(long irrigation_time_seconds)
{
    pImpl->Irrigate(irrigation_time_seconds);
}

long SoilIrrigator::GetTimeFromLastIrrigation()
{
    return pImpl->GetTimeFromLastIrrigation();
}
