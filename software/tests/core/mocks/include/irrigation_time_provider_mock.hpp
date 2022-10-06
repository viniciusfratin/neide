#ifndef IRRIGATION_TIME_PROVIDER_MOCK_HPP
#define IRRIGATION_TIME_PROVIDER_MOCK_HPP

#include "irrigation_time_provider_interface.hpp"

class IrrigationTimeProviderMock : public IrrigationTimeProviderInterface
{
    public:
    IrrigationTimeProviderMock(long time_from_last_irrigation_seconds);
    virtual ~IrrigationTimeProviderMock();

    long GetTimeFromLastIrrigationSeconds() override;

    private:
    const long time_from_last_irrigation_seconds;
};

#endif