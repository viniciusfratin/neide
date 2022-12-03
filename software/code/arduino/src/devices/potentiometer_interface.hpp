#ifndef POTENTIOMETER_INTERFACE_HPP
#define POTENTIOMETER_INTERFACE_HPP

class PotentiometerInterface
{
    public:
    virtual float GetRelativeValue() = 0;
};

#endif