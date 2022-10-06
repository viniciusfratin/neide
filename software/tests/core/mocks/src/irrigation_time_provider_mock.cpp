#include "irrigation_time_provider_mock.hpp"

IrrigationTimeProviderMock::IrrigationTimeProviderMock(long time_from_last_irrigation_seconds) :
    time_from_last_irrigation_seconds(time_from_last_irrigation_seconds)
{

}

IrrigationTimeProviderMock::~IrrigationTimeProviderMock()
{

}

long IrrigationTimeProviderMock::GetTimeFromLastIrrigationSeconds()
{
    return this->time_from_last_irrigation_seconds;
}