#include "CanGwInterfaces.hpp"

CanGwInterfaces::CanGwInterfaces(CanGwModel* canGwModel) 
{
    canInterface_ = std::make_unique<Interfaces::CAN>();
}

Interfaces::CAN* CanGwInterfaces::getCanInterface() 
{
    return canInterface_.get();
}
