#include "irrigator_mock.hpp"

IrrigatorMock::IrrigatorMock()
{
    this->last_irrigation_time_seconds = -1;
}

IrrigatorMock::~IrrigatorMock()
{

}

void IrrigatorMock::Irrigate(long irrigation_time_seconds)
{
    this->last_irrigation_time_seconds = irrigation_time_seconds;
}

long IrrigatorMock::GetLastIrrigationTime()
{
    return this->last_irrigation_time_seconds;
}
