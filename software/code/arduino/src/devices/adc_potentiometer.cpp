#include "adc_potentiometer.hpp"
#include "pin_utils/adc_utils.hpp"

struct ADCPotentiometer::impl
{
    ADCIdentifier adc_identifier;

    impl(
        ADCIdentifier adc_identifier
    )
    {
        this->adc_identifier = adc_identifier;
    }

    float GetRelativeValue()
    {
        float adc_voltage_read = read_adc(this->adc_identifier);

        return (adc_voltage_read / A_VCC);
    }
};

ADCPotentiometer::ADCPotentiometer(
    ADCIdentifier adc_identifier
) : pImpl(
        new impl(
            adc_identifier
        )
    )
{

}

ADCPotentiometer::~ADCPotentiometer()
{
    delete pImpl;
}

float ADCPotentiometer::GetRelativeValue()
{
    return pImpl->GetRelativeValue();
}
