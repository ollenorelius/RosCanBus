#pragma once

#include <memory>

#include "CanGwModel.hpp"
#include "Interfaces/CAN.hpp"
#include "Interfaces/RosPublisher.hpp"


class CanGwInterfaces
{
public:
    CanGwInterfaces(CanGwModel* canGwModel);
    ~CanGwInterfaces();
    Interfaces::CAN* getCanInterface() const;
    Interfaces::RosPublisher* getRosPublisher() const;

private:
    std::unique_ptr<Interfaces::CAN> canInterface_;
    std::unique_ptr<Interfaces::RosPublisher> rosPublisher_;
};