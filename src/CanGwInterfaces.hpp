#pragma once

#include <memory>

#include "CanGwModel.hpp"
#include "Interfaces/CAN.hpp"


class CanGwInterfaces
{
public:
    CanGwInterfaces(CanGwModel* canGwModel);
    Interfaces::CAN* getCanInterface();

private:
    std::unique_ptr<Interfaces::CAN> canInterface_;
};