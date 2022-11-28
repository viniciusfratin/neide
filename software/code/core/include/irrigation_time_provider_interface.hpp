#ifndef IRRIGATION_TIME_PROVIDER_INTERFACE_HPP
#define IRRIGATION_TIME_PROVIDER_INTERFACE_HPP

class IrrigationTimeProviderInterface
{
    public:
    virtual int GetIrrigationTimeSeconds() = 0;
};

#endif