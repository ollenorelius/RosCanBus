#include "CanGwInterfaces.hpp"

CanGwInterfaces::CanGwInterfaces(CanGwModel* canGwModel) 
{
    canInterface_ = std::make_unique<Interfaces::CAN>();
}

CanGwInterfaces::~CanGwInterfaces() 
{
    
}

Interfaces::CAN* CanGwInterfaces::getCanInterface() const
{
    return canInterface_.get();
}
