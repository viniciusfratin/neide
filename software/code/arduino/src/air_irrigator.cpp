#include "air_irrigator.hpp"
#include "irrigator_interface.hpp"
#include "pin_utils/gpio_utils.hpp"
#include <avr/io.h>

#define PWM_DDR_PIN (DDRB)
#define PWM_PIN (PB1)

struct AirIrrigator::impl
{
    long last_irrigation_time;
    GetCurrentTimeSecondsCallback get_current_time_seconds_callback;
    volatile unsigned char* pin_ddr_ptr;
    volatile unsigned char* pin_port_ptr; 
    unsigned char pin;
    ADCIdentifier configuration_adc;

    impl(
        GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
        volatile unsigned char* pin_ddr_ptr, 
        volatile unsigned char* pin_port_ptr, 
        unsigned char pin,
        ADCIdentifier configuration_adc
    )
    {
        this->last_irrigation_time = 0;
        this->get_current_time_seconds_callback = get_current_time_seconds_callback;
        this->pin_ddr_ptr = pin_ddr_ptr;
        this->pin_port_ptr = pin_port_ptr;
        this->pin = pin;
        this->configuration_adc = configuration_adc;

        SET_GPIO_PIN_AS_OUTPUT(this->pin_ddr_ptr, this->pin);
        SET_GPIO_PIN_TO_LOW(this->pin_port_ptr, this->pin);

        /* Set fast PWM on pin 9 with maximum frequency, initially turned off. */
        TCCR1A |= _BV(COM1A1) | _BV(WGM10);
        TCCR1B |= _BV(CS10) | _BV(WGM12);
        PWM_DDR_PIN &= ~(_BV(PWM_PIN));
    }

    long GetTimeFromLastIrrigation()
    {
        long current_time = this->get_current_time_seconds_callback();

        return (current_time - this->last_irrigation_time);
    }

    void Irrigate(long irrigation_time_seconds)
    {
        this->last_irrigation_time = this->get_current_time_seconds_callback();

        /* Set PWM duty cycle to the trim pot in ADC pin. */
        unsigned char duty_cycle = (unsigned char)((read_adc(this->configuration_adc) / A_VCC) * 255);
        OCR1A = duty_cycle;

        /* Turn on indication LED. */
        SET_GPIO_PIN_TO_HIGH(this->pin_port_ptr, this->pin);

        /* Enable fast PWM on pin 9 with maximum frequency. */
        PWM_DDR_PIN |= _BV(PWM_PIN);

        while((this->get_current_time_seconds_callback() - this->last_irrigation_time) <= irrigation_time_seconds);

        /* Disable PWM. */
        PWM_DDR_PIN &= ~(_BV(PWM_PIN));

        /* Turn off indication LED. */
        SET_GPIO_PIN_TO_LOW(this->pin_port_ptr, this->pin);
    }
};

AirIrrigator::AirIrrigator(
    GetCurrentTimeSecondsCallback get_current_time_seconds_callback, 
    volatile unsigned char* pin_ddr_ptr, 
    volatile unsigned char* pin_port_ptr, 
    unsigned char pin,
    ADCIdentifier configuration_adc
) : pImpl(
        new impl(
            get_current_time_seconds_callback,
            pin_ddr_ptr,
            pin_port_ptr,
            pin,
            configuration_adc
        )
    )
{

}

AirIrrigator::~AirIrrigator()
{
    
}

void AirIrrigator::Irrigate(long irrigation_time_seconds)
{
    pImpl->Irrigate(irrigation_time_seconds);
}

long AirIrrigator::GetTimeFromLastIrrigation()
{
    return pImpl->GetTimeFromLastIrrigation();
}
