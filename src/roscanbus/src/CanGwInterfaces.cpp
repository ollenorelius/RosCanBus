#include "CanGwInterfaces.hpp"

CanGwInterfaces::CanGwInterfaces(CanGwModel* canGwModel) 
{
    canInterface_ = std::make_unique<Interfaces::CAN>();
    //rosPublisher_ = std::make_unique<Interfaces::RosPublisher>(canGwModel->getRosNodeModel());
    imuPublisher_ = std::make_unique<Interfaces::ImuPublisher>();
}

CanGwInterfaces::~CanGwInterfaces() 
{
    
}

Interfaces::CAN* CanGwInterfaces::getCanInterface() const
{
    return canInterface_.get();
}
