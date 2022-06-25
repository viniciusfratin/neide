#include "irrigator_mock.hpp"

IrrigatorMock::IrrigatorMock()
{
    this->last_irrigation_time_seconds = -1;
}

IrrigatorMock::~IrrigatorMock()
{

}

void IrrigatorMock::Irrigate(int32_t irrigation_time_seconds)
{
    this->last_irrigation_time_seconds = irrigation_time_seconds;
}

int32_t IrrigatorMock::GetLastIrrigationTime()
{
    return this->last_irrigation_time_seconds;
}
