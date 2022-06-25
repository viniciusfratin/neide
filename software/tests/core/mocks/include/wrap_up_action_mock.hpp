#ifndef WRAP_UP_ACTION_MOCK_H
#define WRAP_UP_ACTION_MOCK_H

#include "wrap_up_action_interface.hpp"

class WrapUpActionMock : public WrapUpActionInterface
{
    public:
    WrapUpActionMock();
    virtual ~WrapUpActionMock();
    
    void WrapUp() override;
    long GetNumberOfCalls();

    private:
    long number_of_calls;
};

#endif