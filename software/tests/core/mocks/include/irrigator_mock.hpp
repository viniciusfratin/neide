#ifndef IRRIGATOR_MOCK_H
#define IRRIGATOR_MOCK_H

#include "irrigator_interface.hpp"

class IrrigatorMock : public IrrigatorInterface
{
    public:
    IrrigatorMock();
    virtual ~IrrigatorMock();
    
    void Irrigate(long irrigation_time_seconds) override;
    long GetLastIrrigationTime();

    private:
    long last_irrigation_time_seconds;
};

#endif