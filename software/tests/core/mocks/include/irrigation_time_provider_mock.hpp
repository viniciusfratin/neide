#ifndef IRRIGATION_TIME_PROVIDER_MOCK_HPP
#define IRRIGATION_TIME_PROVIDER_MOCK_HPP

#include "irrigation_time_provider_interface.hpp"

class IrrigationTimeProviderMock : public IrrigationTimeProviderInterface
{
    public:
    IrrigationTimeProviderMock(int irrigation_time_seconds);
    virtual ~IrrigationTimeProviderMock();

    int GetIrrigationTimeSeconds() override;

    private:
    const int irrigation_time_seconds;
};

#endif