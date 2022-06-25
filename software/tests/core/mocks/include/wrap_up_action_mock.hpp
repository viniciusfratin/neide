#ifndef WRAP_UP_ACTION_MOCK_H
#define WRAP_UP_ACTION_MOCK_H

#include "wrap_up_action_interface.hpp"
#include <cstdint>

class WrapUpActionMock : public WrapUpActionInterface
{
    public:
    WrapUpActionMock();
    virtual ~WrapUpActionMock();
    
    void WrapUp() override;
    int32_t GetNumberOfCalls();

    private:
    int32_t number_of_calls;
};

#endif