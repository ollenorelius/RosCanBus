#pragma once

#include "Controllers/FrameToSignalsController.hpp"
#include "Controllers/SignalPublishingController.hpp"
#include "Controllers/ImuPublishController.hpp"
#include <memory>
#include "Controllers/CanTransmitterController.hpp"
#include "Controllers/RosSubscriberController.hpp"

class CanGwModel;
class CanGwInterfaces;

class CanGwController
{
public:
    CanGwController(CanGwModel* canGwModel, CanGwInterfaces* canGwInterfaces);

private:
    std::unique_ptr<FrameToSignalsController> frameToSignalsController_;
    std::unique_ptr<SignalPublishingController> signalPublishingController_;
    std::unique_ptr<ImuPublishController> imuPublishController_;

    std::unique_ptr<CanTransmitterController> canTransmitterController_;

    std::unique_ptr<RosSubscriberController> rosSubscriberController_;
};