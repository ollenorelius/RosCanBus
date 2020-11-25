#pragma once

#include "Controllers/FrameToSignalsController.hpp"
#include "Controllers/SignalPublishingController.hpp"
#include "Controllers/CanTransmitterController.hpp"

class CanGwModel;
class CanGwInterfaces;

class CanGwController
{
public:
    CanGwController(CanGwModel* canGwModel, CanGwInterfaces* canGwInterfaces);

private:
    std::unique_ptr<FrameToSignalsController> frameToSignalsController_;
    std::unique_ptr<SignalPublishingController> signalPublishingController_;
    std::unique_ptr<CanTransmitterController> canTransmitterController_;
};