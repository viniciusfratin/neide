#ifndef IRRIGATION_TIME_PROVIDER_INTERFACE_HPP
#define IRRIGATION_TIME_PROVIDER_INTERFACE_HPP

class TimeFromLastIrrigationProviderInterface
{
    public:
    virtual long GetTimeFromLastIrrigationSeconds() = 0;
};

#endif