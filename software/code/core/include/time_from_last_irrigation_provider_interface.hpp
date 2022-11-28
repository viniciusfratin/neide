#ifndef TIME_FROM_LAST_IRRIGATION_PROVIDER_INTERFACE_HPP
#define TIME_FROM_LAST_IRRIGATION_PROVIDER_INTERFACE_HPP

class TimeFromLastIrrigationProviderInterface
{
    public:
    virtual long GetTimeFromLastIrrigationSeconds() = 0;
};

#endif