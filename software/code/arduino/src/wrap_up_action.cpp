#include "wrap_up_action.hpp"
#include "wrap_up_action_interface.hpp"

struct WrapUpAction::impl
{
    impl()
    {

    }

    void WrapUp()
    {

    }
};

WrapUpAction::WrapUpAction() : 
    pImpl(
        new impl()
    )
{

}

WrapUpAction::~WrapUpAction()
{
    
}


void WrapUpAction::WrapUp()
{
    pImpl->WrapUp();
}
