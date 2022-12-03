#ifndef ADC_POTENTIOMETER_HPP
#define ADC_POTENTIOMETER_HPP

#include "potentiometer_interface.hpp"
#include "pin_utils/adc_defs.hpp"

class ADCPotentiometer : public PotentiometerInterface
{
    public:
    ADCPotentiometer(
        ADCIdentifier adc_identifier
    );

    float GetRelativeValue() override;
    
    virtual ~ADCPotentiometer();

    private:
    struct impl;
    impl* pImpl;
};

#endif