#ifndef IRRIGATOR_MOCK_H
#define IRRIGATOR_MOCK_H

#include "irrigator_interface.hpp"
#include <cstdint>

class IrrigatorMock : public IrrigatorInterface
{
    public:
    IrrigatorMock();
    virtual ~IrrigatorMock();
    
    void Irrigate(int32_t irrigation_time_seconds) override;
    int32_t GetLastIrrigationTime();

    private:
    int32_t last_irrigation_time_seconds;
};

#endif