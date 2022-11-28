#ifndef TIME_FROM_LAST_IRRIGATION_PROVIDER_MOCK_HPP
#define TIME_FROM_LAST_IRRIGATION_PROVIDER_MOCK_HPP

#include "time_from_last_irrigation_provider_interface.hpp"

class TimeFromLastIrrigationProviderMock : public TimeFromLastIrrigationProviderInterface
{
    public:
    TimeFromLastIrrigationProviderMock(long time_from_last_irrigation_seconds);
    virtual ~TimeFromLastIrrigationProviderMock();

    long GetTimeFromLastIrrigationSeconds() override;

    private:
    const long time_from_last_irrigation_seconds;
};

#endif