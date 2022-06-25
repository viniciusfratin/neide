#include "wrap_up_action_mock.hpp"

WrapUpActionMock::WrapUpActionMock()
{
    this->number_of_calls = 0;
}

WrapUpActionMock::~WrapUpActionMock()
{

}

void WrapUpActionMock::WrapUp()
{
    this->number_of_calls++;
}

int32_t WrapUpActionMock::GetNumberOfCalls()
{
    return this->number_of_calls;
}
