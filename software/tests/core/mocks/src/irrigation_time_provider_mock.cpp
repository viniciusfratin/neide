#include "irrigation_time_provider_mock.hpp"

IrrigationTimeProviderMock::IrrigationTimeProviderMock(int irrigation_time_seconds) :
    irrigation_time_seconds(irrigation_time_seconds)
{

}

IrrigationTimeProviderMock::~IrrigationTimeProviderMock()
{

}

int IrrigationTimeProviderMock::GetIrrigationTimeSeconds()
{
    return this->irrigation_time_seconds;
}