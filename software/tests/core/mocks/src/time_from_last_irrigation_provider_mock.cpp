#include "time_from_last_irrigation_provider_mock.hpp"

TimeFromLastIrrigationProviderMock::TimeFromLastIrrigationProviderMock(long time_from_last_irrigation_seconds) :
    time_from_last_irrigation_seconds(time_from_last_irrigation_seconds)
{

}

TimeFromLastIrrigationProviderMock::~TimeFromLastIrrigationProviderMock()
{

}

long TimeFromLastIrrigationProviderMock::GetTimeFromLastIrrigationSeconds()
{
    return this->time_from_last_irrigation_seconds;
}